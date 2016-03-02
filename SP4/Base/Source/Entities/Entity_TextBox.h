#ifndef ENTITY_TEXTBOX_H
#define ENTITY_TEXTBOX_H

#include "EntityIPos.h"


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
	std::string m_Text;
	bool m_bActivated;
	bool m_bWasActivated;
	int m_iCurrentCharIndex;

	static bool m_bShowBox;
	static bool m_bOpenBox;
	static bool m_bShowText;
	static float m_fBoxScaleX;
	static float m_fBoxScaleY;
};

#endif