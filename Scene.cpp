#include "Scene.h"
#include "global.h"
#include "Object.h"

void Scene::init() { ;
    fprintf(stderr, "Scene's init function");
}
void Scene::clean_up(){;}
void Scene::do_event(){;}
void Scene::show(){;}
Scene::~Scene() { ; 
    clean_up();
}

StartScene::StartScene()
{
;
}

void StartScene::init()
{
    ImageManager* im = ImageManager::get_instance();
    background = im->get_image( ImageList::eMainBG);
    main_menu1 = im->get_image( ImageList::eMainMenu1);
    main_menu1_over = im->get_image( ImageList::eMainMenu1Un);
    main_menu2 = im->get_image( ImageList::eMainMenu2);
    main_menu2_over = im->get_image( ImageList::eMainMenu2Un);


        menu = 0;


	if(background == NULL)
	{
		;
	}
}
void StartScene::clean_up()
{
}
void StartScene::do_event()
{
    if( event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_RETURN: 
                if( menu == 0)
                    change_scene(SCENE_GAME );
                else
                    change_scene(SCENE_CREDIT);
                break;
            case SDLK_DOWN:
            case SDLK_UP:
                if( menu == 0)
                    menu = 1;
                else
                    menu = 0;
                break;
            default: break;
        }
    }
}

void StartScene::show()
{
	apply_surface(0,0,background,screen);
	apply_surface(160,240,main_menu1,screen);
	apply_surface(260,340,main_menu2,screen);
	if(menu == 1)
		apply_surface(160,240,main_menu1_over,screen);
	else
		apply_surface(260,340,main_menu2_over,screen);
	if( SDL_Flip(screen) == -1)
	{
		;
	//	return 1;
	}
}



BadEndScene::BadEndScene()
{
	;
}
void BadEndScene::init()
{
    ImageManager* im = ImageManager::get_instance();
    background = im->get_image( ImageList::eBadEnding);
	//background = load_image("game_ending_bad.png");


	if(background == NULL)
	{
		;
	}
}
void BadEndScene::clean_up()
{
}
void BadEndScene::do_event()
{
    if( event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_RETURN: 
                change_scene(SCENE_START);
                break;
            default: break;
        }
    }

}

void BadEndScene::show()
{
	apply_surface(0,0,background,screen);
	if( SDL_Flip(screen) == -1)
	{
		;
	//	return 1;
	}
}




GoodEndScene::GoodEndScene()
{
	;
}
void GoodEndScene::init()
{
    ImageManager* im = ImageManager::get_instance();
    background = im->get_image( ImageList::eHappyEnding);
//	background = load_image("game_ending_happy.png");


	if(background == NULL)
	{
		;
	}
}
void GoodEndScene::clean_up()
{
}
void GoodEndScene::do_event()
{
    if( event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_RETURN: 
                change_scene(SCENE_CREDIT);
                break;
            default: break;
        }
    }
}
void GoodEndScene::show()
{
	apply_surface(0,0,background,screen);
	if( SDL_Flip(screen) == -1)
	{
		;
	//	return 1;
	}
}



CreditScene::CreditScene()
{
	;
}
void CreditScene::init()
{
    fprintf(stderr, "before load credint.png (%s)\n",SDL_GetError());
    ImageManager* im = ImageManager::get_instance();
    background = im->get_image( ImageList::eCredit);

    fprintf(stderr, "before cannot load credint.png (%s)\n",SDL_GetError());
    if(background == NULL)
    {
        fprintf(stderr, "cannot load credint.png (%s)\n",SDL_GetError());
        ;
    }
}
void CreditScene::clean_up()
{
}
void CreditScene::do_event()
{
    if( event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_RETURN: 
                change_scene(SCENE_START);
                //change_scene(SCENE_GOODEND);
                break;
            default: break;
        }
    }

}

void CreditScene::show()
{
	apply_surface(0,0,background,screen);
	if( SDL_Flip(screen) == -1)
	{
		;
	//	return 1;
	}
}


