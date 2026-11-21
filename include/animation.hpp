#ifndef PLATFORMER_ANIMATION_HPP
#define PLATFORMER_ANIMATION_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class animation{
public:
    typedef std::uint16_t small_int;

    struct frame{
        sf::Vector2<small_int> position;
        sf::Vector2<small_int> size;

        frame() = default;
        frame(const sf::Vector2<small_int> _position, const sf::Vector2<small_int> _size);
    };

private:
    std::string name;
    sf::Sprite sprite;
    std::vector<frame> frames; // while loading textures, take its block_size as input as well
                               // sprite sheet could have block size of 16px while game block is 64px
                               // these frame values should be wrt to 16px, normalize this at input stage only
                               // the config file can contain coordinates like 0, 1, 2 but after normalization,
                               // these values must be 0, 16, 32 . Also instead of using
                               // GAME_TEXTURE_BLOCK_SIZE, expected block size can also be taken in the input,
                               //so we are basically taking scale as input
    small_int curr_frame_index{0};
    small_int frame_duration{1}; // in frames (in game loop frames like 60, 120)
    small_int clock{0};
    bool looping{true};
    bool finished{false};

    void set_frame();

public:
    animation() = default;
    animation(
        const std::string& _name,
        const sf::Texture& _texture,
        const float _texture_scale,
        const bool _looping,
        const small_int _frame_duration,
        const std::vector<frame>& _frames
    );

    std::string get_name() const;
    bool has_finished() const;

    void set_position(const sf::Vector2f _position);
    void set_scale(const sf::Vector2f _scale);
    void update();
    void draw(sf::RenderWindow& _window) const;
};

inline std::string animation::get_name() const{
    return name;
}

inline bool animation::has_finished() const{
    return finished;
}

inline void animation::set_position(const sf::Vector2f _position){
    sprite.setPosition(_position);
}

inline void animation::set_scale(const sf::Vector2f _scale){
    sprite.setScale(_scale);
}

inline void animation::draw(sf::RenderWindow& _window) const{
    _window.draw(sprite);
}

#endif // PLATFORMER_ANIMATION_HPP
