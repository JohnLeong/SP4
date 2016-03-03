#ifndef ENTITY_TEXTBOX_H
#define ENTITY_TEXTBOX_H

#include "EntityIPos.h"

/*
\brief
Text box class to display text
*/

class CTextBox : public CEntityIPos
{
public:
	CTextBox();
	CTextBox(int iXIndex, int iYIndex, CTilemap* cTilemap, std::string text, CEntityIPos* cPlayerPtr);
	~CTextBox(void);

	std::string GetText(void);

	static bool ShowText(void);
	static bool ShowBox(void);

	static float GetBoxScaleX(void);
	static float GetBoxScaleY(void);

	bool IsActivated(void);

	int GetCurrentCharIndex(void);

	virtual void Update(const float dt);		// Update
	static void UpdateBox(const float dt);
	static void ResetBox(void);

protected:
	std::string m_Text;				//Text to display
	bool m_bActivated;				//Is current textbox entity activated by player
	bool m_bWasActivated;			//Was current textbox entity activated by player previously
	int m_iCurrentCharIndex;		//Char index to display text up to a certain point

	static bool m_bShowBox;			//Show text box
	static bool m_bOpenBox;			//Allow text box to open
	static bool m_bShowText;		//Show text inside text box
	static float m_fBoxScaleX;		//ScaleX of textbox
	static float m_fBoxScaleY;		//ScaleY of textbox
};

#endif