#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "PhysicsObjectManager.h"

class CSceneMenu : public CSceneManager
{
	enum GEOMETRY_TYPE
	{
		GEO_RAY,
		GEO_AXES,
		GEO_TEXT,
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		//menus (non highlighted)
		GEO_PLAY,
		GEO_INSTRUCTIONS,
		GEO_OPTIONS,
		GEO_EXIT,
		//menus (highlighted)
		GEO_PLAY_H,
		GEO_INSTRUCTIONS_H,
		GEO_OPTIONS_H,
		GEO_EXIT_H,

		//Backgrounds
		GEO_BACKGROUND_BASE,
		GEO_TEMPLE,
		GEO_GROUND,
		GEO_STAR,

		NUM_GEOMETRY,
	};

public:
	CSceneMenu(void);
	~CSceneMenu(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Keyboard status
	virtual void UpdateKeyboardStatus(const unsigned char key);
	virtual void Render(void);
	virtual void Exit(void);

	void UpdateAnimations(double dt);

	enum NEXT_STATE
	{
		NEXT_NONE,
		NEXT_LEVEL_SELECT,
		NEXT_INSTRUCTIONS,
		NEXT_OPTIONS,
		NEXT_EXIT,
		NEXT_PLAY,
	};

	bool m_bChangeState;
	NEXT_STATE m_iNextState;
protected:
	Mesh* meshList[NUM_GEOMETRY];

	//check if the keyboard is currently active
	bool isKeyBoard;

	//check if selectSound is currently active
	bool isSelectSoundPlaying;
	//check if confirmsound is currently active
	bool isConfirmsoundPlaying;

	//virutally create vector positions for the buttons
	Vector3 geo_pos[4];

	float m_fLeftAnimOffset;
	float m_fBotAnimOffset;
	bool m_bAnimOffsetDir;

	CPhysicsObjectManager m_cObjectManager;

};

#endif