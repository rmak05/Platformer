#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Animation.hpp"

class Asset;

class Asset {
private:
	std::map<std::string, sf::Font>		fonts_map;
	std::map<std::string, sf::Texture>	textures_map;
	std::map<std::string, Animation>	animations_map;
	std::map<std::string, sf::Sound>	sounds_map;

public:
	Asset();

	void add_texture(const std::string _texture_name, const sf::Texture _texture);
	const sf::Texture& get_texture(const std::string& texture_name) const;
	void add_animation(const std::string _animation_name, const Animation _animation);
	Animation get_animation(const std::string& animation_name) const;
};