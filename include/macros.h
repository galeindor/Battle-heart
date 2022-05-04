#pragma once

#include <SFML/Graphics.hpp>

constexpr auto TILES_NUM = 11;
constexpr auto SPACING = 75;

constexpr auto WINDOW_WIDTH = 1400;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto HEIGHT_LIMIT = 200;

constexpr auto DIRECTIONS = 4;
constexpr auto NUM_OF_PICS = 3;
constexpr auto NUM_OF_BG = 2;
constexpr auto MAX_HEALTH = 20;
constexpr auto BAR_WIDTH = 60;


enum LoadTextures
{
	_cleric , _knight , _select
};

enum State
{
	EnemyTrapped = true , EnemyEscaped = false
};

enum Directions
{
	Down=0, Left, Right, Up=3
};


const std::string textures[NUM_OF_PICS] = { "cleric.png" , "knight.png" , "select.png"};

const std::string bg_textures[NUM_OF_PICS] = { "plain.png" };
