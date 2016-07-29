// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "tinyxml2.h"

//Include classes all files need
#include "DebugLogManager.h"
#include "GraphicsManager.h"
#include "AudioManager.h"
#include "ScreensManager.h"
#include "ActivityManager.h"

//Create the debug singleton here
extern DebugLogManager	debug;
extern GraphicsManager	graphicsManager;
extern AudioManager		audioManager;
extern ScreensManager	screensManager;
extern ActivityManager	activityManager;