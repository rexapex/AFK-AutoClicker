#pragma once

enum EPressType
{
	ptHOLD = 0,
	ptCLICK = 1
};

enum EMouseButton
{
	mbLEFT = 0,
	mbRIGHT = 1,
	mbMIDDLE = 2,

	// Should always be at the end
	mbNUM_MOUSE_BTNTS
};

// Names of the mouse buttons
extern TCHAR const * mouseBtns[mbNUM_MOUSE_BTNTS];

struct Settings
{
	TCHAR exePath[MAX_PATH];
	EPressType pressType;
	EMouseButton btn;
	DWORD timeBetweenClicksMs;
	DWORD keyBindStart;
	DWORD keyBindStartModifiers;
	DWORD keyBindStop;
	DWORD keyBindStopModifiers;
};
