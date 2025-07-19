#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

std::vector<std::string> line_parser(std::string& line);
sf::Vector2f grid_to_mid_coord(const sf::Vector2f& top_left_coord, const Animation& _animation);
void redirect_stderr(const std::ofstream& error_file);