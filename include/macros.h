#pragma once

#include <SFML/Graphics.hpp>
class Stat;

// General ----------------------------------
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
const AnimationParams projectileParams = { sf::Vector2f(9, 1), 0.3f };
const AnimationParams effectParams = { sf::Vector2f(5, 1), 0.3f };

// Stats ----------------------------------
constexpr auto MAX_HEALTH = 20;
constexpr auto DEFAULT_MVSPD = 100;
constexpr auto ATK_CD = 10.f; // regular attack cooldown
constexpr auto BASE_CD = 3.f; // basic attack cooldown
constexpr auto SHORT_RANGE = 75.f; // regular attack cooldown

enum Stats
{
	_hp, _movementSpeed, _attackSpeed, _range, NUM_OF_STATS
};

// Textures ----------------------------------
enum LoadTextures
{
	_cleric, _knight, _archer, _dummy, _select, NUM_OF_PICS
};
const std::string textures[NUM_OF_PICS] = { "cleric.png" , "knight.png", "archer.png" ,"enemy.png", "select.png" };

enum effectsTextures
{
	_heal, NUM_OF_EFFECTS
};
const std::string effectsTextures[NUM_OF_EFFECTS] = { "healEffect.png" };
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


// Movement and Steering ------------------------

enum Locations
{
	_target , _object , _velocity , _obstacles
};

enum Steering
{
	_maxVelocity, _maxForce
};

// Structs
struct Target {
	sf::Vector2f _location;
	std::vector<Stat>* _stats;
};

struct Physics {
	float m_mass;
	float m_maxForce;
	float m_maxVelocity;
	float m_range;
};

const std::vector<Physics> playersPhysics = {	{		},
												{	},
												{	} };

//_cleric, _knight, _archer, _select, _dummy, NUM_OF_PICS

const std::vector<std::vector<float>> playersBasicStats = 
{
/* cleric */ {BASIC_DMG*(-2),	LONG_RANGE	},
/* knight */ {BASIC_DMG		,	SHORT_RANGE	},
/* archer */ {BASIC_DMG		,	LONG_RANGE	},
/* dummy  */ {BASIC_DMG		,	SHORT_RANGE }
};