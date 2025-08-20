#include "Helper.hpp"

std::vector<std::string> line_parser(std::string& _line){
	std::vector<std::string> line_components;

	if ((_line.size() >= 2llu) && (_line[0] == '/') && (_line[1] == '/')) {
		line_components.push_back("Comment");

		return line_components;
	}

	std::string component;
	int index = 0, line_len = static_cast<int>(_line.size());

	while (index < line_len) {
		component.clear();

		while ((index < line_len) && (_line[index] != ' ') && (_line[index] != '\t')) {
			component.push_back(_line[index++]);
		}
		index++;

		if(component.empty()) continue;

		line_components.push_back(component);
	}

	return line_components;
}

sf::Vector2f grid_to_mid_coord(const sf::Vector2f& _top_left_coord, const sf::Vector2f& _scale, const sf::Vector2f& _unscaled_size) {
	sf::Vector2f scaled_size = sf::Vector2f(_unscaled_size.x * _scale.x, _unscaled_size.y * _scale.y);
	return (_top_left_coord * 64.0f + scaled_size / 2.0f);
}

void redirect_stderr(const std::ofstream& _error_file) {
	std::cerr.rdbuf(_error_file.rdbuf());
}