#include "Debug.hpp"

namespace debug {
	bool active = false;
	bool show_grid;
	std::vector<sf::VertexArray> grid;
	std::vector<sf::Text> grid_coord;
	sf::Font grid_font;
	sf::Color grid_color;
	sf::Color grid_coord_color;
	int side_length;
	unsigned coord_text_size;

	void activate() {
		active = true;
		show_grid = false;
		grid.clear();
		grid_coord.clear();
		grid_font.loadFromFile("Assets/Fonts/NotoSans_Regular.ttf");
		grid_color = grid_coord_color = sf::Color(255, 0, 0, 255);
		side_length = 64;
		coord_text_size = 15u;

		for (int i = 0; i < 3000; i += side_length) {
			sf::VertexArray line(sf::Lines, 2);
			line[0] = sf::Vertex(sf::Vector2f(i * 1.0f, 0.0f), grid_color);
			line[1] = sf::Vertex(sf::Vector2f(i * 1.0f, 2000.0f), grid_color);

			grid.push_back(line);
		}
		for (int i = 0; i < 2000; i += side_length) {
			sf::VertexArray line(sf::Lines, 2);
			line[0] = sf::Vertex(sf::Vector2f(0.0f, i * 1.0f), grid_color);
			line[1] = sf::Vertex(sf::Vector2f(3000.0f, i * 1.0f), grid_color);

			grid.push_back(line);
		}
		for (int i = 0; i < 3000; i += side_length) {
			for (int j = 0; j < 2000; j += side_length) {
				sf::Text _text;
				std::string coord = "(" + std::to_string(i / side_length) + ", " + std::to_string(j / side_length) + ")";
				_text.setFont(grid_font);
				_text.setFillColor(grid_coord_color);
				_text.setCharacterSize(coord_text_size);
				_text.setPosition(i * 1.0f, j * 1.0f);
				_text.setString(coord);
				_text.setStyle(sf::Text::Bold);

				grid_coord.push_back(_text);
			}
		}
	}

	void deactivate() {
		active = false;
	}

	void update() {
		if(!active) return;

		show_grid = (!show_grid);
	}

	bool is_active() {
		return active;
	}

	void draw(sf::RenderWindow& window) {
		if(!active) return;

		if (show_grid) {
			for (auto& itr : debug::grid) window.draw(itr);
			for (auto& itr : debug::grid_coord) window.draw(itr);
		}
	}

	void print_helper(const int i) {
		std::cerr << i;
	}

	void print_helper(const unsigned ui) {
		std::cerr << ui;
	}

	void print_helper(const long li) {
		std::cerr << li;
	}

	void print_helper(const unsigned long uli) {
		std::cerr << uli;
	}

	void print_helper(const long long lli) {
		std::cerr << lli;
	}

	void print_helper(const unsigned long long ulli) {
		std::cerr << ulli;
	}

	void print_helper(const float f) {
		std::cerr << f;
	}

	void print_helper(const double d) {
		std::cerr << d;
	}

	void print_helper(const long double ld) {
		std::cerr << ld;
	}

	void print_helper(const bool b) {
		std::cerr << b;
	}

	void print_helper(const char c) {
		std::cerr << c;
	}

	void print_helper(const unsigned char uc) {
		std::cerr << uc;
	}

	void print_helper(const std::string s) {
		std::cerr << s;
	}

	void print_helper(const char *t) {
		std::string s = t; 
		print_helper(s);
	}
};