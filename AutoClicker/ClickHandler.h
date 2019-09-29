#pragma once
#include "Settings.h"

class ClickHandler
{
public:
	ClickHandler();
	~ClickHandler();

	void StartAutoClicker(HWND hWndToInjectInto, Settings const & settings);
	void StopAutoClicker(HWND hWndToInjectInto, Settings const & settings);

	std::atomic<bool> const & IsRunning() const { return running; }

private:

	std::atomic<bool> running;
};

