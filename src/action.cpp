#include "action.hpp"

action::action(const action_name _name, const action_type _type) :
name(_name), type(_type){}

action_key::action_key(const input_type _type, const std::int32_t _key_code) :
type(_type), key_code(_key_code){}
