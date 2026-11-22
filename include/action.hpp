#ifndef PLATFORMER_ACTION_HPP
#define PLATFORMER_ACTION_HPP

#include <cstdint>

enum class action_name : std::uint8_t{
    left,
    right,
    jump,
    up,
    down,
    shoot,
    quit,
    pause,
    debug_grid,
    debug_box,
    debug_texture,
    notset,
    _count
};

enum class action_type : std::uint8_t{
    start,
    end,
    notset,
    _count
};

enum class input_type : std::uint8_t{
    keyboard,
    mouse,
    notset,
    _count
};

class action{
private:
    action_name name = action_name::notset;
    action_type type = action_type::notset;

public:
    action() = default;
    action(const action_name _name, const action_type _type);

    action_name get_name() const;
    action_type get_type() const;
};

struct action_key{
    input_type type = input_type::notset;
    std::int32_t key_code = -1;

    action_key() = default;
    action_key(const input_type _type, const std::int32_t _key_code);

    bool operator<=>(const action_key& _that) const = default;
};

inline action_name action::get_name() const{
    return name;
}

inline action_type action::get_type() const{
    return type;
}

#endif // PLATFORMER_ACTION_HPP


/*
TODO:
revisit to check if action_key::key_code can be uint
revisit to check if everything in action_name is actually necessary
*/
