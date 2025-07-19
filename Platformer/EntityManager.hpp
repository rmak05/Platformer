#pragma once

#include <vector>
#include "Entity.hpp"
#include "Collision.hpp"
#include "Debug.hpp"

class EntityManager {
private:
	int										entity_count;	// add a way to avoid incremental counter
	std::vector<entity_ptr>					all_entities;
	std::vector<std::vector<entity_ptr>>	sorted_entities; 
	std::vector<entity_ptr>					entites_to_add;

public:
	EntityManager();

	void delete_inactive_entities(std::vector<entity_ptr>& entity_vec);
	entity_ptr add_entity(const EntityType _type);
	void delete_entity(entity_ptr& _entity);
	void update_entities();
	void transform_entities();
	void resolve_collisions();
	void update_animations();
	void toggle_box_display();
	void toggle_texture_display();
	void draw_entities(sf::RenderWindow& game_window) const;
};