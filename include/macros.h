#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class Stat;

// ----------------------------------------------
//					General						-
// ----------------------------------------------
const std::string LevelsFileName = "Levels.txt";
const std::string MAIN_FONT = "POORICH.TTF";
constexpr auto NUM_OF_PLAYERS = 4;

struct LevelInfo {
	bool m_lvlPlayers[NUM_OF_PLAYERS];
	std::vector<std::vector<sf::Vector2i>> m_enemyWaves;
};
constexpr auto PI = 3.14159265358979323846;
const sf::Vector2f DEFAULT_VEC(0, 0);
const sf::Vector2f SPRITE_SCALE(1.5f, 1.5f);

// each attack has a const defence ignore rate ( dmg / (def * ignore_rate)) - for balanced damage
constexpr auto DEFENSE_IGNORE_RATE = 0.3f;
constexpr auto SPRITE_SIZE = 60;
constexpr auto WINDOW_WIDTH = 1400;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto HEIGHT_LIMIT = 200;
constexpr auto CUT_CORNERS = 50; // used to limit the player movement to not touch corners
constexpr auto SKILL_GAP = 100;
constexpr auto RADIUS = 55;
constexpr auto BAR_WIDTH = 60;
constexpr auto BAR_HEIGHT = 10;
constexpr auto NEW_LEVEL_DETECTED = -3;
constexpr auto WAVE = '!';
constexpr auto _levelInProgress = 2;
constexpr float DEF_MVSPD = 5.1;

// ----------------------------------------------
//					Animations					-
// ----------------------------------------------
enum CharacterAnimation {
	_walk, _idle, _death, _attack, _specialAttack, SPRITE_ROWS
};

struct AnimationParams {
	sf::Vector2f _imageCount;
	float _switchTime; // remove switch time because it's 0.3f for all.
};

// animation parameters for every type of character and sprite
const AnimationParams PlayerParams =		{ sf::Vector2f(9,5) , 0.3f  };
const AnimationParams characterParams =		{ sf::Vector2f(10,5), 0.3f  };
const AnimationParams projectileParams =	{ sf::Vector2f(8, 1), 0.3f  };
const AnimationParams effectParams =		{ sf::Vector2f(5, 1), 0.3f  };

// each character sprite sheet has different lengths rows so in order to handle all type of spritesheets
// we save the length of each row in the sheet
const std::vector<std::vector<int>> CharacterRowLengths = {
/* cleric*/		{9, 6, 6, 8, 7},
/* knight*/		{9, 8, 6, 6, 7},
/* wizard*/		{9 ,6 ,6 ,8 ,7},
/* archer*/		{9 ,6 ,6 ,8 ,7},
/* demon */		{6, 3, 4, 4, 0},
/* imp */		{6, 3, 4, 5, 0},
/* miniDra*/	{4, 3, 2, 3, 0},
/* wolf	  */	{9, 6, 6, 8, 7},
/* darkCleric*/	{9, 6, 6, 8, 7}

};

// ----------------------------------------------
//					Sounds						-
// ----------------------------------------------
constexpr auto DEFAULT_VOLUME = 40;
const std::vector<std::string> soundList = {
	"battle.wav",
	"buttonClick.wav",
	"clickPlayer.ogg",
	"movePlayer.wav",
	"hoverSound.ogg"
};

// ----------------------------------------------
//					Effects						-
// ----------------------------------------------

enum class AttackType { // different type of attacks targets
	Single , Multi , Self
};

// different type of effects
enum Effects {
	_heal, _damage, _defend, _drainLife, NUM_OF_EFFECTS
};

constexpr auto BUFF_DURATION = 20.f;

// ----------------------------------------------
//					Skills						-
// ----------------------------------------------
constexpr auto NUM_OF_CHARS = 9;
constexpr auto SKILL_RECT_SIZE = 80;

enum Skills {
	_basic, _skill1, _skill2, NUM_OF_SKILLS
};

const float skillCooldowns[NUM_OF_CHARS][NUM_OF_SKILLS] = {
/* cleric*/		{1.75f, 20.f, 30.f } ,
/* knight*/		{0.f ,30.f,  30.f } ,
/* wizard*/		{1.7f, 5.f , 5.f } ,
/* archer*/		{0.f, 20.f , 15.f } ,
/* demon*/		{1.5f},
/* imp */		{1.65f},
/* miniDragon*/	{1.7f},
/* wolf*/		{1.7f},
/* darkCleric*/	{1.7f},
};

