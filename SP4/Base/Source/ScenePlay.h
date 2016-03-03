#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Level.h"


const float SKYBOXSIZE = 1000.f;

class CScenePlay : public CSceneManager
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		GEO_GRASS_DARKGREEN,
		GEO_GRASS_LIGHTGREEN,
		GEO_TEXT,
		GEO_BACKCOVER,
		GEO_BACKGROUND,

		//Tile overlay
		GEO_OVERLAY_RED,
		GEO_QUESTION_MARK,

		GEO_TEXTBOX,

		GEO_TRANSPARENT_LAYER,

		GEO_STAR,
		GEO_STAROUTLINE,

		GEO_COIN,
		GEO_KEYS_RED,
		GEO_KEYS_BLUE,
		GEO_KEYS_YELLOW,
		GEO_KEYS_GREEN,

		//Tile geometry
		GEO_TILE_FLOOR_STONE_01,
		GEO_TILE_FLOOR_ICE_01,
		GEO_TILE_WALL_STONE_01,
		GEO_TILE_HOLE_STONE_01,
		GEO_TILE_HOLE_STONE_FILLED_01,
		GEO_TILE_DOOR_RED,
		GEO_TILE_DOOR_BLUE,
		GEO_TILE_DOOR_GREEN,
		GEO_TILE_DOOR_YELLOW,
		GEO_TILE_RUNE,
		GEO_TILE_RUNE_USED,
		GEO_TILE_FORCE_UP,
		GEO_TILE_FORCE_DOWN,
		GEO_TILE_FORCE_LEFT,
		GEO_TILE_FORCE_RIGHT,
		GEO_TILE_STAIRCASE,
		GEO_TILE_MONKEY,

		GEO_PLAYER,
		GEO_SCROLL,
		GEO_QUIT_BUTTON,
		GEO_QUIT_BUTTON_HIGHLIGHTED,
		GEO_RESTART_BUTTON,
		GEO_RESTART_BUTTON_HIGHLIGHTED,
		GEO_NEXT_BUTTON,
		GEO_NEXT_BUTTON_HIGHLIGHTED,

		NUM_GEOMETRY,
	};

public:
	CScenePlay(void);
	CScenePlay(const int m_window_width, const int m_window_height);
	CScenePlay(const int m_window_width, const int m_window_height, int iLevel, bool bPanic);
	~CScenePlay(void);

	virtual void Init();
	virtual void Update(double dt);

	//set the boolean for quit 
	static void SetISQuitToMain(bool b);
	//get the boolean for quit
	static bool GetIsQuitToMain();

	virtual void Render();
	virtual void Exit();

	void InitLevel();

	// Render the main components of this scene
	void RenderGUI(void);
	void RenderWin(void);
	void RenderLose(void);
	void RenderPlayer(void);
	void RenderEntities(void);
	void RenderTextBox(void);
	void RenderInventory(void);
	void RenderTilemap(void);
	void RenderAchievement(CAchievements* achievement);

	bool m_bExitPlay;
	bool m_bToFinishScreen;
private:
	//unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	// Window size
	int m_window_width;
	int m_window_height;

	// Handle to 3rd Person View's avatar
	//CPlayInfo3PV* m_cAvatar;
	
	CPlayer* m_cPlayer;

	//Level
	CLevel m_cLevel;

	//Achievements
	int m_iCurrentLevel;

	static bool m_bBacktoMainMenu;
    
	Vector3 quit_button_vec;
	Vector3 restart_button_vec;
	Vector3 nextLevel_button_vec_winScreen;
	Vector3 restart_button_vec_winScreen;
	Vector3 exit_button_vec_winScreen;
	Vector3 restart_button_vec_loseScreen;
	Vector3 quit_button_vec_loseScreen;
	
	SpriteAnimation* coins_sprite;

	//keys sprite animation
	SpriteAnimation* keys_sprite_red;
	SpriteAnimation* keys_sprite_green;
	SpriteAnimation* keys_sprite_yellow;
	SpriteAnimation* keys_sprite_blue;

	float m_fShakeAngle;
	float m_fShakeOffsetX;
	float m_fShakeOffsetY;

	//Win & lose
	bool m_bShowWin;
	bool m_bShowLose;

	bool m_bDied;
	bool m_bTimerCheck;
	bool m_bMouseisPressed;
	bool m_bQuitselectsound;
	bool m_bPlayWinSound;
	bool m_bPlayLoseSound;
};

#endif