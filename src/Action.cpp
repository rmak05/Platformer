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

ActionKey::ActionKey() {
	type = InputType::_default;
	code = (-1);
}

ActionKey::ActionKey(InputType _type, int _code) {
	type = _type;
	code = _code;
}

bool ActionKey::operator<(const ActionKey& _that) const {
	if (this->type != _that.type) return this->type < _that.type;
	return this->code < _that.code;
}

bool ActionKey::operator>(const ActionKey& _that) const {
	if (this->type != _that.type) return this->type > _that.type;
	return this->code > _that.code;
}

bool ActionKey::operator<=(const ActionKey& _that) const {
	if (this->type != _that.type) return this->type <= _that.type;
	return this->code <= _that.code;
}

bool ActionKey::operator>=(const ActionKey& _that) const {
	if (this->type != _that.type) return this->type >= _that.type;
	return this->code >= _that.code;
}

bool ActionKey::operator==(const ActionKey& _that) const {
	return ((this->type == _that.type) && (this->code == _that.code));
}

bool ActionKey::operator!=(const ActionKey& _that) const {
	return ((this->type != _that.type) || (this->code != _that.code));
}