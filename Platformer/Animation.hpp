#pragma once

#include <SFML/Graphics.hpp>

class Animation;

class Animation {
private:
	sf::Sprite		sprite;			// Maybe can use rectangle instead
	std::string		name;			// can use enum
	sf::Vector2u	size;			// size of the sprite sheet (columns x rows)
	sf::Vector2u	sprite_size;	// size of each sprite in pixels (assuming all sprites have equal size)
	unsigned		sprite_count;
	unsigned		duration;		// number of frames before changing current sprite
	unsigned		curr_frame;		// total frames = sprite_count * speed
	bool			loop;
	bool			end;

public:
	Animation();
	Animation(const std::string _name, const sf::Texture& _texture, const float _scale_x, const float _scale_y, const unsigned _num_rows, const unsigned _num_columns, const unsigned _duration, const bool _loop);

	std::string get_name() const;
	sf::Sprite get_sprite() const;
	sf::Vector2f get_scale() const;
	sf::Vector2u get_size() const;
	sf::Vector2u get_sprite_size() const;
	void set_position(sf::Vector2f _position);
	void set_position(float _pos_x, float _pos_y);
	void set_scale(sf::Vector2f _scale);
	void set_scale(float _scale_x, float _scale_y);
	void update();
	bool has_ended() const;
	void draw(sf::RenderWindow& game_window) const;
};