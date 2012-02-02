
#include "GlobalFunctions.h"
#include "common.h"
#include "global.h"
#include "Scene.h"
#include "timer.h"
#include "lua_glue.h"



//#include "SDL/SDL_thread.h"


int DEFAULT_FRAME_RATE;
double DEFAULT_RATE;
double RATE_RATE;
int DEFAULT_LIMIT;
int LIMIT_RATE;
int START_GRADE;
bool IS_FULL_SCREEN;

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

lua_State* L;


void lua_init()
{
    L = luaL_newstate();
    luaL_openlibs(L);
    fprintf(stderr, "in lua_init function start %s\n",AT );

    if ( luaL_loadfile(L, "Configuration.lua") || lua_pcall(L,0,0,0))
    //if ( luaL_loadfile(L, "luac.out") || lua_pcall(L,0,0,0))
        maj_lua_error(L, "cannot run config. file: %s\n", lua_tostring(L,-1));
    fprintf(stderr, "in after lua_loadfile");

    lua_getglobal(L, "default_frame_rate");
    lua_getglobal(L, "default_rate");
    lua_getglobal(L, "rate_rate");
    lua_getglobal(L, "default_limit");
    lua_getglobal(L, "limit_rate");
    lua_getglobal(L, "start_grade");

    lua_getglobal(L, "is_full_screen");

    DEFAULT_FRAME_RATE = lua_tointeger(L,1);
    DEFAULT_RATE = lua_tonumber(L,2);
    RATE_RATE = lua_tonumber(L,3);
    DEFAULT_LIMIT = lua_tointeger(L,4);
    LIMIT_RATE = lua_tointeger(L,5);
    START_GRADE = lua_tointeger(L,6);
    IS_FULL_SCREEN = lua_toboolean(L,7);

    fprintf(stderr, "default frame rate is %d\n", LIMIT_RATE);
    fprintf(stderr, "LIMIT_RATE is %d\n", LIMIT_RATE);


    init_glue();
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

        if (IS_FULL_SCREEN)
            screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN);
        else
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
    lua_close(L);

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

        scene->show();


        while(SDL_PollEvent ( &event))
        {
            scene->do_event();

            if ( event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_q:
                        quit = true;
                        break;
                    default: break;
                }

            }
        }

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
