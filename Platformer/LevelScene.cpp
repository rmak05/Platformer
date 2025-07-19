#include "LevelScene.hpp"

PlayerConfig::PlayerConfig() {
	start_pos_x		= 0.0f;
	start_pos_y		= 0.0f;
	run_velocity	= 0.0f;
	jump_velocity	= 0.0f;
}

PlayerConfig::PlayerConfig(Animation _animation, float _pos_x, float _pos_y, float _run, float _jump) {
	player_animation	=	_animation;
	start_pos_x			=	_pos_x;
	start_pos_y			=	_pos_y;
	run_velocity		=	_run;
	jump_velocity		=	_jump;
}

LevelScene::LevelScene(EntityManager& _entity_manager, SceneId _id, Asset& _assets, int& _level) : Scene(_entity_manager, _id, _assets), player_config(), level(_level) {
	gravity = 0.0f;
}

void LevelScene::initialise() {
    Scene::initialise();

	// register actions
	register_action(sf::Keyboard::W,		ActionName::jump);
	register_action(sf::Keyboard::A,		ActionName::left);
	register_action(sf::Keyboard::D,		ActionName::right);
	register_action(sf::Keyboard::Up,		ActionName::jump);
	register_action(sf::Keyboard::Left,		ActionName::left);
	register_action(sf::Keyboard::Right,	ActionName::right);

	register_action(sf::Keyboard::Escape,	ActionName::quit);
	register_action(sf::Keyboard::B,		ActionName::debug_box);
	register_action(sf::Keyboard::T,		ActionName::debug_texture);
	// add pause action

    // load level file
	std::string config_path = "Config\\";

	std::ifstream level_file;
	std::string level_file_name = "Level" + std::to_string(level) + ".txt";
	level_file.open(config_path + level_file_name);
	if (level_file.fail()) {
		std::cerr << "Failed to open the file " << config_path + level_file_name << std::endl;
		std::exit(EXIT_FAILURE);
	}

	while (!level_file.eof()) {
		std::string line;
		std::getline(level_file, line);

		std::vector<std::string> line_components = line_parser(line);

		if(line_components.empty()) continue;

		if		(line_components[0] == "Tile") {
			auto _entity = add_entity(EntityType::tile);

			Animation _animation = all_assets.get_animation(line_components[1]);
			_entity->set_component<CShape>(_animation);

			float xcoord = std::stof(line_components[2]);
			float ycoord = std::stof(line_components[3]);
			_entity->set_component<CTransform>(grid_to_mid_coord(sf::Vector2f(xcoord, ycoord), _animation));

			_entity->set_component<CBoundingBox>(_animation.get_scaled_size());
		}
		else if (line_components[0] == "Decoration") {
			auto _entity = add_entity(EntityType::decoration);

			Animation _animation = all_assets.get_animation(line_components[1]);
			_entity->set_component<CShape>(_animation);

			float xcoord = std::stof(line_components[2]);
			float ycoord = std::stof(line_components[3]);
			_entity->set_component<CTransform>(grid_to_mid_coord(sf::Vector2f(xcoord, ycoord), _animation));
		}
		else if (line_components[0] == "Gravity") {
			gravity = std::stof(line_components[1]);
		}
		else if (line_components[0] == "Player") {
			player_config = PlayerConfig(all_assets.get_animation(line_components[1]), std::stof(line_components[2]), std::stof(line_components[3]), std::stof(line_components[4]), std::stof(line_components[5]));
		}
	}

	level_file.close();

	spawn_player();

	all_views.push_back(sf::View());
}

void LevelScene::do_action(Action _action) {
	// TODO: complete this

	switch (_action.get_name()) {
		case ActionName::jump : {
			// shouldn't be able to jump if in air
			// can do this by checking if vertical velocity is zero
			
			if (_action.get_type() == ActionType::start) {
				auto& _cmotion = player_ptr->get_component<CMotion>();
				if(_cmotion.velocity.y == 0.0f) _cmotion.velocity.y = player_config.jump_velocity;
			}

			break;
		}

		case ActionName::left : {
			auto& _cmotion = player_ptr->get_component<CMotion>();
			if		(_action.get_type() == ActionType::start) {
				_cmotion.velocity.x = (-player_config.run_velocity);
			}
			else if (_action.get_type() == ActionType::end) {
				_cmotion.velocity.x = 0.0f;
			}

			break;
		}

		case ActionName::right : {
			auto& _cmotion = player_ptr->get_component<CMotion>();
			if		(_action.get_type() == ActionType::start) {
				_cmotion.velocity.x = (player_config.run_velocity);
			}
			else if (_action.get_type() == ActionType::end) {
				_cmotion.velocity.x = 0.0f;
			}

			break;
		}

		case ActionName::debug_box : {
			if (_action.get_type() == ActionType::start) {
				entity_manager.toggle_box_display();
			}

			break;
		}

		case ActionName::debug_texture : {
			if (_action.get_type() == ActionType::start) {
				entity_manager.toggle_texture_display();
			}

			break;
		}

		default : {
			break;
		}
	}
}

void LevelScene::update_and_set_views(sf::RenderWindow& game_window) {
	float player_x_pos = player_ptr->get_component<CTransform>().curr_position.x;
	all_views[0].reset(sf::FloatRect(player_x_pos - static_cast<float>(WINDOW_WIDTH) / 2.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT));
	game_window.setView(all_views[0]);
}

void LevelScene::spawn_player() {
	player_ptr = add_entity(EntityType::player);

	player_ptr->set_component<CShape>(player_config.player_animation);

	player_ptr->set_component<CTransform>(grid_to_mid_coord(sf::Vector2f(player_config.start_pos_x, player_config.start_pos_y), player_config.player_animation));

	player_ptr->set_component<CBoundingBox>(player_config.player_animation.get_scaled_size());

	player_ptr->set_component<CMotion>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, gravity));
}