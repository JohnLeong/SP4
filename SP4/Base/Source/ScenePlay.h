#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Level.h"
#include "Achievements\Achievements.h"

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

		//Tile overlay
		GEO_OVERLAY_RED,

		//Tile geometry
		GEO_TILE_FLOOR_STONE_01,
		GEO_TILE_FLOOR_ICE_01,
		GEO_TILE_WALL_STONE_01,
		GEO_TILE_HOLE_STONE_01,
		GEO_PLAYER,

		NUM_GEOMETRY,
	};

public:
	CScenePlay(void);
	CScenePlay(const int m_window_width, const int m_window_height);
	~CScenePlay(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Avatar position
 	virtual void UpdateAvatarStatus(const unsigned char key, const bool status = true);
	// Update Weapon status
	virtual void UpdateWeaponStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	void InitLevel();
	void InitAchievements();

	// Render the main components of this scene
	void RenderGUI();
	void RenderPlayer();
	void RenderEntities();
	void RenderTilemap(void);

	bool m_bExitPlay;

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
	CAchievements* m_cAchievements;

	int m_iCurrentLevel;
};

#endif