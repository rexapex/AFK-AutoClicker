#pragma once
#include "Settings.h"

class FileHandler
{
public:
	FileHandler();
	~FileHandler();

	void SaveSettingsToFile(Settings const &);
	bool LoadSettingsFromFile(Settings &);

	bool FileExists(TCHAR * path);

private:
	void GetSettingsFilePath(TCHAR ** path);
};

