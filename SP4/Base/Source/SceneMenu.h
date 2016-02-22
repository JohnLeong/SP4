#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"


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
	virtual void Render();
	virtual void Exit();

	//get the value of choice
	int getChoiceVal(void);
	//set the value of choice
	void setChoiceVal(int choice);

	//check for collision
	bool checkForcollision(float mouseX,float mouseY,float pos_buttonX, float pos_buttonY, float pos_buttonWidth, float pos_buttonHeight);
protected:
	Mesh* meshList[NUM_GEOMETRY];

	//World size
	float m_world_width;
	float m_world_height;

	//get mouse position in world space
	float worldX;
	float worldY;
	//transverse the menu
	int choice;

	//virutally create vector positions for the buttons
	Vector3 geo_pos[4];

};

#endif