const float skillFactors[NUM_OF_CHARS][NUM_OF_SKILLS] = {
/* cleric*/		{1.f, 1.2f, 1.75f },
/* knight*/		{1.f ,1.5f, 1.3f  },
/* wizard*/		{1.f, 1.5f , 1.5f },
/* archer*/		{1.f, 1.8f , 1.4f },
/* demon*/		{1.f},
/* imp */		{1.f},
/* miniDragon*/	{1.f},
/* wolf	*/		{1.f},
/* darkCleric*/	{1.f},
};

const std::string skillTextures[NUM_OF_PLAYERS][NUM_OF_SKILLS] ={	
	{"clericBasic.png", "heal.png",	"clericShield.png" } ,
	{"knightBasic.png", "shield.png","swing.png" } ,
	{"wizardBasic.png", "drainlife.png" , "lightningIcon.png"} ,		
	{"archerBasic.png" , "aimedshot.png" , "barrage.png"}
};


// ----------------------------------------------------------
//						Projectiles							-
// ----------------------------------------------------------

enum ProjEnums // types of projectile
{
	_healBall, _fireProj, _energy, _lightning,
	_tesla, _waterStrike, _fireBreath, _arrow, _none,
	NUM_OF_PROJ
};

const std::vector<std::string > ProjTextrues = {
	"healProj.png", "FireBlast.png", "energy.png", "Lightning.png",
	"Tesla_Ball.png", "water_strike.png", "fireBreath.png" ,
	"arrow.png", "none"
};

// sprite sheets row lengths
const std::vector<std::vector<int>> ProjRowlengths = {
	{8}, {11} , {8} , {12} ,
	{16} , {10} , {8} , {1}, {0}
};

// ----------------------------------------------------------
//							Screens							-
// ----------------------------------------------------------

enum Backgrounds {
	_skillInfo, _helpBG, _settingsBG, 
	_levelSelect, _menu, _firstLevel, 
	NUM_OF_BG
};

const std::string bgTextures[NUM_OF_BG] = { 
	"skillInfoBG.png", "help.png", "settings.png", 
	"levelSelectBG.png", "menuBG.png", "plain.png" 
};

// ----------------------------------------------
//				Gameplay screen                 -
// ----------------------------------------------

// offset to center the sprites.
const sf::Vector2f healthOffset(30, 100);
const sf::Vector2f healthTextOffset(10, 130);
const sf::Vector2f projectileOffset(-10, -20);
const sf::Vector2f selectedOffset(45, 30);
const sf::Vector2f DemonOffset(20, 50);
const sf::Vector2f gameButtonPos(615, 450);
const sf::Vector2f restartButtonPos(615, 500);
const sf::Vector2f exitButtonPos(615, 550);
const sf::Vector2f pauseButtonPos(1300, 30);
constexpr auto onPlayer = true;
constexpr auto isActive = true;

// Buttons --------------------------------------
enum GameButtons {
	_pause, _continue, _restart, _exitButton,
	_pauseHL, _continueHL, _restartHL, _exitButtonHL,
	_skillHover,
	NUM_OF_GBUTTONS
};

enum ButtonIndexes {
	_continueIndex, _restartIndex, _exitIndex
};

const std::string gameButtonsTexts[NUM_OF_GBUTTONS] = {
	"pauseButton.png",
	"continueButton.png",
	"restartButton.png",
	"exitButton.png",
	"pauseButtonHL.png",
	"continueButtonHL.png",
	"restartButtonHL.png",
	"exitButtonHL.png",
	"skillHover.png"
};

// Music in levels ------------------------------
const std::vector<std::string> levelsMusic{
	{"levelMusic1.ogg"},
	{"levelMusic2.ogg"}
};

// States ---------------------------------------
enum GameStates {
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
	{ 300, 300 },
	{ 350, 350 }
};

// Textures ----------------------------------
enum ObjectEnums {
	_cleric, _knight, _wizard, _archer,	// players
	_demon, _imp, _MiniDragon,_wolf , _darkCleric,// enemies
	_select, NUM_OF_OBJECTS
};


const std::string textures[NUM_OF_OBJECTS] = {
	"cleric.png" , "knight.png", "wizard.png" , "archer.png",
	"Demon.png","Imp.png", "MiniDragon.png", "wolf.png" , "DarkCleric.png", "select.png" };


