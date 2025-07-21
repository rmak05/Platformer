#pragma once

enum class ActionName;
enum class ActionType;

class Action;

enum class ActionName {
	left,
	right,
	jump,
	up,
	down,
	shoot,
	quit,
	pause,
	debug_box,
	debug_texture,
	count,
	_default
};

enum class ActionType {
	start,
	end,
	count,
	_default
};

class Action {
private:
	ActionName name;
	ActionType type;

public:
	Action();
	Action(const ActionName _name, const ActionType _type);

	ActionName get_name() const;
	ActionType get_type() const;
};