
#include "common.h"
#include "Scene.h"

int DEFAULT_FRAME_RATE;
double DEFAULT_RATE;
double RATE_RATE;
int DEFAULT_LIMIT;
int LIMIT_RATE;
int START_GRADE;
bool IS_FULL_SCREEN;
int CHAR_VELOCITY;
int SHOP_COUNT_FOR_UPGRADE;


TTF_Font *font = NULL;
SDL_Color textColor = {0,0,0};
SDL_Color whiteColor= {0xff,0xff,0xff};
SDL_Color blackColor= {0,0,0};




SDL_Surface *screen = NULL;
SDL_Event  event;

lua_State* L = NULL;
