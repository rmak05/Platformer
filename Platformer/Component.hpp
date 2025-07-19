#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Theme.hpp"

class Component;
class CTransform;
class CShape;
class CBoundingBox;
class CMotion;
class CLifespan;
class CInput;
//class CScore;

class Component {
public:
	bool has;

	Component();
};

class CTransform : public Component {
public:
	sf::Vector2f prev_position;
	sf::Vector2f curr_position;

	CTransform();
	CTransform(const sf::Vector2f _position);
	CTransform(float _x, float _y);
};

class CShape : public Component {
public:
	Animation shape;
	bool display_shape;

	CShape();
	CShape(const Animation _shape);

	void set_position(sf::Vector2f _position);
	void update_animation();
	void draw(sf::RenderWindow& game_window) const;
};

class CBoundingBox : public Component {
public:
	sf::Vector2f box_size;
	sf::Vector2f half_size;
	sf::RectangleShape box;
	bool display_box;

	CBoundingBox();
	CBoundingBox(const sf::Vector2f& _size);

	void set_position(sf::Vector2f _position);
	void draw(sf::RenderWindow& game_window) const;
};

class CMotion : public Component {
public:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	CMotion();
	CMotion(const sf::Vector2f _velocity, const sf::Vector2f _acceleration);
};

class CLifespan : public Component {
public:
	
};

class CInput : public Component {
public:
	
};

//class CScore : public Component {
//public:
//	
//};