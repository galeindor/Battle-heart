#pragma once

#include <SFML/Graphics.hpp>

constexpr auto TILES_NUM = 11;
constexpr auto SPACING = 75;

constexpr auto WINDOW_WIDTH = 1400;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto HEIGHT_LIMIT = 200;
constexpr auto CUT_CORNERS = 50; // used to limit the player movement to not touch corners

constexpr auto NUM_OF_PICS = 3;
constexpr auto NUM_OF_BG = 2;
constexpr auto NUM_OF_PLAYERS = 3;

constexpr auto MAX_SKILL = 2;
constexpr auto BASIC_DMG = 1;
constexpr auto MAX_HEALTH = 20;
constexpr auto SKILL_RECT_SIZE= 80;

constexpr auto BAR_WIDTH = 60;
constexpr auto ATK_CD = 10.f; // regular attack cooldown


enum LoadTextures
{
	_cleric , _knight , _select
};

enum State
{
	EnemyTrapped = true , EnemyEscaped = false
};

const std::string textures[NUM_OF_PICS] = { "cleric.png" , "knight.png" , "select.png"};

const std::string skillTextures[NUM_OF_PLAYERS][MAX_SKILL] = {  { "heal.png"	, "clericShield.png"} ,
																{ "shield.png"	, "swing.png"		}
															 };

const std::string bg_textures[NUM_OF_PICS] = { "plain.png" };

