#pragma once

#include <SFML/Graphics.hpp>
class Stat;

// General ----------------------------------
const std::string LevelsFileName = "Levels.txt";
const sf::Vector2f healthOffset(30, 100);
const sf::Vector2f selectedOffset(45, 30);
const sf::Vector2f DEFAULT_VEC(0, 0);
constexpr auto SPRITE_SIZE = 64;
constexpr auto WINDOW_WIDTH = 1400;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto HEIGHT_LIMIT = 200;
constexpr auto CUT_CORNERS = 50; // used to limit the player movement to not touch corners
constexpr auto BAR_WIDTH = 60;
constexpr auto LONG_RANGE = 2000;
constexpr auto singleTarget = true;
constexpr auto onPlayer = true;
constexpr auto isActive = true;
constexpr auto NONE_SELECTED = -1;
constexpr auto PLAYER_DETECTED = -2;
constexpr auto NEW_LEVEL_DETECTED = -3;
constexpr auto NEW_WAVE = '!';
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
enum CharacterAnimation
{
	_walk, _basicAtt, _idle, _cast, _death,
};

struct AnimationParams {
	sf::Vector2f _imageCount;
	float _switchTime;
};

const AnimationParams characterParams = { sf::Vector2f(9,5), 0.3f };
const AnimationParams projectileParams = { sf::Vector2f(7, 1), 0.3f };
const AnimationParams effectParams = { sf::Vector2f(5, 1), 0.3f };

// Stats ----------------------------------
constexpr auto MAX_HEALTH = 100;
constexpr auto DEFAULT_MVSPD = 100;
constexpr auto ATK_CD = 10.f; // regular attack cooldown
constexpr auto BASE_CD = 3.f; // basic attack cooldown
constexpr auto SHORT_RANGE = 75.f; // regular attack cooldown

enum Stats
{
	_hp, _attackSpeed, _dmg, _range, _defence, NUM_OF_STATS
};

const std::vector<std::vector<float>> playersBasicStats =
{
	/* cleric */ { 70.f, 2.f, 6.f, 200.f , 10.f},
	/* knight */ { 120.f, 3.f, -7.f, 40.f , 20.f},
	/* archer */ { 90.f, 2.f, -6.f, 600.f , 13.f},
	/* dummy  */ { 80.f, 4.f, -5.f, 40.f , 15.f}
};

// Textures ----------------------------------
enum ObjectEnums
{
	_cleric, _knight, _archer, _dummy, _select, NUM_OF_OBJECTS
};
const std::string textures[NUM_OF_OBJECTS] = { "cleric.png" , "knight.png", "archer.png" ,"enemy.png", "select.png" };

enum Effects
{
	_heal, _damage, _defend, NUM_OF_EFFECTS
};
const std::string effectsTextures[NUM_OF_EFFECTS] = { "healEffect.png" };
constexpr auto EFFECT_COOLDOWN = 2.f;
// Skills ----------------------------------
constexpr auto NUM_OF_PLAYERS = 3;
constexpr auto MAX_SKILL = 2;
constexpr auto BASIC_DMG = 1;
constexpr auto SKILL_RECT_SIZE = 80; // size of the rectangle where skills are shown (?)

enum Skills
{
	_basic, _Skill, _skill2, _passive, NUM_OF_SKILLS
};

const std::string skillTextures[NUM_OF_PLAYERS][MAX_SKILL] = { { "heal.png"	, "clericShield.png"} ,
																{ "shield.png"	, "swing.png"		} ,
																{ "barrage.png" , "apolloarrow.png"	}
};

// Backgrounds ----------------------------------
enum Backgrounds
{
	_menu, _firstLevel, NUM_OF_BG
};
const std::string bg_textures[NUM_OF_BG] = { "plain.png", "menuBG.png" };


// Movement and Steering ------------------------

enum Locations
{
	_target, _object, _velocity, _obstacles
};

enum Physics
{
	_maxVelocity, _maxForce, _mass
};

//Physics
const std::vector<std::vector<float>> objectsPhysics = { { 0.1f, 50.f, 90.f },
														  { 0.3f, 35.f, 80.f },
														  { 0.2f, 40.f, 100.f },
														  { 0.1f, 45.f, 70.f } };

struct Target {
	sf::Vector2f _location;
	std::vector<std::shared_ptr<Stat>> _stats;
};

struct LevelInfo
{
	bool m_lvlPlayers[NUM_OF_PLAYERS];
	std::vector<std::vector<sf::Vector2i>> m_enemyWaves;
};
};


// Projectiles

enum Projectiles
{
	_healBall , NUM_OF_PROJ
};

const std::string proj_textures[NUM_OF_PROJ] = { "healProj.png"};