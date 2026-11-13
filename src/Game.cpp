// #include "Game.hpp"

// Game::Game() {
// 	window_width				= WINDOW_WIDTH;
// 	window_height				= WINDOW_HEIGHT;
// 	frame_rate					= 60u;
// 	curr_frame					= 0ll;
// 	curr_scene					= SceneId::_default;
// 	curr_level					= 1000000000;
// }

// void Game::initialise() {
// 	config();

// 	// intitialise scenes
// 	all_scenes = std::vector<scene_ptr>((size_t)SceneId::count);
// 	all_scenes[static_cast<int>(SceneId::level)] = std::make_shared<LevelScene>(entity_manager, SceneId::level, all_assets, curr_level);
// 	curr_level = 1;		// TODO: remove this please
// 	set_curr_scene(SceneId::level);

// 	sf::VideoMode desktop_size	= sf::VideoMode::getDesktopMode();
// 	//window_width				= (int)desktop_size.width;
// 	//window_height				= (int)desktop_size.height;
// 	game_window.create(sf::VideoMode({window_width, window_height}), sf::String("Platformer"));
// 	game_window.setKeyRepeatEnabled(false);
// 	game_window.setFramerateLimit(frame_rate);
// }

// void Game::config() {
// 	std::string config_path("Config");

// 	// Loading Assets
// 	std::ifstream assets_file;
// 	std::string assets_file_name = "Assets.txt";
// 	assets_file.open(config_path + "/" + assets_file_name);
// 	if (assets_file.fail()) {
// 		std::cerr << "Failed to open the file " << config_path + "/" + assets_file_name << std::endl;
// 		std::exit(EXIT_FAILURE);
// 	}
// 	std::string texture_path, font_path;

// 	while (!assets_file.eof()) {
// 		std::string line;
// 		std::getline(assets_file, line);

// 		std::vector<std::string> line_components = line_parser(line);

// 		if		(line_components.empty()) {
// 			continue;
// 		}
// 		else if	(line_components[0] == "TexturePath") {
// 			texture_path = line_components[1];
// 		}
// 		else if (line_components[0] == "Texture") {
// 			all_assets.add_texture(line_components[1], texture_path + "/" + line_components[2]);
// 		}
// 		else if (line_components[0] == "Animation") {
// 			all_assets.add_animation(line_components);
// 		}
// 		else if	(line_components[0] == "FontPath") {
// 			font_path = line_components[1];
// 		}
// 		else if (line_components[0] == "Font") {
// 			all_assets.add_font(line_components[1], font_path + "/" + line_components[2]);
// 		}
// 	}

// 	assets_file.close();
// }

// void Game::set_curr_scene(SceneId _scene_id) {
// 	curr_scene = _scene_id;

// 	all_scenes[static_cast<int>(curr_scene)]->initialise();
// }

// void Game::run() {
// 	initialise();

// 	while (game_window.isOpen()){
// 		curr_frame++;

// 		while (const std::optional _event = game_window.pollEvent()) {
// 			if (_event->is<sf::Event::Closed>()) {
// 				game_window.close();
// 			}
// 			else if (const auto* mouse_pressed = _event->getIf<sf::Event::MouseButtonPressed>()) {
// 				ActionName _name = all_scenes[static_cast<int>(curr_scene)]->find_action(ActionKey(InputType::mouse, static_cast<int>(mouse_pressed->button)));
// 				if (_name != ActionName::_default) all_scenes[static_cast<int>(curr_scene)]->do_action(Action(_name, ActionType::start));
// 			}
// 			else if (const auto* mouse_released = _event->getIf<sf::Event::MouseButtonReleased>()) {
// 				ActionName _name = all_scenes[static_cast<int>(curr_scene)]->find_action(ActionKey(InputType::mouse, static_cast<int>(mouse_released->button)));
// 				if (_name != ActionName::_default) all_scenes[static_cast<int>(curr_scene)]->do_action(Action(_name, ActionType::end));
// 			}
// 			else if (const auto* key_pressed = _event->getIf<sf::Event::KeyPressed>()) {
// 				ActionName _name = all_scenes[static_cast<int>(curr_scene)]->find_action(ActionKey(InputType::keyboard, static_cast<int>(key_pressed->code)));
// 				if (_name != ActionName::_default) all_scenes[static_cast<int>(curr_scene)]->do_action(Action(_name, ActionType::start));
// 			}
// 			else if (const auto* key_released = _event->getIf<sf::Event::KeyReleased>()) {
// 				ActionName _name = all_scenes[static_cast<int>(curr_scene)]->find_action(ActionKey(InputType::keyboard, static_cast<int>(key_released->code)));
// 				if (_name != ActionName::_default) all_scenes[static_cast<int>(curr_scene)]->do_action(Action(_name, ActionType::end));
// 			}
// 		}

// 		all_scenes[static_cast<int>(curr_scene)]->update_added_entities();
// 		all_scenes[static_cast<int>(curr_scene)]->update_deleted_entities();
// 		all_scenes[static_cast<int>(curr_scene)]->transform_entities();
// 		all_scenes[static_cast<int>(curr_scene)]->resolve_collisions();
// 		all_scenes[static_cast<int>(curr_scene)]->update_animations();
// 		all_scenes[static_cast<int>(curr_scene)]->update_added_entities();
// 		all_scenes[static_cast<int>(curr_scene)]->update_deleted_entities();
// 		all_scenes[static_cast<int>(curr_scene)]->update_and_set_views(game_window);

// 		game_window.clear(BG_COLOR);
// 		all_scenes[static_cast<int>(curr_scene)]->draw_entities(game_window);
// 		debug::draw(game_window);
// 		game_window.display();
// 	}
// }

// /*
// TODO: make a get_curr_scene function
// Connect debug to debug box and debug textures
// Should Animation in assets return a reference or a copy?
// */
