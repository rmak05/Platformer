#pragma once

#include <tuple>
#include <utility>
#include "Component.hpp"
#include "Debug.hpp"

enum class EntityType;

class Entity;

typedef std::tuple<
	CTransform,
	CShape,
	CBoundingBox,
	CMotion,
	CInput,
	CLifespan,
	CScore
> ComponentTuple;
typedef std::shared_ptr<Entity> entity_ptr;

enum class EntityType {
	player,
	tile,
	decoration,
	bullet,
	count,
	_default
};

class Entity {
private:
	friend class EntityManager;

	bool			active;
	unsigned		id;
	EntityType		type;
	ComponentTuple	all_components;

	Entity();
	Entity(const unsigned _id, const EntityType _type);

public:
	template<typename T, typename... TArgs>
	T& set_component(TArgs&&... args);
	template<typename T>
	T& get_component();
	template<typename T>
	const T& get_component() const;
	template<typename T>
	bool has_component() const;
	template<typename T>
	void remove_component();

	bool is_active() const;
	void set_inactive();
	const unsigned get_id() const;
	const EntityType get_type() const;
	void transform();
	void transform_after_collision();
	void update_animation();
	void draw(sf::RenderWindow& game_window, bool display_shape, bool display_box) const;
};

template<typename T, typename... TArgs>
T& Entity::set_component(TArgs&&... args) {
	T& _component = std::get<T>(all_components);
	_component = T(std::forward<TArgs>(args)...);
	_component.has = true;

	return _component;
}

template<typename T>
T& Entity::get_component() {
	return std::get<T>(all_components);
}

template<typename T>
const T& Entity::get_component() const {
	return std::get<T>(all_components);
}

template<typename T>
bool Entity::has_component() const{
	return get_component<T>().has;
}

template<typename T>
void Entity::remove_component() {
	get_component<T>() = T();
}