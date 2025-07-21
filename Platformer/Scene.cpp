#include "Scene.hpp"

Scene::Scene(EntityManager& _entity_manager, SceneId _id, Asset& _assets) : entity_manager(_entity_manager), all_assets(_assets) {
	id			= _id;
	is_paused	= false;
	has_ended	= false;
}

void Scene::initialise() {
	entity_manager = EntityManager();

	is_paused	= false;
	has_ended	= false;
}

void Scene::register_action(const int _key, const ActionName _action_name) {
	action_map[_key] = _action_name;
}

ActionName Scene::find_action(int _key) {
	if(action_map.find(_key) != action_map.end()) return action_map[_key];
	else return ActionName::_default;
}

void Scene::transform_entities() {
	entity_manager.transform_entities();
}

entity_ptr Scene::add_entity(const EntityType _type) {
	return entity_manager.add_entity(_type);
}

void Scene::delete_entity(entity_ptr& _entity) {
	entity_manager.delete_entity(_entity);
}

void Scene::update_entities() {
	entity_manager.update_entities();
}

void Scene::resolve_collisions() {
	entity_manager.resolve_collisions();
}

void Scene::update_animations() {
	entity_manager.update_animations();
}

void Scene::draw_entities(sf::RenderWindow& game_window) const {
	entity_manager.draw_entities(game_window);
}