#include "Animation.hpp"

Animation::Animation() {
    sprite_count    = 0u;
    duration        = 0u;
    curr_frame      = 0u;
    loop            = true;
    end             = false;
}

Animation::Animation(const std::string _name, const sf::Texture& _texture, const float _scale_x, const float _scale_y, const unsigned _num_rows, const unsigned _num_columns, const unsigned _duration, const bool _loop) : end(false) {
    name            = _name;
    size            = sf::Vector2u(_num_columns, _num_rows);
    sprite_count    = _num_rows * _num_columns;
    duration        = _duration;
    curr_frame      = sprite_count * duration - 1u;
    loop            = _loop;
    sprite_size     = sf::Vector2u(_texture.getSize().x / _num_columns, _texture.getSize().y / _num_rows);
    sprite.setTexture(_texture);
    sprite.setScale(_scale_x, _scale_y);
    sprite.setOrigin(static_cast<sf::Vector2f>(sprite_size) / 2.0f);
}

std::string Animation::get_name() const {
    return name;
}

sf::Sprite Animation::get_sprite() const {
    return sprite;
}

sf::Vector2f Animation::get_scale() const {
    return sprite.getScale();
}

sf::Vector2u Animation::get_size() const {
    return size;
}

sf::Vector2u Animation::get_sprite_size() const {
    return sprite_size;
}

sf::Vector2f Animation::get_scaled_size() const {
    sf::Vector2f _scale = sprite.getScale();

    return sf::Vector2f(sprite_size.x * _scale.x, sprite_size.y * _scale.y);
}

void Animation::set_position(sf::Vector2f _position) {
    sprite.setPosition(_position);
}

void Animation::set_position(float _x, float _y) {
    sprite.setPosition(_x, _y);
}

void Animation::set_scale(sf::Vector2f _scale) {
    sprite.setScale(_scale);
}

void Animation::set_scale(float _scale_x, float _scale_y) {
    sprite.setScale(_scale_x, _scale_y);
}

void Animation::update() {
    if (duration == 0u || end) return;

    int previous_sprite_number = curr_frame / duration;

    curr_frame++;
    curr_frame %= (sprite_count * duration);

    if (!loop && curr_frame == sprite_count * duration - 1u) {
        end = true;
    }

    int sprite_number = curr_frame / duration;
    if (sprite_number == previous_sprite_number) return;

    int rows                    = static_cast<int>(size.y);
    int columns                 = static_cast<int>(size.x);
    sf::Vector2i _sprite_size   = static_cast<sf::Vector2i>(sprite_size);

    sprite.setTextureRect(sf::IntRect((sprite_number % columns) * _sprite_size.x, (sprite_number / columns) * _sprite_size.y, _sprite_size.x, _sprite_size.y));
}

bool Animation::has_ended() const {
    return end;
}

void Animation::draw(sf::RenderWindow& game_window) const {
    game_window.draw(sprite);
}