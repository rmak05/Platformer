#include "config.hpp"
#include "component.hpp"

component::component(const bool _has) :
has{_has}{}

ctransform::ctransform(const sf::Vector2f _position, const sf::Vector2f _scale) :
prev_position{_position}, curr_position{_position}, scale{_scale}{}

cvisual::cvisual(const animation& _animation) :
drawable{_animation}{}

// void cvisual::set_position(sf::Vector2f _position) {
// 	shape.set_position(_position);
// }

// void cvisual::set_scale(sf::Vector2f _scale) {
// 	shape.set_scale(_scale);
// }

// void cvisual::update_animation() {
// 	shape.update();
// }

// void cvisual::draw(sf::RenderWindow& game_window, bool display_shape) const {
// 	if (display_shape) {
// 		shape.draw(game_window);
// 	}
// }

cbounding_box::cbounding_box(const sf::Vector2f _box_size) :
box_size{_box_size}, half_box_size{_box_size / 2.0f}{
    box.setSize(box_size);
    box.setOrigin(half_box_size);
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineColor(BOUNDING_BOX_COLOR);
    box.setOutlineThickness(BOUNDING_BOX_THICKNESS);
}

// void cbounding_box::set_position(sf::Vector2f _position) {
// 	box.setPosition(_position);
// }

// void cbounding_box::draw(sf::RenderWindow& game_window, bool display_box) const {
// 	if (display_box) {
// 		game_window.draw(box);
// 	}
// }

cmotion::cmotion(const sf::Vector2f _velocity, const sf::Vector2f _acceleration) :
velocity{_velocity}, acceleration{_acceleration}{}

cinput::cinput(const bool _left, const bool _right) :
left{_left}, right{_right}{}
