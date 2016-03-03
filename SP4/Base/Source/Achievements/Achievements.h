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

	enum saveProperties
	{
		Name,
		Title,
		TotalProperties,
		Properties,
		Completed,
		ShowOnce,
		NUM_Properties
	};

	CAchievements(string theName, string theTitle, vector<string> theRelatedProps, bool mUnlocked, bool mAppearedOnce, bool mShowedOnce, double timer);
	~CAchievements(void);
	void Update(vector<CProperties*> checkList);								// Update
	vector<string> GetProps();
	void Save(fstream& file, int id);
	void Reset(fstream& file, int id);
	static string propertyName[NUM_Properties];

	string GetTitle();

	bool GetUnlocked();
	bool GetAppearedOnce();
	bool GetShowedOnce();
	double GetTimer();

	void SetUnlocked(bool mUnlocked);
	void SetAppearedOnce(bool mAppearedOnce);
	void SetShowedOnce(bool mShowedOnce);
	void SetTimer(double mTimer);

private:
	string mName, mTitle;
	vector<string> mProps;
	bool mUnlocked, mAppearedOnce, mShowedOnce;
	double mTimer;
};