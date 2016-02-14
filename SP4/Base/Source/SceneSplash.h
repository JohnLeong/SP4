#ifndef SCENE_SPLASH_H
#define SCENE_SPLASH_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class CSceneSplash : public CSceneManager
{
	enum GEOMETRY_TYPE
	{
		GEO_QUAD,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

public:
	CSceneSplash(void);
	CSceneSplash(const int m_window_width, const int m_window_height);
	~CSceneSplash(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Keyboard status
	virtual void UpdateKeyboardStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	float m_fTimer;
protected:
	Mesh* meshList[NUM_GEOMETRY];

};

#endif