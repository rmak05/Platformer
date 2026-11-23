#include <cmath>
#include <stdexcept>

#include "animation.hpp"

animation::frame::frame(const sf::Vector2<small_int> _position, const sf::Vector2<small_int> _size) :
position{_position}, size{_size}{}

void animation::set_frame(){
    frame& curr_frame = frames[curr_frame_index];

    sprite.setTextureRect(sf::IntRect(
        static_cast<sf::Vector2i>(curr_frame.position),
        static_cast<sf::Vector2i>(curr_frame.size)
    ));
    sprite.setOrigin(sprite.getLocalBounds().size / 2.0f);
}

animation::animation(
    const std::string& _name,
    const sf::Texture& _texture,
    const float _texture_scale,
    const bool _looping,
    const small_int _frame_duration,
    const std::vector<frame>& _frames
) : name(_name), sprite{_texture}, frames(_frames), frame_duration{_frame_duration}, looping{_looping}{
    if(!std::isfinite(_texture_scale) || !_texture_scale){
        throw std::invalid_argument("`_texture_scale` must be finite and non-zero.");
    }
    if(_frame_duration <= 0) throw std::invalid_argument("`_frame_duration` must be positive.");
    if(frames.empty()) throw std::invalid_argument("`_frames` cannot be empty.");

    set_frame();
    sprite.setScale({_texture_scale, _texture_scale});
}

void animation::update(){
    if(finished) return;

    if(clock >= frame_duration){
        if(!looping && curr_frame_index == static_cast<small_int>(frames.size()) - 1){
            finished = true;
            return;
        }

        clock = 0;
        curr_frame_index = (curr_frame_index + 1) % frames.size();
    }

    set_frame();
    clock++;
}
