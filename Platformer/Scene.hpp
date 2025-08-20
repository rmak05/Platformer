#pragma once

#include <vector>
#include <map>
#include "EntityManager.hpp"
#include "Action.hpp"
#include "Asset.hpp"

enum class SceneId;

class Scene;

typedef std::shared_ptr<Scene> scene_ptr;

enum class SceneId {
	menu,
	level,
	count,
	_default
};

class Scene {
protected:
	SceneId							id;
	EntityManager&					entity_manager;
	bool							is_paused;
	bool							has_ended;
	std::map<ActionKey, ActionName>	action_map;		// input to action name
	Asset&							all_assets;
	std::vector<sf::View>			all_views;
	// The idea is to store multiple views, but map could be more useful as different view might have a different purpose and we need to make specific updates to specific views, can make enums to aid this

public:
	Scene(EntityManager& _entity_manager, SceneId _id, Asset& _assets);

	virtual void initialise();

	void register_action(const ActionKey _key, const ActionName _action_name);
	ActionName find_action(const ActionKey _key);
	virtual void do_action(Action _action) = 0;

	entity_ptr add_entity(const EntityType _type);
	void delete_entity(entity_ptr& _entity);
	void update_added_entities();
	void update_deleted_entities();
	virtual void transform_entities();
	void resolve_collisions();

	void update_animations();
	virtual void update_and_set_views(sf::RenderWindow& game_window) = 0;
	void draw_entities(sf::RenderWindow& game_window) const;
};