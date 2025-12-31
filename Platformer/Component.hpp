#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Theme.hpp"
#include "Debug.hpp"

class Component;
class CTransform;
class CShape;
class CBoundingBox;
class CMotion;
class CInput;
class CNPCPath;
class CLifespan;
class CScore;

class Component {
public:
	bool has;

	Component();
	Component(const bool _has);
};

class CTransform : public Component {
public:
	sf::Vector2f prev_position;
	sf::Vector2f curr_position;
	sf::Vector2f scale;

	CTransform();
	CTransform(const sf::Vector2f _position, const sf::Vector2f _scale);
};

class CShape : public Component {
public:
	Animation shape;

	CShape();
	CShape(const Animation _shape);

	void set_position(sf::Vector2f _position);
	void set_scale(sf::Vector2f _scale);
	void update_animation();
	void draw(sf::RenderWindow& game_window, bool display_shape) const;
};

class CBoundingBox : public Component {
public:
	sf::Vector2f box_size;
	sf::Vector2f half_size;
	sf::RectangleShape box;

	CBoundingBox();
	CBoundingBox(const sf::Vector2f& _size);

	void set_position(sf::Vector2f _position);
	void draw(sf::RenderWindow& game_window, bool display_box) const;
};

class CMotion : public Component {
public:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	CMotion();
	CMotion(const sf::Vector2f _velocity, const sf::Vector2f _acceleration);
};

class CInput : public Component {
public:
	bool left;
	bool right;

	CInput();
	CInput(const bool _left, const bool _right);
};

class CNPCPath : public Component {
public:
	sf::Vector2f start_pos;
	sf::Vector2f end_pos;

	CNPCPath();
	CNPCPath(const sf::Vector2f& _start_pos, const sf::Vector2f& _end_pos);
};

class CLifespan : public Component {
public:
	
};

class CScore : public Component {
public:
	
};