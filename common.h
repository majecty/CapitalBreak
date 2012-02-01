

#ifndef _MAJECTY_COMMON_H__
#define _MAJECTY_COMMON_H__
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Constants.h"
#include "GlobalFunctions.h"
#include "global.h"
#include <string>
#include <sstream>

extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lua.hpp"
#include "lua/luaconf.h"
#include "lua/lualib.h"
}

#define ZeroMemory(Destination, length)  \
{ \
  memset((void*)Destination, 0, length);\
}
//#include "Card.h"
//#include "Scene.h"
#endif
