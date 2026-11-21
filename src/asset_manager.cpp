#include <utility>

#include "asset_manager.hpp"
#include "utils/logger.hpp"

void asset_manager::add_texture(const std::string& _name, const std::string& _path){
    auto hint_ptr = textures.lower_bound(_name);

    if(hint_ptr != textures.end() && hint_ptr->first == _name){
        logger::warning("A texture with name {} already exists.", _name);
        return;
    }

    sf::Texture texture;
    if(!texture.loadFromFile(_path)){
        logger::warning("Unable to load the texture {} from {}", _name, _path);
        return;
    }

    textures.emplace_hint(hint_ptr, _name, std::move(texture));
}

void asset_manager::add_font(const std::string& _name, const std::string& _path){
    auto hint_ptr = fonts.lower_bound(_name);

    if(hint_ptr != fonts.end() && hint_ptr->first == _name){
        logger::warning("A font with name {} already exists.", _name);
        return;
    }

    sf::Font font;
    if(!font.openFromFile(_path)){
        logger::warning("Unable to load the font {} from {}", _name, _path);
        return;
    }

    fonts.emplace_hint(hint_ptr, _name, std::move(font));
}

void asset_manager::add_animation(
    const std::string& _name,
    const std::string& _texture_name,
    const float _texture_scale,
    const bool _looping,
    const animation::small_int _frame_duration,
    const std::vector<animation::frame>& _frames
){
    auto hint_ptr = animations.lower_bound(_name);

    if(hint_ptr != animations.end() && hint_ptr->first == _name){
        logger::warning("An animation with name {} already exists.", _name);
        return;
    }

    animations.emplace_hint(
        hint_ptr,
        std::piecewise_construct,
        std::forward_as_tuple(_name),
        std::forward_as_tuple(
            _name,
            get_texture(_texture_name),
            _texture_scale,
            _looping,
            _frame_duration,
            _frames
        )
    );
}
