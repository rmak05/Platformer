#include "Helper.hpp"

std::vector<std::string> line_parser(std::string& line){
	std::vector<std::string> line_components;

	if ((line.size() >= 2llu) && (line[0] == '/') && (line[1] == '/')) {
		line_components.push_back("Comment");

		return line_components;
	}

	std::string component;
	int index = 0, line_len = static_cast<int>(line.size());

	while (index < line_len) {
		component.clear();

		while ((index < line_len) && (line[index] != ' ') && (line[index] != '\t')) {
			component.push_back(line[index++]);
		}
		index++;

		if(component.empty()) continue;

		line_components.push_back(component);
	}

	return line_components;
}

sf::Vector2f grid_to_mid_coord(const sf::Vector2f& top_left_coord, const Animation& _animation) {
	return (top_left_coord * 64.0f + static_cast<sf::Vector2f>(_animation.get_scaled_size()) / 2.0f);
}

void redirect_stderr(const std::ofstream& error_file) {
	std::cerr.rdbuf(error_file.rdbuf());
}