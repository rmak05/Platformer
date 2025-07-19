#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#define print(x)					\
if(debug::is_active()){				\
	std::cerr << #x << " : ";		\
	debug::print_helper(x);			\
	std::cerr << std::endl;			\
}

namespace debug {
	extern bool active;

	extern bool show_grid;
	extern std::vector<sf::VertexArray> grid;
	extern std::vector<sf::Text> grid_coord;
	extern sf::Font grid_font;
	extern sf::Color grid_color;
	extern sf::Color grid_coord_color;
	extern int side_length;
	extern unsigned coord_text_size;

	void activate();
	void deactivate();
	void update();
	bool is_active();

	void draw(sf::RenderWindow& window);

	void print_helper(const int i);
	void print_helper(const unsigned ui);
	void print_helper(const long li);
	void print_helper(const unsigned long uli);
	void print_helper(const long long lli);
	void print_helper(const unsigned long long ulli);
	void print_helper(const float f);
	void print_helper(const double d);
	void print_helper(const long double ld);
	void print_helper(const bool b);
	void print_helper(const char c);
	void print_helper(const unsigned char c);
	void print_helper(const std::string s);
	void print_helper(const char *t);
	template<typename T> 
	void print_helper(const sf::Vector2<T> v2);
	template<typename T, typename V> 
	void print_helper(const std::pair<T, V> p);
	template<typename T> 
	void print_helper(const std::vector<T> v);
	template<typename T>
	void print_helper(const std::set<T> st);
	template<typename T> 
	void print_helper(const std::multiset<T> mst);
	template<typename T, typename V> 
	void print_helper(const std::map<T, V> mp);
	template<typename T, typename V> 
	void print_helper(const std::multimap<T, V> mmp);
	template<typename T>
	void print_helper(const std::unordered_set<T> st);
	template<typename T, typename V> 
	void print_helper(const std::unordered_map<T, V> mp);
};

template<typename T> 
void debug::print_helper(const sf::Vector2<T> v2) {
	std::cerr << "{";
	print_helper(v2.x);
	std::cerr << ", ";
	print_helper(v2.y);
	std::cerr << "}";
}

template<typename T, typename V> 
void debug::print_helper(const std::pair<T, V> p) {
	std::cerr << "{";
	print_helper(p.first);
	std::cerr << ", ";
	print_helper(p.second);
	std::cerr << "}";
}

template<typename T> 
void debug::print_helper(const std::vector<T> v) {
	std::cerr << "[ "; 
	for (T t : v) {
		print_helper(t); 
		std::cerr << " ";
	} 
	std::cerr << "]";
}

template<typename T>
void debug::print_helper(const std::set<T> st) {
	std::cerr << "[ "; 
	for (T t : st) {
		print_helper(t); 
		std::cerr << " ";
	} 
	std::cerr << "]";
}

template<typename T> 
void debug::print_helper(const std::multiset<T> mst) {
	std::cerr << "[ "; 
	for (T t : mst) {
		print_helper(t); 
		std::cerr << " ";
	} 
	std::cerr << "]";
}

template<typename T, typename V> 
void debug::print_helper(const std::map<T, V> mp) {
	std::cerr << "[ "; 
	for (std::pair<T, V> p : mp) {
		print_helper(p);
		std::cerr << " ";
	} 
	std::cerr << "]";
}

template<typename T, typename V> 
void debug::print_helper(const std::multimap<T, V> mmp) {
	std::cerr << "[ "; 
	for (std::pair<T, V> p : mmp) {
		print_helper(p);
		std::cerr << " ";
	} 
	std::cerr << "]";
}

template<typename T>
void debug::print_helper(const std::unordered_set<T> st) {
	std::cerr << "[ "; 
	for (T t : st) {
		print_helper(t); 
		std::cerr << " ";
	} 
	std::cerr << "]";
}

template<typename T, typename V> 
void debug::print_helper(const std::unordered_map<T, V> mp) {
	std::cerr << "[ "; 
	for (std::pair<T, V> p : mp) {
		print_helper(p);
		std::cerr << " ";
	} 
	std::cerr << "]";
}