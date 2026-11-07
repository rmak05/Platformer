#include "EntityManager.hpp"

EntityManager::EntityManager() {
	entity_count			= 0u;
	sorted_entities			= std::vector<std::vector<entity_ptr>>((size_t)EntityType::count);
	display_textures		= true;
	display_bounding_boxes	= false;
}

void EntityManager::delete_inactive_entities(std::vector<entity_ptr>& entity_vec) {
	int vec_size = static_cast<int>(entity_vec.size()), curr = 0, last = vec_size;

	while (curr < last) {
		if (!entity_vec[curr]->is_active()) {
			std::swap(entity_vec[curr], entity_vec[--last]);
		}
		else {
			curr++;
		}
	}

	entity_vec.resize(last);
}

entity_ptr EntityManager::add_entity(const EntityType _type) {
	entity_ptr new_entity = entity_ptr(new Entity(++entity_count, _type));
	entites_to_add.push_back(new_entity);

	return new_entity;
}

void EntityManager::delete_entity(entity_ptr& _entity) {
	_entity->set_inactive();
}

void EntityManager::update_added_entities() {
	for (entity_ptr _entity : entites_to_add) {
		all_entities.push_back(_entity);
		sorted_entities[static_cast<int>(_entity->get_type())].push_back(_entity);
	}
	entites_to_add.clear();
}

void EntityManager::update_deleted_entities() {
	delete_inactive_entities(all_entities);
	for(auto& entity_vec : sorted_entities) delete_inactive_entities(entity_vec);
}

void EntityManager::transform_entities() {
	for (auto& _entity : all_entities) {
		_entity->transform();
	}
}

void EntityManager::resolve_collisions() {}

void EntityManager::update_animations() {
	for (auto& _entity : all_entities) {
		if (_entity->get_component<CShape>().shape.has_ended()) {
			_entity->set_inactive();
			continue;
		}
		_entity->update_animation();
	}
}

void EntityManager::toggle_box_display() {
	display_bounding_boxes = !display_bounding_boxes;
}

void EntityManager::toggle_texture_display() {
	display_textures = !display_textures;
}

void EntityManager::draw_entities(sf::RenderWindow& game_window) const {
	// improve this logic

	for (auto& _entity : all_entities) {
		if(_entity->get_type() != EntityType::decoration) _entity->draw(game_window, display_textures, display_bounding_boxes);
	}
	for (auto& _entity : all_entities) {
		if(_entity->get_type() == EntityType::decoration) _entity->draw(game_window, display_textures, display_bounding_boxes);
	}
}