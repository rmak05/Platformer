#include <format>
#include <iostream>
#include <utility>
#include "asset_manager.hpp"

void asset_manager::add_texture(const std::string& _name, const std::string& _path){
    sf::Texture texture;
    if(!texture.loadFromFile(_path)){
        std::cerr << std::format(
            "Unable to load the texture {} from {}\n",
            _name,
            _path
        );
        return;
    }

    textures.insert_or_assign(_name, std::move(texture));
}

void asset_manager::add_font(const std::string& _name, const std::string& _path){
    std::unique_ptr<sf::Font> font_ptr = std::make_unique<sf::Font>();
    if(!font_ptr->openFromFile(_path)){
        std::cerr << std::format(
            "Unable to load the font {} from {}\n",
            _name,
            _path
        );
        return;
    }

    fonts.insert_or_assign(_name, std::move(font_ptr));
}


// void asset_manager::add_animation(const std::vector<std::string>& _args){
//     animations.emplace(
//         std::piecewise_construct,
//         std::forward_as_tuple(_args[1]),
//         std::forward_as_tuple(_args[1],
//             get_texture(_args[2]),
//             std::stof(_args[3]),
//             std::stof(_args[4]),
//             static_cast<unsigned>(std::stoi(_args[5])),
//             static_cast<unsigned>(std::stoi(_args[6])),
//             static_cast<unsigned>(std::stoi(_args[7])),
//             static_cast<bool>(std::stoi(_args[8]))
//         )
//     );
// }

/*
TODO:
improve add_animation after improving animation class
*/
