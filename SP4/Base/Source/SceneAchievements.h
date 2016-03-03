#ifndef SCENE_ACHIEVEMENT_H
#define SCENE_ACHIEVEMENT_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class  CSceneAchievements : public CSceneManager
{
	enum GEOMETRY_TYPE
	{
		GEO_RAY,
		GEO_AXES,
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_TEXT,
		GEO_LOGO,
		GEO_QUAD,
		GEO_WASD,
		GEO_MOUSE,
		GEO_HEADER,
		//buttons
		GEO_BACK,
		GEO_BACK_H,
		GEO_BACKGROUND_BASE,
		GEO_COIN,
		GEO_COIN2,
		GEO_DEATH,
		GEO_DEATH2,
		NUM_GEOMETRY,
	};

public:
	CSceneAchievements(void);
	CSceneAchievements(const int m_window_width, const int m_window_height);
	~CSceneAchievements(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Keyboard status
	virtual void UpdateKeyboardStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	void UpdateAnimations(double dt);

	bool m_bChangeState;

protected:
	Mesh* meshList[NUM_GEOMETRY];

	// Window size
	int m_window_width;
	int m_window_height;

	//check if the keyboard is currently active
	bool m_bisKeyBoard;

	//check if selectSound is currently acftive
	bool isSelectSoundPlaying;

	//virutally create vector positions for the buttons
	Vector3 geo_pos;

	float m_fLeftAnimOffset;
	float m_fBotAnimOffset;
	bool m_bAnimOffsetDir;
};

#endif