#include "Asset.hpp"

Asset::Asset() {}

void Asset::add_texture(const std::string _texture_name, const sf::Texture _texture_image) {
    textures_map[_texture_name] = _texture_image;
}

const sf::Texture& Asset::get_texture(const std::string& texture_name) const {
    return textures_map.at(texture_name);
}

void Asset::add_animation(const std::string _animation_name, const Animation _animation) {
    animations_map[_animation_name] = _animation;
}

Animation Asset::get_animation(const std::string& animation_name) const {
    return animations_map.at(animation_name);
}