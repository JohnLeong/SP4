#ifndef SCENE_LEVELSELECT_H
#define SCENE_LEVELSELECT_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class  CSceneLevelSelection : public CSceneManager
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
		//buttons
		GEO_QUIT_BUTTON,

		//levels
		GEO_LEVEL1_BUTTON,
		GEO_LEVEL2_BUTTON,
		GEO_LEVEL3_BUTTON,
		GEO_LEVEL4_BUTTON,

		NUM_GEOMETRY,
	};

public:
	CSceneLevelSelection(void);
	CSceneLevelSelection(const int m_window_width, const int m_window_height);
	~CSceneLevelSelection(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Keyboard status
	virtual void UpdateKeyboardStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	//set the boolean for quit 
	static void SetISQuitToMain(bool b);
	//get the boolean for quit
	static bool GetIsQuitToMain();

protected:
	Mesh* meshList[NUM_GEOMETRY];

	// Window size
	int m_window_width;
	int m_window_height;

	static bool m_bBacktoMainMenu;

	//virutally create vector positions for the buttons
	Vector3 button_vec[5];
};

#endif