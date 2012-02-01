
#include "common.h"
#include "global.h"
#include "GlobalFunctions.h"
#include "valance.h"
#include "Scene.h"
#include "timer.h"
//#include "SDL/SDL_thread.h"

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

		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay( (1000/ FRAMES_PER_SECOND) - fps.get_ticks() );
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