// Map ------------------------------------------
// create hash table of all objects
static std::unordered_map<std::string, int> levelsMap = {
	std::make_pair("Cleric", _cleric),
	std::make_pair("Knight", _knight),
	std::make_pair("Wizard", _wizard),
	std::make_pair("Archer", _archer),
	std::make_pair("Demon" , _demon),
	std::make_pair("Imp" , _imp),
	std::make_pair("MiniDragon",_MiniDragon),
	std::make_pair("Wolf" , _wolf),
	std::make_pair("DarkCleric",_darkCleric),
	std::make_pair("Level", NEW_LEVEL_DETECTED)
};


// Stats ----------------------------------------
enum Stats {
	_hp, _dmg, _range, _defence,
	NUM_OF_STATS
};

// stats of all characters
const std::vector<std::vector<float>> charactersStats = {
	/* cleric */	{ 700.f , 50.f, 800.f , 10.f},
	/* knight */	{ 1200.f, 120.f, 40.f , 20.f},
	/* wizard */	{ 900.f , 100.f, 600.f , 13.f},
	/* archer */	{ 800.f , 200.f, 600.f , 15.f},
	/* demon  */	{ 900.f , 130.f, 70.f , 15.f},
	/* imp	  */	{ 750.f , 100.f , 400.f , 10.f},
	/* miniDrag */	{1250.f , 200.f , 200.f , 35.f},
	/* wolf */		{1250.f , 120.f , 200.f , 35.f},
	/* darkCleric*/ {1000.f , 300.f , 200.f , 35.f}

};

// Movement and Steering ------------------------
enum Locations {
	_target, _object, _velocity
};

//Physics ---------------------------------------
const std::vector<std::vector<float>> objectsPhysics = {
	/* cleric */		{ 0.1f, 50.f, 90.f },
	/* knight */		{ 0.3f, 35.f, 80.f },
	/* wizard */		{ 0.2f, 40.f, 100.f },
	/* archer */		{ 0.2f, 40.f, 100.f },
	/* demon  */		{ 0.1f, 45.f, 70.f },
	/* imp */			{ 0.15f , 42.f , 78.f},
	/* MiniDragon */	{ 0.2f , 40.f , 70.f},
	/* wolf */			{ 0.2f , 40.f , 70.f},
	/* darkCleric */	{ 0.2f , 40.f , 70.f},
};

enum Physics {
	_mass, _maxForce, _maxVelocity
};

// ----------------------------------------------
//					Menu screen					-
// ----------------------------------------------
// Buttons --------------------------------------
enum MenuButtons {
	_battle, _levels, _help, _settings, _escape,
	NUM_OF_MBUTTONS
};
const std::vector<std::string> MENU_BUTTONS_STRINGS = { 
	{"Battle"}, {"Levels"}, {"Help"}, {"Settings"}, {"Exit"} 
};
const sf::Vector2f battleButtonPos = sf::Vector2f(436, 49);
const sf::Vector2f screenButtonsStart = sf::Vector2f(380, 120);
const int buttonOffset = 90;

// ----------------------------------------------
//				Level Select screen				-
// ----------------------------------------------
const sf::Vector2f levelDetailsStart(256, 580);
const sf::Vector2f lsLevelsOffset(163, 123);
const sf::Vector2f lsLevelsStartPos(318, 188);
const sf::Vector2f lvlSelOffset(-8, -8);
const sf::Vector2f startButtonPos(1050, 600);
const sf::Vector2f returnButtonPos(1020, 30);
constexpr auto LEVELS_CHART_COLS = 5;
constexpr auto MAX_LEVELS = 15;

enum LevelSelectTextures {
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

enum LevelSelectButtons {
	_start, _return,
	NUM_OF_LSBUTTONS
};

// ----------------------------------------------
//				Settings screen					-
// ----------------------------------------------
const sf::Vector2f volButtonStart(570, 310);
enum VolumeButtons {
	_volInc, _volDec, _volMute,
	_volIncHL, _volDecHL, _volMuteHL,
	NUM_OF_VOL_BUTTONS,
};

const std::vector<std::string> volTextures = {
	{"volInc.png"},
	{"volDec.png"},
	{"volMute.png"},
	{"volIncHL.png"},
	{"volDecHL.png"},
	{"volMuteHL.png"}
};