#ifndef PLATFORMER_CONFIG_HPP
#define PLATFORMER_CONFIG_HPP

#include <cstdint>

#include <SFML/Graphics.hpp>

inline constexpr uint8_t GAME_TEXTURE_BLOCK_SIZE{64};

inline constexpr sf::Color BOUNDING_BOX_COLOR{0x6600ffff};
inline constexpr float BOUNDING_BOX_THICKNESS{-2.0f};

#endif // PLATFORMER_CONFIG_HPP
