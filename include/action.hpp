#ifndef PLATFORMER_ACTION_HPP
#define PLATFORMER_ACTION_HPP

#include <compare>
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
public:
    struct key{
        input_type type{input_type::notset};
        std::int32_t code{-1};

        key() = default;
        key(const input_type _type, const std::int32_t _code);

        std::strong_ordering operator<=>(const key& _that) const = default;
    };

private:
    action_name name{action_name::notset};
    action_type type{action_type::notset};

public:
    action() = default;
    action(const action_name _name, const action_type _type);

    action_name get_name() const;
    action_type get_type() const;
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
revisit to check if key::code can be uint
revisit to check if everything in action_name is actually necessary
*/
