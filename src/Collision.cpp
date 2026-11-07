#include "Collision.hpp"

Collision::Collision() {}

// not is_curr = is_prev
sf::Vector2f Collision::overlap_helper(const entity_ptr& _entity1, const entity_ptr& _entity2, bool is_curr) {
    if((!_entity1->has_component<CBoundingBox>()) || (!_entity2->has_component<CBoundingBox>())) return sf::Vector2f(0.0f, 0.0f);

    sf::Vector2f _pos1;
    sf::Vector2f _pos2;
    if (is_curr) {
        _pos1 = _entity1->get_component<CTransform>().curr_position;
        _pos2 = _entity2->get_component<CTransform>().curr_position;
    }
    else {
        _pos1 = _entity1->get_component<CTransform>().prev_position;
        _pos2 = _entity2->get_component<CTransform>().prev_position;
    }
    sf::Vector2f _half_box1 = _entity1->get_component<CBoundingBox>().half_size;
    sf::Vector2f _half_box2 = _entity2->get_component<CBoundingBox>().half_size;

    sf::Vector2f _delta = sf::Vector2f(std::fabsf(_pos1.x - _pos2.x), std::fabs(_pos1.y - _pos2.y));

    sf::Vector2f _overlap;
    _overlap.x = _half_box1.x + _half_box2.x - _delta.x;
    _overlap.y = _half_box1.y + _half_box2.y - _delta.y;

    return _overlap;
}

sf::Vector2f Collision::prev_overlap(const entity_ptr& _entity1, const entity_ptr& _entity2) {
    return overlap_helper(_entity1, _entity2, false);
}

sf::Vector2f Collision::curr_overlap(const entity_ptr& _entity1, const entity_ptr& _entity2) {
    return overlap_helper(_entity1, _entity2, true);
}