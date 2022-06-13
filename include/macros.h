#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
class Stat;

// ----------------------------------------------
//					General						-
// ----------------------------------------------
const std::string LevelsFileName = "Levels.txt";
const std::string MAIN_FONT = "POORICH.TTF";
constexpr auto NUM_OF_PLAYERS = 3;
struct LevelInfo {
	bool m_lvlPlayers[NUM_OF_PLAYERS];
	std::vector<std::vector<sf::Vector2i>> m_enemyWaves;
};
constexpr auto PI = 3.14159265358979323846;
const sf::Vector2f DEFAULT_VEC(0, 0);
constexpr auto SPRITE_SIZE = 60;
constexpr auto WINDOW_WIDTH = 1400;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto HEIGHT_LIMIT = 200;
constexpr auto CUT_CORNERS = 50; // used to limit the player movement to not touch corners
constexpr auto BAR_WIDTH = 60;
constexpr auto NEW_LEVEL_DETECTED = -3;
constexpr auto WAVE = '!';
constexpr auto _levelInProgress = 2;

// ----------------------------------------------
//					Animations					-
// ----------------------------------------------
enum CharacterAnimation
{
	_walk, _hurt, _idle, _death, _attack, _specialAttack, SPRITE_ROWS
};

struct AnimationParams {
	sf::Vector2f _imageCount;
	float _switchTime; // remove switch time because it's 0.3f for all.
};

const AnimationParams characterParams = { sf::Vector2f(10,6), 0.3f };
const AnimationParams projectileParams = { sf::Vector2f(8, 1), 0.3f };
const AnimationParams effectParams = { sf::Vector2f(5, 1), 0.3f };

const std::vector<std::vector<int>> CharacterRowLengths = {
	{ 6, 4, 9, 8, 7, 7 },
	{ 6, 4, 7, 8, 5, 8 },
	{ 6 ,4 ,9 ,8 ,7 ,7 },
	{ 6, 2, 3, 4, 4, 0 },
	{ 6, 2, 3, 4, 5, 0 } 
};

const std::vector<std::vector<int>> EffectsSSLengths = { {5} };

const std::vector<std::vector<int>> ProjRowlengths = { {22} };

// ----------------------------------------------
//					Effects						-
// ----------------------------------------------
enum Effects
{
	_heal, _damage, _defend, _drainLife, NUM_OF_EFFECTS
};


const std::string effectsTextures[NUM_OF_EFFECTS] = { "healEffect.png" };
constexpr auto EFFECT_COOLDOWN = 2.f;

// ----------------------------------------------
//					Skills						-
// ----------------------------------------------
constexpr auto NUM_OF_CHARS = 5;
constexpr auto SKILL_RECT_SIZE = 80;

enum Skills
{
	_basic, _skill1, _skill2, _passive, NUM_OF_SKILLS
};

const float skillCooldowns[NUM_OF_CHARS][NUM_OF_SKILLS] = {
	{1.75f, 20.f, 30.f , 100.f} ,
	{1.65f ,30.f,  30.f, 100.f } ,
	{1.7f, 5.f , 5.f , 100.f} ,
	{1.5f},
	{1.65f}
};

const float skillFactors[NUM_OF_CHARS][NUM_OF_SKILLS] = {	
	{1.f, 1.2f, 1.75f , 1.f},	
	{1.f ,1.5f, 1.3f, 1.f },
	{1.f, 1.5f , 1.5f , 1.f},
	{1.f},
	{1.f}
};

const std::string skillTextures[NUM_OF_PLAYERS][NUM_OF_SKILLS] ={	{"clericBasic.png", "heal.png",	"clericShield.png" , ""} ,
																	{"knightBasic.png", "shield.png","swing.png" , ""} ,
																	{"archerBasic.png", "aimedshot.png" , "barrage.png" , ""} ,						
};

// ----------------------------------------------------------
//						Screens								-
// ----------------------------------------------------------
enum Backgrounds
{
	_levelSelect, _menu, _firstLevel, NUM_OF_BG
};

const std::string bgTextures[NUM_OF_BG] = { "levelSelectBG.png", "menuBG.png", "plain.png" };

// ----------------------------------------------
//				Gameplay screen                 -
// ----------------------------------------------
const sf::Vector2f healthOffset(30, 100);
const sf::Vector2f selectedOffset(45, 30);
const sf::Vector2f continueButtonPos(615, 450);
const sf::Vector2f restartButtonPos(615, 500);
const sf::Vector2f exitButtonPos(615, 550);
const sf::Vector2f pauseButtonPos(1200, 200);
constexpr auto singleTarget = true;
constexpr auto onPlayer = true;
constexpr auto isActive = true;

