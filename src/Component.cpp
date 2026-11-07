#include "Component.hpp"

Component::Component() :
has(false) {}

Component::Component(const bool _has) :
has(_has) {}

CTransform::CTransform() :
Component() {}

CTransform::CTransform(const sf::Vector2f _position, const sf::Vector2f _scale) :
prev_position(_position), curr_position(_position), scale(_scale), Component() {}

CShape::CShape() :
Component() {}

CShape::CShape(const Animation _shape) :
shape(_shape), Component() {}

void CShape::set_position(sf::Vector2f _position) {
	shape.set_position(_position);
}

void CShape::set_scale(sf::Vector2f _scale) {
	shape.set_scale(_scale);
}

void CShape::update_animation() {
	shape.update();
}

void CShape::draw(sf::RenderWindow& game_window, bool display_shape) const {
	if (display_shape) {
		shape.draw(game_window);
	}
}

CBoundingBox::CBoundingBox() :
Component() {}

CBoundingBox::CBoundingBox(const sf::Vector2f& _size) :
box_size(_size), half_size(_size / 2.0f), Component() {
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

CMotion::CMotion() :
Component() {}

CMotion::CMotion(const sf::Vector2f _velocity, const sf::Vector2f _acceleration) :
velocity(_velocity), acceleration(_acceleration), Component() {}

CInput::CInput() :
left(false), right(false), Component() {}

CInput::CInput(const bool _left, const bool _right) :
left(_left), right(_right), Component() {}

CNPCPath::CNPCPath() :
Component() {}

CNPCPath::CNPCPath(const sf::Vector2f& _start_pos, const sf::Vector2f& _end_pos) :
start_pos(_start_pos), end_pos(_end_pos), Component() {}