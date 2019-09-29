#include "stdafx.h"
#include "ClickHandler.h"

ClickHandler::ClickHandler()
{

}

ClickHandler::~ClickHandler()
{

}

void ClickHandler::StartAutoClicker(HWND hWndToInjectInto, Settings const & settings)
{
	// Ensure the window is know before trying to inject input
	if(hWndToInjectInto)
	{
		running = true;
		DWORD btnDown = settings.btn == mbLEFT ? WM_LBUTTONDOWN : settings.btn == mbRIGHT ? WM_RBUTTONDOWN : WM_MBUTTONDOWN;
		DWORD btnUp = settings.btn == mbLEFT ? WM_LBUTTONUP : settings.btn == mbRIGHT ? WM_RBUTTONUP : WM_MBUTTONUP;
		// Holding down won't work because tabbing out cause the mouseup event to trigger
		// Send a mouse down event every second so if a mouseup occurs, there will be little downtime
		std::thread t([ this, hWndToInjectInto, settings, btnDown, btnUp ]()
		{
			while(running)
			{
				SendMessage(hWndToInjectInto, btnDown, 100, 100);
				Sleep(settings.timeBetweenClicksMs);
				if(settings.pressType == ptCLICK) {
					// Click requires a press followed by a release
					SendMessage(hWndToInjectInto, btnUp, 100, 100);
				}
			}
		});
		t.detach();
	}
	else
	{
		MessageBox(NULL, _T("Window could not be found for specified executable"), NULL, NULL);
	}
}

void ClickHandler::StopAutoClicker(HWND hWndToInjectInto, Settings const & settings)
{
	// Ensure the window is know before trying to inject input
	if(hWndToInjectInto)
	{
		running = false;
		DWORD btn = settings.btn == mbLEFT ? WM_LBUTTONUP : settings.btn == mbRIGHT ? WM_RBUTTONUP : WM_MBUTTONUP;
		SendMessage(hWndToInjectInto, btn, 100, 100);
	}
	else
	{
		MessageBox(NULL, _T("Window could not be found for specified executable"), NULL, NULL);
	}
}
