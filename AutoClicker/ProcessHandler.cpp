#include "stdafx.h"
#include "ProcessHandler.h"

static HWND hWndToInjectInto;

ProcessHandler::ProcessHandler()
{

}

ProcessHandler::~ProcessHandler()
{

}

// Called as windows are enumertated over
BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if(lpdwProcessId == lParam)
	{
		///	MessageBox(NULL, _T("Found Window"), _T("Found Window"), NULL);
		TCHAR title[256];
		GetWindowText(hwnd, title, sizeof(title));
		///	MessageBox(NULL, title, title, NULL);
		hWndToInjectInto = hwnd;
		return FALSE;
	}
	return TRUE;
}

// Finds the process at the path specified it is exists and is running
// Returns true on success and sets output of GetWnd to the processes' window
// https://docs.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes
bool ProcessHandler::FindWndOfProcess(TCHAR path[MAX_PATH])
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;

	if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return false;
	}

	// Calculate how many process identifiers were returned
	cProcesses = cbNeeded / sizeof(DWORD);

	// Set the window to NULL before trying to find a new one
	hWndToInjectInto = NULL;

	// Find the process required
	for(DWORD i = 0; i < cProcesses; i++)
	{
		if(aProcesses[i] != 0)
		{
			// Get a handle to the process
			DWORD pid = aProcesses[i];
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

			if(hProcess)
			{
				// Get the path of the process
				TCHAR filename[MAX_PATH];
				DWORD filenameLen;
				if((filenameLen = GetModuleFileNameEx(hProcess, NULL, filename, MAX_PATH)) >= 0)
				{
					// Check if the path is the same as the path specified
					if(_tcscmp(filename, path) == 0)
					{
						EnumWindows(EnumWindowsProc, pid);
						if(hWndToInjectInto) {
							hwnd = hWndToInjectInto;
							return true;
						}
						break;
					}
				}
			}

			// Close the handle to the process
			CloseHandle(hProcess);
		}
	}

	return false;
}
