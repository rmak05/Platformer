#ifndef PLATFORMER_ASSET_MANAGER_HPP
#define PLATFORMER_ASSET_MANAGER_HPP

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
// #include "Animation.hpp"

/**
 * @brief A manager which stores and manages assets like textures, fonts and animations.
 */
class asset_manager{
private:
	std::map<std::string, sf::Texture>               textures;
	std::map<std::string, std::unique_ptr<sf::Font>> fonts;
	// std::map<std::string, Animation>                 animations;

public:
	void add_texture(const std::string& _name, const std::string& _path);
	const sf::Texture& get_texture(const std::string& _name) const;
	void add_font(const std::string& _name, const std::string& _path);
	const sf::Font& get_font(const std::string& _name) const;
	// void add_animation(const std::vector<std::string>& _args);
	// const Animation& get_animation(const std::string& _name) const;
};

inline const sf::Texture& asset_manager::get_texture(const std::string& _name) const{
    return textures.at(_name);
}

inline const sf::Font& asset_manager::get_font(const std::string& _name) const{
    return *fonts.at(_name);
}

// inline const Animation& asset_manager::get_animation(const std::string& _name) const{
//     return animations.at(_name);
// }

#endif // PLATFORMER_ASSET_MANAGER_HPP
