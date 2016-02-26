#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using std::string;
using std::vector;

class CProperties;
class CAchievements
{
public:
	CAchievements(string theName, vector<CProperties*> theRelatedProps, bool mUnlocked);
	~CAchievements(void);
	void Update();								// Update

private:
	string mName; // achievement name
	vector<CProperties*> mProps;
	bool mUnlocked;
};