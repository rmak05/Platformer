#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Collision;

class Collision {
private:
    static sf::Vector2f overlap_helper(const entity_ptr& _entity1, const entity_ptr& _entity2, bool is_curr);

public:
    Collision();

    static sf::Vector2f prev_overlap(const entity_ptr& _entity1, const entity_ptr& _entity2);
    static sf::Vector2f curr_overlap(const entity_ptr& _entity1, const entity_ptr& _entity2);
};