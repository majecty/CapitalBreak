#pragma once

//#ifndef _MAJECTY_COMMON_H__
//#define _MAJECTY_COMMON_H__
extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/luaconf.h"
#include "lua/lualib.h"
}
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Constants.h"
#include "GlobalFunctions.h"
#include "Configuration.h"
#include "global.h"
#include <string>
#include <sstream>





//#include "lua/lua.hpp"
#include <iostream>
#include <stdarg.h>

#define ZeroMemory(Destination, length)  \
{ \
  memset((void*)Destination, 0, length);\
}
#define STRINGIFY(in ) #in
#define MACROTOSTRING(in) STRINGIFY(in)
#define AT __FILE__ ":" MACROTOSTRING(__LINE__)
//#include "Card.h"
//#include "Scene.h"
//#endif
