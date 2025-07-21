#include "Entity.hpp"

Entity::Entity() {
	active	= false;
	id		= 0u;
	type	= EntityType::_default;
}

Entity::Entity(const unsigned _id, const EntityType _type) {
	active	= true;
	id		= _id;
	type	= _type;
}

bool Entity::is_active() const {
	return active;
}

void Entity::set_inactive() {
	active = false;
}

const unsigned Entity::get_id() const {
	return id;
}

const EntityType Entity::get_type() const {
	return type;
}

void Entity::transform() {
	auto& _cmotion				= get_component<CMotion>();
	_cmotion.velocity			+= _cmotion.acceleration;

	auto& _ctransform			= get_component<CTransform>();
	_ctransform.prev_position	= _ctransform.curr_position;
	_ctransform.curr_position	+= _cmotion.velocity;

	auto& _cshape				= get_component<CShape>();
	_cshape.set_position(_ctransform.curr_position);

	auto& _cboundingbox			= get_component<CBoundingBox>();
	_cboundingbox.set_position(_ctransform.curr_position);
}

void Entity::transform_after_collision() {
	auto& _ctransform			= get_component<CTransform>();

	auto& _cshape				= get_component<CShape>();
	_cshape.set_position(_ctransform.curr_position);

	auto& _cboundingbox			= get_component<CBoundingBox>();
	_cboundingbox.set_position(_ctransform.curr_position);
}

void Entity::update_animation() {
	auto& _cshape = get_component<CShape>();
	_cshape.update_animation();
}

void Entity::draw(sf::RenderWindow& game_window, bool display_shape, bool display_box) const {
	if (has_component<CShape>()) {
		auto& _cshape = get_component<CShape>();
		_cshape.draw(game_window, display_shape);
	}

	if (has_component<CBoundingBox>()) {
		auto& _cboundingbox = get_component<CBoundingBox>();
		_cboundingbox.draw(game_window, display_box);
	}
}