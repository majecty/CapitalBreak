
#include "GlobalFunctions.h"
#include "common.h"
#include "global.h"
#include "Scene.h"
#include "timer.h"
#include "lua_glue.h"


Scene* scenes[SCENE_NUM];
bool quit = false;
Scene* scene = NULL;

static void scenes_initialize();
static void SDL_Initialize();
static void default_video_initialize();
static void font_module_initialize();
static void load_font();
static void delete_scenes();

void init()
{
    quit = false;

    lua_init();

    scenes_initialize();


    SDL_Initialize();

    default_video_initialize();

    font_module_initialize();


    SDL_WM_SetCaption("Capital Break", NULL);

}

void load_files()
{
//    load_default_background();

    load_font();

}

void clean_up()
{
    lua_close(L);

    scene->clean_up();

//    SDL_FreeSurface(buildings_image);

    delete_scenes();

    TTF_CloseFont( font);

    TTF_Quit();

    SDL_Quit();
}

static void event_loop()
{

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
}

int main(int argc, char* args[] )
{

    int frame = 0;

    init();

    load_files();

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
        frame++;

        fps.start(); 

        scene->show();

        event_loop();


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


static void scenes_initialize()
{
    scenes[SCENE_START] = new StartScene();
    scenes[SCENE_GAME] = new GameScene();
    scenes[SCENE_BADEND] = new BadEndScene();
    scenes[SCENE_GOODEND] = new GoodEndScene();
    scenes[SCENE_CREDIT] = new CreditScene();

}

static void SDL_Initialize()
{
    if( SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        error( "SDL CORE Initialize ERROR ",AT);
    }
}

static void default_video_initialize()
{

    if (IS_FULL_SCREEN)
        screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN);
    else
        screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if (screen == NULL)
    {
        error("Set Video Mode ERROR\n",AT);
    }
}

static void font_module_initialize()
{

    if( TTF_Init() == -1 )
    {
        error( "Font Module Load Error \n",AT);
    }
}

static void load_font()
{
    font = TTF_OpenFont("SangSangTitleM.ttf", 25);
    if(font == NULL)
    {
        error("Font Load Error \n",AT);
    }

}

static void delete_scenes()
{
    delete (scenes[SCENE_START]);
    delete (scenes[SCENE_GAME] );
    delete (scenes[SCENE_BADEND]);
    delete (scenes[SCENE_GOODEND]);
    delete (scenes[SCENE_CREDIT]);
}
