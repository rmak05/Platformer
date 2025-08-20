#include "LevelScene.hpp"

PlayerConfig::PlayerConfig() {
	start_pos_x		= 0.0f;
	start_pos_y		= 0.0f;
	run_velocity	= 0.0f;
	jump_velocity	= 0.0f;
}

PlayerConfig::PlayerConfig(Animation _animation_still, Animation _animation_moving, Animation _animation_jumping, float _pos_x, float _pos_y, float _run, float _jump) {
	animation_still		= _animation_still;
	animation_moving	= _animation_moving;
	animation_jumping	= _animation_jumping;
	start_pos_x			= _pos_x;
	start_pos_y			= _pos_y;
	run_velocity		= _run;
	jump_velocity		= _jump;
}

BulletConfig::BulletConfig() {
	bullet_velocity = 0.0f;
}

BulletConfig::BulletConfig(Animation _bullet_animation, float _bullet_velocity, Animation _explosion_animation) {
	bullet_animation	= _bullet_animation;
	bullet_velocity		= _bullet_velocity;
	explosion_animation	= _explosion_animation;
}

LevelScene::LevelScene(EntityManager& _entity_manager, SceneId _id, Asset& _assets, int& _level) : Scene(_entity_manager, _id, _assets), player_config(), bullet_config(), level(_level) {
	gravity = 0.0f;
}

void LevelScene::initialise() {
    Scene::initialise();

	// register actions
	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::W)),		ActionName::jump);
	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::A)),		ActionName::left);
	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::D)),		ActionName::right);
	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::Up)),		ActionName::jump);
	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::Left)),	ActionName::left);
	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::Right)),	ActionName::right);
	register_action(
		ActionKey(InputType::mouse, static_cast<int>(sf::Mouse::Left)),			ActionName::shoot);

	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::Escape)),	ActionName::quit);
	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::B)),		ActionName::debug_box);
	register_action(
		ActionKey(InputType::keyboard, static_cast<int>(sf::Keyboard::T)),		ActionName::debug_texture);
	register_action(
		ActionKey(InputType::mouse, static_cast<int>(sf::Mouse::Right)),		ActionName::debug_grid);
	// add pause action

    // load level file
	std::string config_path = "Config/";

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
			_entity->set_component<CTransform>(grid_to_mid_coord(sf::Vector2f(xcoord, ycoord), _animation.get_scale(), static_cast<sf::Vector2f>(_animation.get_sprite_size())), _animation.get_scale());

			_entity->set_component<CBoundingBox>(vector_pairwise_product(static_cast<sf::Vector2f>(_animation.get_sprite_size()), _animation.get_scale()));
		}
		else if (line_components[0] == "Decoration") {
			auto _entity = add_entity(EntityType::decoration);

			Animation _animation = all_assets.get_animation(line_components[1]);
			_entity->set_component<CShape>(_animation);

			float xcoord = std::stof(line_components[2]);
			float ycoord = std::stof(line_components[3]);
			_entity->set_component<CTransform>(grid_to_mid_coord(sf::Vector2f(xcoord, ycoord), _animation.get_scale(), static_cast<sf::Vector2f>(_animation.get_sprite_size())), _animation.get_scale());
		}
		else if (line_components[0] == "Gravity") {
			gravity = std::stof(line_components[1]);
		}
		else if (line_components[0] == "Player") {
			player_config = PlayerConfig(all_assets.get_animation(line_components[1]), all_assets.get_animation(line_components[2]), all_assets.get_animation(line_components[3]), std::stof(line_components[4]), std::stof(line_components[5]), std::stof(line_components[6]), std::stof(line_components[7]));
		}
		else if (line_components[0] == "Bullet") {
			bullet_config = BulletConfig(all_assets.get_animation(line_components[1]), std::stof(line_components[2]), all_assets.get_animation(line_components[3]));
		}
	}

	level_file.close();

	spawn_player();

	all_views.push_back(sf::View());
}

