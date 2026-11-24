#ifndef PLATFORMER_ENTITY_HPP
#define PLATFORMER_ENTITY_HPP

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <utility>

#include <SFML/Graphics.hpp>

#include "component.hpp"
// #include "Debug.hpp"

class entity;

typedef std::tuple<
	ctransform,
	cvisual,
	cbounding_box,
	cmotion,
	cinput
> component_tuple;
typedef std::shared_ptr<entity> entity_ptr;

enum class entity_type : std::uint8_t{
	player,
	tile,
	decoration,
	bullet,
	enemy,
    notset,
    _count
};

class entity{
private:
	// friend class EntityManager;

	component_tuple all_components;

	entity() = default; // I expect this to fail as cvisual doesn't have a default constructor
	entity(const std::uint32_t _id, const entity_type _type);

    template<typename T>
	const T& get_component_helper() const;

public:
	bool active{false};
	entity_type type{entity_type::notset};
	std::uint32_t id{0};

	template<typename T, typename... Targs>
	T& set_component(Targs&&... _args);
	template<typename T>
	T& get_component();
	template<typename T>
	const T& get_component() const;
	template<typename T>
	bool has_component() const;
	template<typename T>
	void remove_component();

	void transform();
	void transform_after_collision();
	void update_animation();
	void draw(sf::RenderWindow& _window, bool display_shape, bool display_box) const;
};

template<typename T, typename... Targs>
T& entity::set_component(Targs&&... _args){
	T& comp = std::get<T>(all_components);
	comp = T(std::forward<Targs>(_args)...);
	comp.active = true;

	return comp;
}

template<typename T>
const T& entity::get_component_helper() const{
    if(!has_component<T>()){
		throw std::runtime_error("Tried to access a component which the entity doesn't contain.");
	}
	return std::get<T>(all_components);
}

template<typename T>
T& entity::get_component(){
    return const_cast<T&>(std::as_const(*this).get_component_helper<T>());
}

template<typename T>
const T& entity::get_component() const{
    return get_component_helper<T>();
}

template<typename T>
inline bool entity::has_component() const{
	return std::get<T>(all_components).active;
}

template<typename T>
inline void entity::remove_component(){
	get_component<T>() = T();
}

#endif // PLATFORMER_ENTITY_HPP
