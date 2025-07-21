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

void EntityManager::resolve_collisions() {
	for (auto& _entity1 : all_entities) {
		if(!_entity1->is_active()) continue;

		for (auto& _entity2 : all_entities) {
			if(!_entity1->is_active()) break;
			if(!_entity2->is_active()) continue;
			if(_entity1->get_id() == _entity2->get_id()) continue;
			// TODO: remove these lines
			if(_entity1->get_type() == EntityType::bullet) break;
			if(_entity2->get_type() == EntityType::bullet) continue;

			sf::Vector2f prev_overlap = Collision::prev_overlap(_entity1, _entity2);
			sf::Vector2f curr_overlap = Collision::curr_overlap(_entity1, _entity2);

			if ((curr_overlap.x <= 0.0f) && (curr_overlap.y <= 0.0f)) continue;

			if		((prev_overlap.y > 0.0f) && (curr_overlap.x > 0.0f)) {
				if		(_entity1->get_type() == EntityType::player) {
					auto& _ctransform	= _entity1->get_component<CTransform>();
					float direction		= 0.0f;
					if(_ctransform.curr_position.x >= _ctransform.prev_position.x) direction = (-1.0f);
					else direction = 1.0f;
					_ctransform.curr_position.x += curr_overlap.x * direction;
				}
				else if (_entity2->get_type() == EntityType::player) {
					auto& _ctransform	= _entity2->get_component<CTransform>();
					float direction		= 0.0f;
					if(_ctransform.curr_position.x >= _ctransform.prev_position.x) direction = (-1.0f);
					else direction = 1.0f;
					_ctransform.curr_position.x += curr_overlap.x * direction;
				}
				else {

				}
			}
			else if ((prev_overlap.x > 0.0f) && (curr_overlap.y > 0.0f)) {
				if		(_entity1->get_type() == EntityType::player) {
					auto& _ctransform	= _entity1->get_component<CTransform>();
					float direction		= 0.0f;
					if(_ctransform.curr_position.y >= _ctransform.prev_position.y) direction = (-1.0f);
					else direction = 1.0f;
					_ctransform.curr_position.y += curr_overlap.y * direction;

					auto& _cmotion		= _entity1->get_component<CMotion>();
					_cmotion.velocity.y	= 0.0f;
				}
				else if (_entity2->get_type() == EntityType::player) {
					auto& _ctransform	= _entity2->get_component<CTransform>();
					float direction		= 0.0f;
					if(_ctransform.curr_position.y >= _ctransform.prev_position.y) direction = (-1.0f);
					else direction = 1.0f;
					_ctransform.curr_position.y += curr_overlap.y * direction;

					auto& _cmotion		= _entity2->get_component<CMotion>();
					_cmotion.velocity.y	= 0.0f;
				}
				else {

				}
			}

			_entity1->transform_after_collision();
			_entity2->transform_after_collision();
		}
	}
}

void EntityManager::update_animations() {
	for (auto& _entity : all_entities) {
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
		if(_entity->get_type() == EntityType::decoration) _entity->draw(game_window, display_textures, display_bounding_boxes);
	}
	for (auto& _entity : all_entities) {
		if(_entity->get_type() != EntityType::decoration) _entity->draw(game_window, display_textures, display_bounding_boxes);
	}
}