#include "stdafx.h"
#include "FileHandler.h"

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler()
{

}

void FileHandler::SaveSettingsToFile(Settings const & s)
{
	// Get the path of the settings file
	TCHAR * path;
	GetSettingsFilePath(&path);

	// Open and write to the file
	std::wofstream f;
	f.open(path);
	f << L"EXEPATH " << s.exePath << L"\n";
	f << L"HOLDORCLICK " << s.pressType << L"\n";
	f << L"MBTN " << s.btn << L"\n";
	f << L"INTERVAL " << s.timeBetweenClicksMs << L"\n";
	f << L"KEYSTART " << s.keyBindStart << L"\n";
	f << L"KEYSTARTMOD " << s.keyBindStartModifiers << L"\n";
	f << L"KEYSTOP " << s.keyBindStop << L"\n";
	f << L"KEYSTOPMOD " << s.keyBindStopModifiers << L"\n";
	f.close();
}

void FileHandler::LoadSettingsFromFile(Settings & s)
{
	// Get the path of the settings file
	TCHAR * path;
	GetSettingsFilePath(&path);

	std::wifstream f;
	f.open(path);
	std::wstring line;
	while(std::getline(f, line))
	{
		// NOTE - Only works if TCHAR is a wide char
		std::wstring key;
		std::wstring value;
		size_t splitPos = line.find(' ');
		key = line.substr(0, splitPos);
		value = line.substr(splitPos+1, line.size()-splitPos-1);

		// Determine which variable to set based on key name
		if(key == L"EXEPATH")
		{
			memcpy_s(s.exePath, MAX_PATH*sizeof(TCHAR), value.c_str(), value.size()*sizeof(wchar_t));
		}
		else if(key == L"HOLDORCLICK")
		{
			s.pressType = (EPressType)wcstol(value.c_str(), NULL, 10);
		}
		else if(key == L"MBTN")
		{
			s.btn = (EMouseButton)wcstol(value.c_str(), NULL, 10);
		}
		else if(key == L"INTERVAL")
		{
			s.timeBetweenClicksMs = wcstol(value.c_str(), NULL, 10);
		}
		else if(key == L"KEYSTART")
		{
			s.keyBindStart = wcstol(value.c_str(), NULL, 10);
		}
		else if(key == L"KEYSTARTMOD")
		{
			s.keyBindStartModifiers = wcstol(value.c_str(), NULL, 10);
		}
		else if(key == L"KEYSTOP")
		{
			s.keyBindStop = wcstol(value.c_str(), NULL, 10);
		}
		else if(key == L"KEYSTOPMOD")
		{
			s.keyBindStopModifiers = wcstol(value.c_str(), NULL, 10);
		}
	}
}

void FileHandler::GetSettingsFilePath(TCHAR ** path)
{
	TCHAR szPath[MAX_PATH];
	// Get the AppData/Roaming folder
	if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
	{
		// Append the application folder
		PathAppend(szPath, _T("\\Origami Sheep\\AutoClicker\\"));

		// Create the folders if they don't already exist
		SHCreateDirectoryEx(NULL, szPath, NULL);

		// Append the filename
		PathAppend(szPath, _T("\\Settings.txt"));
		*path = szPath;
	}
}
