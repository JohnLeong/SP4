#pragma once
#include "Properties.h"

class CAchievements
{
public:
	CAchievements(string theId, vector<CProperties*> theRelatedProps);
	~CAchievements(void);
	void Update();								// Update

private:
	string mName; // achievement name
	bool mUnlocked;
	vector<CProperties*> mProps; // array of related properties
};