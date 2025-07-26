#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Animation.hpp"

class Asset;

class Asset {
private:
	std::map<std::string, sf::Texture>	textures_map;
	std::map<std::string, sf::Font>		fonts_map;
	std::map<std::string, sf::Sound>	sounds_map;
	std::map<std::string, Animation>	animations_map;

public:
	Asset();

	void add_texture(const std::string& _texture_name, const std::string& _texture_path);
	const sf::Texture& get_texture(const std::string& _texture_name) const;
	void add_font(const std::string& _font_name, const std::string& _font_path);
	const sf::Font& get_font(const std::string& _font_name) const;
	void add_animation(const std::vector<std::string>& _args);
	const Animation& get_animation(const std::string& _animation_name) const;
};