void LevelScene::do_action(Action _action) {
	// TODO: complete this
	switch (_action.get_name()) {
		case ActionName::jump: {
			if (_action.get_type() == ActionType::start) {
				auto& _cmotion = player_ptr->get_component<CMotion>();
				if(_cmotion.velocity.y == 0.0f){
					_cmotion.velocity.y = player_config.jump_velocity;
				}
			}

			break;
		}

		case ActionName::left: {
			auto& _transform	= player_ptr->get_component<CTransform>();
			auto& _cmotion		= player_ptr->get_component<CMotion>();

			if		(_action.get_type() == ActionType::start) {
				player_ptr->get_component<CInput>().left = true;
				_cmotion.velocity.x += (-player_config.run_velocity);
				_transform.scale.x = std::fabsf(_transform.scale.x) * (-1);
			}
			else if (_action.get_type() == ActionType::end) {
				player_ptr->get_component<CInput>().left = false;
				if(player_ptr->get_component<CInput>().right){
					_cmotion.velocity.x = (player_config.run_velocity);
					_transform.scale.x = std::fabsf(_transform.scale.x) * (1);
				}
				else _cmotion.velocity.x = 0.0f;
			}

			break;
		}

		case ActionName::right: {
			auto& _transform	= player_ptr->get_component<CTransform>();
			auto& _cmotion		= player_ptr->get_component<CMotion>();

			if		(_action.get_type() == ActionType::start) {
				player_ptr->get_component<CInput>().right = true;
				_cmotion.velocity.x += (player_config.run_velocity);
				_transform.scale.x = std::fabsf(_transform.scale.x) * (1);
			}
			else if (_action.get_type() == ActionType::end) {
				player_ptr->get_component<CInput>().right = false;
				if(player_ptr->get_component<CInput>().left){
					_cmotion.velocity.x = (-player_config.run_velocity);
					_transform.scale.x = std::fabsf(_transform.scale.x) * (-1);
				}
				else _cmotion.velocity.x = 0.0f;
			}

			break;
		}

		case ActionName::shoot: {
			if (_action.get_type() == ActionType::start) {
				spawn_bullet();
			}

			break;
		}

		case ActionName::debug_grid: {
			if (_action.get_type() == ActionType::start) {
				debug::update();
			}

			break;
		}

		case ActionName::debug_box: {
			if (_action.get_type() == ActionType::start) {
				entity_manager.toggle_box_display();
			}

			break;
		}

		case ActionName::debug_texture: {
			if (_action.get_type() == ActionType::start) {
				entity_manager.toggle_texture_display();
			}

			break;
		}

		default: {
			break;
		}
	}
}

void LevelScene::transform_entities() {
	for (auto& _entity : entity_manager.all_entities) {
		if(_entity->get_type() == EntityType::player) continue;
		_entity->transform();
	}

	auto& _cmotion	= player_ptr->get_component<CMotion>();
	auto& _shape	= player_ptr->get_component<CShape>();
	if		(_cmotion.velocity == sf::Vector2f(0.0f, 0.0f)){
		if (_shape.shape.get_name() != player_config.animation_still.get_name()) _shape.shape = player_config.animation_still;
	}
	else if (_cmotion.velocity.y == 0.0f){
		if (_shape.shape.get_name() != player_config.animation_moving.get_name()) _shape.shape = player_config.animation_moving;
	}
	else if (_cmotion.velocity.y < 0.0f){
		if (_shape.shape.get_name() != player_config.animation_jumping.get_name()) _shape.shape = player_config.animation_jumping;
	}
	else {
		if (_shape.shape.get_name() != player_config.animation_still.get_name()) _shape.shape = player_config.animation_still;
	}
	player_ptr->transform();
}

void LevelScene::update_and_set_views(sf::RenderWindow& game_window) {
	float player_x_pos = player_ptr->get_component<CTransform>().curr_position.x;
	all_views[0].reset(sf::FloatRect(player_x_pos - static_cast<float>(WINDOW_WIDTH) / 2.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT));
	game_window.setView(all_views[0]);
}

void LevelScene::spawn_player() {
	player_ptr = add_entity(EntityType::player);
	player_ptr->set_component<CShape>(player_config.animation_still);
	player_ptr->set_component<CTransform>(grid_to_mid_coord(sf::Vector2f(player_config.start_pos_x, player_config.start_pos_y), player_config.animation_still.get_scale(), static_cast<sf::Vector2f>(player_config.animation_still.get_sprite_size())), player_config.animation_still.get_scale());
	player_ptr->set_component<CBoundingBox>(vector_pairwise_product(static_cast<sf::Vector2f>(player_config.animation_still.get_sprite_size()), player_config.animation_still.get_scale()));
	player_ptr->set_component<CMotion>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, gravity));
	player_ptr->set_component<CInput>();
}

void LevelScene::spawn_bullet() {
	float direction = static_cast<float>(player_ptr->get_component<CTransform>().scale.x > 0.0f ? 1.0f : -1.0f);

	entity_ptr _bullet = add_entity(EntityType::bullet);
	sf::Vector2f bullet_scale = bullet_config.bullet_animation.get_scale();
	bullet_scale.x *= direction;
	_bullet->set_component<CShape>(bullet_config.bullet_animation);
	_bullet->set_component<CTransform>(player_ptr->get_component<CTransform>().curr_position + sf::Vector2f(32.0f * direction, -8.0f), bullet_scale);
	_bullet->set_component<CBoundingBox>(vector_pairwise_product(static_cast<sf::Vector2f>(bullet_config.bullet_animation.get_sprite_size()), bullet_config.bullet_animation.get_scale()));
	_bullet->set_component<CMotion>(sf::Vector2f(bullet_config.bullet_velocity * direction, 0.0f), sf::Vector2f(0.0f, 0.0f));

	entity_ptr _explosion = add_entity(EntityType::decoration);
	_explosion->set_component<CShape>(bullet_config.explosion_animation);
	_explosion->set_component<CTransform>(player_ptr->get_component<CTransform>().curr_position + sf::Vector2f(44.0f * direction, -8.0f), bullet_config.explosion_animation.get_scale());
}

// TODO: bullet might collide with player at bullet spawn
// TODO: Jump while pressing right, just after player lands, animation doesn't change to moving.
// Scale must be changed in transform entities i think, so maybe remove scale from animation and shift to CTransform or something