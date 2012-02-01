
#include "common.h"
#include "global.h"
#include "GlobalFunctions.h"
#include "valance.h"
#include "Scene.h"
#include "timer.h"


#include <iostream>
#include <stdarg.h>

//#include "SDL/SDL_thread.h"


int DEFAULT_FRAME_RATE;
double DEFAULT_RATE;
double RATE_RATE;
int DEFAULT_LIMIT;
int LIMIT_RATE;

Scene* scene = NULL;
Scene* scenes[SCENE_NUM];

TTF_Font *font = NULL;
SDL_Color textColor = {0,0,0};
SDL_Color whiteColor= {0xff,0xff,0xff};
SDL_Color blackColor= {0,0,0};

SDL_Surface *buildings_image;

bool quit = false;

SDL_Surface *screen = NULL;
SDL_Event  event;

void lua_error(lua_State *L, const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

void lua_init()
{
    lua_State *L = luaL_newstate();
    fprintf(stderr, "in lua_init function start");

    if ( luaL_loadfile(L, "Configuration.lua") || lua_pcall(L,0,0,0))
        lua_error(L, "cannot run config. file: %s", lua_tostring(L,-1));
    fprintf(stderr, "in after lua_loadfile");

    lua_getglobal(L, "default_frame_rate");
    lua_getglobal(L, "default_rate");
    lua_getglobal(L, "rate_rate");
    lua_getglobal(L, "default_limit");
    lua_getglobal(L, "limit_rate");

    DEFAULT_FRAME_RATE = lua_tointeger(L,1);
    DEFAULT_RATE = lua_tonumber(L,2);
    RATE_RATE = lua_tonumber(L,3);
    DEFAULT_LIMIT = lua_tointeger(L,5);
    LIMIT_RATE = lua_tointeger(L,6);

    fprintf(stderr, "default frame rate is %d\n", LIMIT_RATE);
    fprintf(stderr, "LIMIT_RATE is %d\n", LIMIT_RATE);


    //lua_State *L = luaL_newstate();
    //luaL_openlibs(L);

    //luaopen_io(L); // provides io.*

    std::cerr << "-- Loading file: " << "test" << std::endl;

    /*
    //int s = luaL_loadfile(L, file);

    if ( s==0 ) {
      // execute Lua program
      s = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    */

    //report_errors(L, s);
    lua_close(L);
    std::cerr << std::endl;
}


bool init()
{
	quit = false;

	scenes[SCENE_START] = new StartScene();
	scenes[SCENE_GAME] = new GameScene();
	scenes[SCENE_BADEND] = new BadEndScene();
	scenes[SCENE_GOODEND] = new GoodEndScene();
	scenes[SCENE_CREDIT] = new CreditScene();


	if( SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	if (screen == NULL)
	{
		return false;
	}

	if( TTF_Init() == -1 )
	{
		return false;
	}

	SDL_WM_SetCaption("Capital Break", NULL);


	return true;
}

bool load_files()
{

	font = TTF_OpenFont("SangSangTitleM.ttf", 25);
	buildings_image = load_image("game_1s_building.png");

	if(font == NULL)
	{
		return false;
	}
	return true;
}

void clean_up()
{

	scene->clean_up();
	SDL_FreeSurface(buildings_image);

	delete (scenes[SCENE_START]);
	delete (scenes[SCENE_GAME] );
	delete (scenes[SCENE_BADEND]);
	delete( scenes[SCENE_GOODEND]);
	delete( scenes[SCENE_CREDIT]);

	TTF_CloseFont( font);

	TTF_Quit();

	SDL_Quit();
}

int main(int argc, char* args[] )
{
    //fprintf(stderr, "Error log ok? %s\n", SDL_GetError());
    lua_init();

	int frame = 0;

	if( init() == false )
	{
            fprintf(stderr, "main initialize fail\n");
		return 1;
	}

	if( load_files() == false)
	{
            fprintf(stderr, "main loadfiles fail\n");
		return 1;
	}

	scene = scenes[SCENE_START];

	scene->init();


	Timer fps;
	Timer fpsMeter;
	// Timer used to update the caption
	Timer update;

	update.start();
	fpsMeter.start();

	while (quit == false)
	{
		fps.start(); 

		scene->do_event();

		scene->show();

		frame++;

		if( fps.get_ticks() < 1000 / DEFAULT_FRAME_RATE)
		{
			SDL_Delay( (1000/ DEFAULT_FRAME_RATE) - fps.get_ticks() );
		}
		if( update.get_ticks() > 1000)
		{
			std::stringstream caption;
			caption << "Capital Break " << frame / (fpsMeter.get_ticks() / 1000.f) << "fps";
			SDL_WM_SetCaption( caption.str().c_str(), NULL);
			update.start();

		}
	}
	clean_up();

	return 0;
}
void change_scene(int scene_num)
{
	scene->clean_up();
	scene = scenes[scene_num];
	scene->init();

}
