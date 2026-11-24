#ifndef PLATFORMER_COMPONENT_HPP
#define PLATFORMER_COMPONENT_HPP

#include <optional>

#include "animation.hpp"

class component{
public:
    bool active{false};

    component() = default;
    component(const bool _active);
};

class ctransform : public component{
public:
    sf::Vector2f prev_position;
    sf::Vector2f curr_position;
    sf::Vector2f scale;

    ctransform() = default;
    ctransform(const sf::Vector2f _position, const sf::Vector2f _scale);
};

class cvisual : public component{
public:
    std::optional<animation> drawable;

    cvisual() = default;
    cvisual(const animation& _animation);

    // void set_position(const sf::Vector2f _position);
    // void set_scale(const sf::Vector2f _scale);
    // void update_animation();
    // void draw(sf::RenderWindow& _window, const bool _display_shape) const;
};

class cbounding_box : public component{
public:
    sf::Vector2f box_size;
    sf::Vector2f half_box_size;
    sf::RectangleShape box;

    cbounding_box() = default;
    cbounding_box(const sf::Vector2f _box_size);

    // void set_position(const sf::Vector2f _position);
    // void draw(sf::RenderWindow& game_window, const bool _display) const;
};

class cmotion : public component{
public:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    cmotion() = default;
    cmotion(const sf::Vector2f _velocity, const sf::Vector2f _acceleration);
};

class cinput : public component{
public:
    bool left{false};
    bool right{false};

    cinput() = default;
    cinput(const bool _left, const bool _right);
};


/*
TODO:
check commented code and remove it
complete below components
*/

// class cnpc_path : public component{
// public:
// 	sf::Vector2f start_pos;
// 	sf::Vector2f end_pos;

// 	cnpc_path();
// 	cnpc_path(const sf::Vector2f _start_pos, const sf::Vector2f _end_pos);
// };

// class clifespan : public component{
// public:

// };

// class cscore : public component{
// public:

// };

#endif // PLATFORMER_COMPONENT_HPP
