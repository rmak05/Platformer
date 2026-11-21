#ifndef PLATFORMER_ASSET_MANAGER_HPP
#define PLATFORMER_ASSET_MANAGER_HPP

#include <map>
#include <string>
#include <stdexcept>
#include <vector>

#include <SFML/Graphics.hpp>

#include "animation.hpp"
#include "utils/logger.hpp"

/**
 * @brief A manager which stores and manages assets like textures, fonts and animations.
 */
class asset_manager{
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, animation> animations;

public:
    void add_texture(const std::string& _name, const std::string& _path);
    const sf::Texture& get_texture(const std::string& _name) const;
    void add_font(const std::string& _name, const std::string& _path);
    const sf::Font& get_font(const std::string& _name) const;
    void add_animation(
        const std::string& _name,
        const std::string& _texture_name,
        const float _texture_scale,
        const bool _looping,
        const animation::small_int _frame_duration,
        const std::vector<animation::frame>& _frames
    );
    animation get_animation(const std::string& _name) const;
};

inline const sf::Texture& asset_manager::get_texture(const std::string& _name) const{
    try{
        return textures.at(_name);
    }
    catch(const std::out_of_range&){
        logger::error("Missing texture {}", _name);
        throw;
    }
}

inline const sf::Font& asset_manager::get_font(const std::string& _name) const{
    try{
        return fonts.at(_name);
    }
    catch(const std::out_of_range&){
        logger::error("Missing font {}", _name);
        throw;
    }
}

inline animation asset_manager::get_animation(const std::string& _name) const{
    try{
        return animations.at(_name);
    }
    catch(const std::out_of_range&){
        logger::error("Missing animation {}", _name);
        throw;
    }
}

#endif // PLATFORMER_ASSET_MANAGER_HPP

/*
TODO: Explore trie instead of map to store assets. Or just keep std::map as it's pre-built
*/
