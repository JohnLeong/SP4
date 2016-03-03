#ifndef SCENE_OPTIONS_H
#define SCENE_OPTIONS_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "SceneOptions.h"

class CLuaScript;
class CSceneOptions : public CSceneManager
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

		GEO_BACK,
		GEO_BACK_H,

		GEO_BACKGROUND_BASE,
		GEO_BACKGROUND_IMAGE,

		//volume control
		GEO_MUTE_IMAGE,
		GEO_VOL_HIGH,
		GEO_VOL_MID,
		GEO_VOL_LOW,

		GEO_RESET,
		GEO_RESET_H,

		NUM_GEOMETRY,
	};

	enum VOL_CONTROL
	{
		VOL_HIGH,
		VOL_MID,
		VOL_LOW,

		VOL_MUTE,
	};

public:
	CSceneOptions(void);
	CSceneOptions(const int m_window_width, const int m_window_height);
	~CSceneOptions(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Keyboard status
	virtual void UpdateKeyboardStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	VOL_CONTROL m_ivolControl;

protected:
	Mesh* meshList[NUM_GEOMETRY];

	// Window size
	int m_window_width;
	int m_window_height;

	//check if the keyboard is currently active
	bool m_bisKeyBoard;

	//check if selectSound is currently acftive
	bool isSelectSoundPlaying;

	//for volume control
	int m_volControl;

	//virutally create vector positions for the buttons
	Vector3 geo_pos[3];

	CLuaScript* m_cLuaScript;
};

#endif