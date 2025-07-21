#include "Component.hpp"

Component::Component() {
	has = false;
}

CTransform::CTransform() : Component() {}

CTransform::CTransform(const sf::Vector2f _position) : Component() {
	prev_position = _position;
	curr_position = _position;
}

CTransform::CTransform(float _x, float _y) : Component() {
	prev_position.x = _x;
	prev_position.y = _y;

	curr_position	= prev_position; 
}

CShape::CShape() : Component() {}

CShape::CShape(const Animation _shape) : Component() {
	shape			= _shape;
}

void CShape::set_position(sf::Vector2f _position) {
	shape.set_position(_position);
}

void CShape::update_animation() {
	shape.update();
}

void CShape::draw(sf::RenderWindow& game_window, bool display_shape) const {
	if (display_shape) {
		shape.draw(game_window);
	}
}

CBoundingBox::CBoundingBox() : Component() {}

CBoundingBox::CBoundingBox(const sf::Vector2f& _size) : Component() {
	box_size	= _size;
	half_size	= box_size / 2.0f;
	box.setSize(_size);
	box.setOrigin(half_size);
	box.setFillColor(sf::Color(0xffffff00));
	box.setOutlineColor(BOX_COLOR);
	box.setOutlineThickness(BOX_THICKNESS);
}

void CBoundingBox::set_position(sf::Vector2f _position) {
	box.setPosition(_position);
}

void CBoundingBox::draw(sf::RenderWindow& game_window, bool display_box) const {
	if (display_box) {
		game_window.draw(box);
	}
}

CMotion::CMotion() : Component() {}

CMotion::CMotion(const sf::Vector2f _velocity, const sf::Vector2f _acceleration) : Component() {
	velocity		= _velocity;
	acceleration	= _acceleration;
}