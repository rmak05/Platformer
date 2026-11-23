#include "action.hpp"

action::action(const action_name _name, const action_type _type) :
name{_name}, type{_type}{}

action::key::key(const input_type _type, const std::int32_t _code) :
type{_type}, code{_code}{}
