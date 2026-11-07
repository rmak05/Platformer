#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
#include "EntityManager.hpp"
#include "Scene.hpp"
#include "LevelScene.hpp"
#include "Asset.hpp"
#include "Theme.hpp"
#include "Helper.hpp"
#include "Debug.hpp"

class Game;

class Game {
private:
	Asset					all_assets;
	sf::RenderWindow		game_window;
	int						window_width;
	int						window_height;
	unsigned				frame_rate;
	long long				curr_frame;
	EntityManager			entity_manager;
	std::vector<scene_ptr>	all_scenes;
	SceneId					curr_scene;
	int						curr_level;
	// bool paused;
	// bool running;

	void initialise();
	void config();

	void set_curr_scene(SceneId _scene_id);

public:
	Game();

	void run();
};