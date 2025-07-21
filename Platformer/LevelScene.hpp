#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Scene.hpp"
#include "Helper.hpp"

struct PlayerConfig;

class LevelScene;

struct PlayerConfig {
    Animation   player_animation;
    float       start_pos_x;
    float       start_pos_y;
    float       run_velocity;
    float       jump_velocity;

    PlayerConfig();
    PlayerConfig(Animation _animation, float _pos_x, float _pos_y, float _run, float _jump);
};

class LevelScene : public Scene {
private:
    int&            level;
    PlayerConfig    player_config;
    entity_ptr      player_ptr;
    float           gravity;

public:
    LevelScene(EntityManager& _entity_manager, SceneId _id, Asset& _assets, int& _level);

    void initialise() override;
    void do_action(Action _action) override;
    void update_and_set_views(sf::RenderWindow& game_window) override;

    void spawn_player();
    void spawn_bullet();
};