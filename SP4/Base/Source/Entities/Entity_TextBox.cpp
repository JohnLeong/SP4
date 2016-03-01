#include "Entity_TextBox.h"

#define BOX_MIN_SCALE_X 1.f
#define BOX_MIN_SCALE_Y 1.f

#define BOX_MAX_SCALE_X 400.f

#define BOX_SCALE_SPEED 2000.f

float CTextBox::m_fBoxScaleX = BOX_MIN_SCALE_X;
float CTextBox::m_fBoxScaleY = BOX_MIN_SCALE_Y;
bool CTextBox::m_bOpenBox = false;
bool CTextBox::m_bShowText = false;
bool CTextBox::m_bShowBox = false;

CTextBox::CTextBox()
: m_bActivated(false)
, m_bWasActivated(false)
{
}

CTextBox::CTextBox(int iXIndex, int iYIndex, CTilemap* cTilemap, std::string text, CEntityIPos* cPlayerPtr)
: m_bActivated(false)
, m_bWasActivated(false)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_Text = text;
	this->m_cPlayerPtr = cPlayerPtr;
}

CTextBox::~CTextBox(void)
{
}

std::string CTextBox::GetText(void)
{
	return m_Text;
}

bool CTextBox::ShowText(void)
{
	return CTextBox::m_bShowText;
}

bool CTextBox::ShowBox(void)
{
	return CTextBox::m_bShowBox;
}

float CTextBox::GetBoxScaleX(void)
{
	return CTextBox::m_fBoxScaleX;
}

float CTextBox::GetBoxScaleY(void)
{
	return CTextBox::m_fBoxScaleY;
}

/********************************************************************************
Update
********************************************************************************/
void CTextBox::Update(const float dt)
{
	if (this->m_iXIndex == this->m_cPlayerPtr->GetXIndex() && this->m_iYIndex == this->m_cPlayerPtr->GetYIndex())
	{
		m_bActivated = true;
		m_bWasActivated = true;
		CTextBox::m_bOpenBox = true;
	}
	else
	{
		if (m_bWasActivated)
		{
			CTextBox::m_bOpenBox = false;
		}
		m_bActivated = false;
		m_bWasActivated = false;
	}

}

void CTextBox::UpdateBox(const float dt)
{
	if (CTextBox::m_bOpenBox)
	{
		CTextBox::m_bShowBox = true;
		CTextBox::m_fBoxScaleX += dt * BOX_SCALE_SPEED;
		if (CTextBox::m_fBoxScaleX >= BOX_MAX_SCALE_X)
		{
			CTextBox::m_bShowText = true;
			CTextBox::m_fBoxScaleX = BOX_MAX_SCALE_X;
		}
		else
			CTextBox::m_bShowText = false;
	}
	else
	{
		CTextBox::m_bShowText = false;
		CTextBox::m_fBoxScaleX -= dt * BOX_SCALE_SPEED;
		if (CTextBox::m_fBoxScaleX < BOX_MIN_SCALE_X)
		{
			CTextBox::m_fBoxScaleX = BOX_MIN_SCALE_X;
			CTextBox::m_bShowBox = false;
		}
	}
}

void CTextBox::ResetBox(void)
{
	CTextBox::m_fBoxScaleX = BOX_MIN_SCALE_X;
	CTextBox::m_fBoxScaleY = BOX_MIN_SCALE_Y;
	CTextBox::m_bOpenBox = false;
	CTextBox::m_bShowText = false;
	CTextBox::m_bShowBox = false;
}