#pragma once
class ProcessHandler
{
public:
	ProcessHandler();
	~ProcessHandler();

	// Finds the process at the path specified it is exists and is running
	// Returns true on success and sets output of GetWnd to the processes' window
	bool FindWndOfProcess(TCHAR path[MAX_PATH]);

	HWND GetWnd() const { return hwnd; }

private:
	HWND hwnd;
};

