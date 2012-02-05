

#ifndef _MAJECTY_GLOBAL_H__
#define _MAJECTY_GLOBAL_H__
#include "common.h"
//#include "lua.hpp"

const bool DEBUG_ON = true;

const int SCENE_START = 0;
const int SCENE_GAME = 1;
const int SCENE_BADEND = 2;
const int SCENE_GOODEND = 3;
const int SCENE_CREDIT = 4;
const int SCENE_NUM = 5;
const int UNIT_WIDTH = 30;
const int UNIT_HEIGHT = 30;

const int MESSAGE_BOX_X = 140+10;
const int MESSAGE_BOX_Y = 389;
const int MESSAGE_BOX_W = 500;
const int MESSAGE_BOX_H = 100;

const int MAP_X = 140;
const int MAP_Y = 30;
const int MAP_W = 500;
const int MAP_H = 340;

const int DOOR_X = 40;
const int DOOR_Y = 60;
const int DOOR_W = 50;
const int DOOR_H = 16;

const int OPEN_DOOR_EVENT = 100;
const int MESSAGE_BOX_1_EVENT = 110;
const int MESSAGE_BOX_2_EVENT = 111;
//const int OPEN_DOOR_EVENT = 100;


extern SDL_Surface *screen ;
extern SDL_Event  event;
extern TTF_Font *font ;
extern SDL_Color textColor ;
extern SDL_Color whiteColor ;
extern SDL_Color blackColor ;
extern lua_State *L;

extern bool quit ;

extern SDL_Surface *buildings_image;


#endif
