#include "Asset.hpp"

Asset::Asset() {}

void Asset::add_texture(const std::string& _texture_name, const std::string& _texture_path) {
    sf::Texture _texture;
    if (!_texture.loadFromFile(_texture_path)) {
        std::cerr << "Unable to load the texture " << _texture_name << " from " << _texture_path << std::endl;
    }

    textures_map[_texture_name] = std::move(_texture);
}

const sf::Texture& Asset::get_texture(const std::string& _texture_name) const {
    return textures_map.at(_texture_name);
}

void Asset::add_font(const std::string& _font_name, const std::string& _font_path) {
    sf::Font _font;
    if (!_font.loadFromFile(_font_path)) {
        std::cerr << "Unable to load the font " << _font_name << " from " << _font_path << std::endl;
    }

    fonts_map[_font_name] = std::move(_font);
}

const sf::Font& Asset::get_font(const std::string& _font_name) const {
    return fonts_map.at(_font_name);
}

void Asset::add_animation(const std::vector<std::string>& _args) {
    animations_map.emplace(std::piecewise_construct, std::forward_as_tuple(_args[1]), std::forward_as_tuple(_args[1], get_texture(_args[2]), std::stof(_args[3]), std::stof(_args[4]), static_cast<unsigned>(std::stoi(_args[5])), static_cast<unsigned>(std::stoi(_args[6])), static_cast<unsigned>(std::stoi(_args[7])), static_cast<bool>(std::stoi(_args[8]))));
}

const Animation& Asset::get_animation(const std::string& _animation_name) const {
    return animations_map.at(_animation_name);
}