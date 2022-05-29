#pragma once

#include <SFML/Graphics.hpp>

// General ----------------------------------
const sf::Vector2f healthOffset(30, 100);
const sf::Vector2f selectedOffset(45, 30);
constexpr auto SPRITE_SIZE = 64;
constexpr auto WINDOW_WIDTH = 1400;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto HEIGHT_LIMIT = 200;
constexpr auto CUT_CORNERS = 50; // used to limit the player movement to not touch corners
constexpr auto BAR_WIDTH = 60;
constexpr auto ATK_CD = 10.f; // regular attack cooldown
constexpr auto BASE_CD = 3.f; // regular attack cooldown


// Buttons
enum MenuButtons
{
	_battle, _levels, _escape, NUM_OF_MBUTTONS
};
const std::string MENU_BUTTON_FONT = "titillium.otf";
const std::vector<std::string> MENU_BUTTONS_STRINGS = { {"Battle"}, {"Levels"}, {"Exit"} };
const sf::Vector2f MENU_BUTTONS_START = sf::Vector2f(436, 49);
const int MENU_BUTTONS_OFFSET = 110, MENU_BUTTONS_GAP = 20;

// Animations ----------------------------------
enum ObjectAnimation
{
	_walk, _basicAtt, _idle, _cast, _death
};

// Stats ----------------------------------
constexpr auto MAX_HEALTH = 20;
constexpr auto DEFAULT_MVSPD = 100;
constexpr auto ATK_CD = 10.f; // regular attack cooldown

enum Stats
{
	_hp, _movementSpeed, _attackSpeed, _range, NUM_OF_STATS
};

// Textures ----------------------------------
enum LoadTextures
{
	_cleric, _knight, _archer, _select, _dummy, NUM_OF_PICS
};
const std::string textures[NUM_OF_PICS] = { "cleric.png" , "knight.png", "archer.png" , "select.png", "enemy.png"};

// Skills ----------------------------------
constexpr auto NUM_OF_PLAYERS = 3;
constexpr auto MAX_SKILL = 2;
constexpr auto BASIC_DMG = 1;
constexpr auto SKILL_RECT_SIZE = 80; // size of the rectangle where skills are shown (?)

const std::string skillTextures[NUM_OF_PLAYERS][MAX_SKILL] = {  { "heal.png"	, "clericShield.png"} ,
																{ "shield.png"	, "swing.png"		} ,
																{ "barrage.png" , "apolloarrow.png"	}
															 };

// Backgrounds ----------------------------------
enum Backgrounds
{
	_menu, _firstLevel, NUM_OF_BG
};
const std::string bg_textures[NUM_OF_BG] = { "plain.png", "menuBG.png" };

