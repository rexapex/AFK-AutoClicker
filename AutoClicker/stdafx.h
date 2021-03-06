// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <shellapi.h>
#include <ShlObj.h>
#include <Psapi.h>
#include <Commdlg.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

// C++11 imports
#include <thread>
#include <atomic>
#include <fstream>
#include <string>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// reference additional headers your program requires here
