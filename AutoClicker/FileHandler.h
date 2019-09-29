#pragma once
#include "Settings.h"

class FileHandler
{
public:
	FileHandler();
	~FileHandler();

	void SaveSettingsToFile(Settings const &);
	void LoadSettingsFromFile(Settings &);

private:
	void GetSettingsFilePath(TCHAR ** path);
};

