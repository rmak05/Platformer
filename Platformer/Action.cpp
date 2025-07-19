#include "Action.hpp"

Action::Action() {
	name = ActionName::_default;
	type = ActionType::_default;
}

Action::Action(const ActionName _name, const ActionType _type) {
	name = _name;
	type = _type;
}

ActionName Action::get_name() const {
	return name;
}

ActionType Action::get_type() const {
	return type;
}