enum GameButtons
{
	_pause, _continue, _restart, _exitButton,
	_pauseHL, _continueHL, _restartHL, _exitButtonHL,
	NUM_OF_GBUTTONS
};

const std::string gameButtonsTexts[NUM_OF_GBUTTONS] = {
	"pauseButton.png",
	"continueButton.png",
	"restartButton.png",
	"exitButton.png",
	"pauseButtonHL.png",
	"continueButtonHL.png",
	"restartButtonHL.png",
	"exitButtonHL.png"
};

enum GameStates
{
	_winLevel, _loseLevel, _pauseLevel,
	NUM_OF_GAME_STATES
};

const std::string gameStateTexts[NUM_OF_GAME_STATES] = {
	"Victory.png",
	"Defeat.png",
	"Pause.png"
};

const std::vector<sf::Vector2f> startPositions = {
{ 200, 200 },
{ 250, 250 },
{ 300, 300 }
};

// Textures ----------------------------------
enum ObjectEnums
{
	_cleric, _knight, _archer, 
	_demon, _imp, 
	_select, NUM_OF_OBJECTS
};

enum ProjEnums
{
	_healBall, _fireProj, _energy, _lightning, 
	_tesla, _waterStrike, _none, 
	NUM_OF_PROJ
};

const std::string textures[NUM_OF_OBJECTS] = { 
	"cleric1.png" , "knightSS.png", "witch.png" ,"Demon.png", 
	"Imp.png", "select.png" };

const std::vector<std::string > ProjTextrues = { 
	"healProj.png" , "fireProj.png" , "energy.png" , "lightning.png" , 
	"tesla_ball.png" , "water_strike.png"  , "none" };

// Map ------------------------------------------
static std::unordered_map<std::string, int> levelsMap = {
	std::make_pair("Cleric",_cleric),
	std::make_pair("Knight", _knight),
	std::make_pair("Archer", _archer),
	std::make_pair("Dummy" , _demon),
	std::make_pair("Imp" , _imp),
	std::make_pair("Level", NEW_LEVEL_DETECTED)
};

// Stats ----------------------------------------
enum Stats
{
	_hp, _attackSpeed, _dmg, _range, _defence,
	NUM_OF_STATS
};

const std::vector<std::vector<float>> charactersStats =
{
	/* cleric */ { 70.f, 2.f, 6.f, 800.f , 10.f},
	/* knight */ { 120.f, 3.f, 15.f, 40.f , 20.f},
	/* archer */ { 90.f, 2.f, 20.f, 600.f , 13.f},
	/* dummy  */ { 80.f, 4.f, 10.f, 40.f , 15.f},
	/* imp	  */ { 75.f , 3.f , 20.f , 500.f , 10.f}
};

// Movement and Steering ------------------------
enum Locations
{
	_target, _object, _velocity, _obstacles
};

//Physics ---------------------------------------
const std::vector<std::vector<float>> objectsPhysics = {
	{ 0.1f, 50.f, 90.f },
	{ 0.3f, 35.f, 80.f },
	{ 0.2f, 40.f, 100.f },
	{ 0.1f, 45.f, 70.f },
	{ 0.15f , 42.f , 78.f}
};

enum Physics
{
	_mass, _maxForce, _maxVelocity
};

// ----------------------------------------------
// Menu screen									-
// ----------------------------------------------
// Buttons --------------------------------------
enum MenuButtons
{
	_battle, _levels, _help, _escape,
	NUM_OF_MBUTTONS
};

const std::vector<std::string> MENU_BUTTONS_STRINGS = { {"Battle"}, {"Levels"}, {"Help"}, {"Exit"} };
const sf::Vector2f MENU_BUTTONS_START = sf::Vector2f(436, 49);
const int MENU_BUTTONS_OFFSET = 110, MENU_BUTTONS_GAP = 20;

// ----------------------------------------------
// Level Select screen							-
// ----------------------------------------------
const sf::Vector2f lsLevelsOffset(163, 123);
const sf::Vector2f lsLevelsStartPos(318, 188);
const sf::Vector2f lvlSelOffset(-8, -8);
const sf::Vector2f startButtonPos(1050, 600);
const sf::Vector2f returnButtonPos(1020, 30);
constexpr auto LEVELS_CHART_COLS = 5;
constexpr auto MAX_LEVELS = 15;

enum LevelSelectTextures
{
	_currLvlIcon, _lvlCompleted, _levelSelection, _startButton, _startButtonHL,
	NUM_OF_LS_TEXTS
};

const std::string lvSelTexts[NUM_OF_LS_TEXTS] = {
	"currentLevelIcon.png",
	"levelCompleted.png",
	"levelSelection.png",
	"startButton.png",
	"startButtonHL.png"
};
enum LevelSelectButtons
{
	_start, _return,
	NUM_OF_LSBUTTONS
};






