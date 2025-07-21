#include "Game.hpp"

Game::Game() {
	window_width				= WINDOW_WIDTH;
	window_height				= WINDOW_HEIGHT;
	frame_rate					= 60u;
	curr_frame					= 0ll;
	curr_scene					= SceneId::_default;
	curr_level					= 1000000000;
}

void Game::initialise() {
	config();

	// intitialise scenes
	all_scenes = std::vector<scene_ptr>((size_t)SceneId::count);
	all_scenes[static_cast<int>(SceneId::level)] = std::make_shared<LevelScene>(entity_manager, SceneId::level, all_assets, curr_level);
	curr_level = 1;		// remove this please
	set_curr_scene(SceneId::level);

	sf::VideoMode desktop_size	= sf::VideoMode::getDesktopMode();
	//window_width				= (int)desktop_size.width;
	//window_height				= (int)desktop_size.height;
	game_window.create(sf::VideoMode(window_width, window_height), "Platformer");
	game_window.setKeyRepeatEnabled(false);
	game_window.setFramerateLimit(frame_rate);
}

void Game::config() {
	std::string config_path = "Config\\";

	// Loading Assets
	std::ifstream assets_file;
	std::string assets_file_name = "Assets.txt";
	assets_file.open(config_path + assets_file_name);
	if (assets_file.fail()) {
		std::cerr << "Failed to open the file " << config_path + assets_file_name << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::string textures_path, animations_path, fonts_path;

	while (!assets_file.eof()) {
		std::string line;
		std::getline(assets_file, line);

		std::vector<std::string> line_components = line_parser(line);

		if(line_components.empty()) continue;

		if		(line_components[0] == "TexturePath") {
			textures_path = line_components[1];
		}
		else if (line_components[0] == "Texture") {
			sf::Texture _texture;
			if (!_texture.loadFromFile(textures_path + line_components[2])) {
				std::cerr << "Unable to load the texture " << line_components[1] << " from " << textures_path + line_components[2] << std::endl;
			}
			all_assets.add_texture(line_components[1], _texture);
		}
		else if (line_components[0] == "Animation") {
			Animation _animation(line_components[1], all_assets.get_texture(line_components[2]), std::stof(line_components[3]), std::stof(line_components[4]), static_cast<unsigned>(std::stoi(line_components[5])), static_cast<unsigned>(std::stoi(line_components[6])), static_cast<unsigned>(std::stoi(line_components[7])));
			all_assets.add_animation(line_components[1], _animation);
		}
	}

	assets_file.close();
}

void Game::set_curr_scene(SceneId _scene_id) {
	curr_scene = _scene_id;

	all_scenes[static_cast<int>(curr_scene)]->initialise();
}

void Game::resolve_collisions() {
	all_scenes[static_cast<int>(curr_scene)]->resolve_collisions();
}

void Game::run() {
	initialise();

	while (game_window.isOpen()){
		curr_frame++;

		sf::Event _event;

		while (game_window.pollEvent(_event)){
			switch (_event.type) {
				case sf::Event::EventType::Closed: {
					game_window.close();

					break;
				}

				case sf::Event::EventType::MouseButtonPressed: {
					if (_event.mouseButton.button == sf::Mouse::Right) {
						debug::update();
					}

					break;
				}

				case sf::Event::EventType::KeyPressed: {
					ActionName _name = all_scenes[static_cast<int>(curr_scene)]->find_action(static_cast<int>(_event.key.code));
					if(_name != ActionName::_default) all_scenes[static_cast<int>(curr_scene)]->do_action(Action(_name, ActionType::start));

					break;
				}

				case sf::Event::EventType::KeyReleased: {
					ActionName _name = all_scenes[static_cast<int>(curr_scene)]->find_action(static_cast<int>(_event.key.code));
					if(_name != ActionName::_default) all_scenes[static_cast<int>(curr_scene)]->do_action(Action(_name, ActionType::end));

					break;
				}

				default: {
					break;
				}
			}
		}

		all_scenes[static_cast<int>(curr_scene)]->update_entities();
		all_scenes[static_cast<int>(curr_scene)]->transform_entities();
		all_scenes[static_cast<int>(curr_scene)]->resolve_collisions();
		all_scenes[static_cast<int>(curr_scene)]->update_animations();
		all_scenes[static_cast<int>(curr_scene)]->update_and_set_views(game_window);

		game_window.clear(BG_COLOR);
		all_scenes[static_cast<int>(curr_scene)]->draw_entities(game_window);
		debug::draw(game_window);
		game_window.display();
	}
}