#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

std::vector<std::string> line_parser(std::string& _line);
sf::Vector2f grid_to_mid_coord(const sf::Vector2f& _top_left_coord, const sf::Vector2f& _scale, const sf::Vector2f& _unscaled_size);
void redirect_stderr(const std::ofstream& _error_file);

template<class T>
sf::Vector2<T> vector_pairwise_product(const sf::Vector2<T>& _a, const sf::Vector2<T>& _b) {
    return sf::Vector2<T>(_a.x * _b.x, _a.y * _b.y);
}