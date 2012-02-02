#include "common.h"
#include "Scene.h"
#include "lua_glue.h"
//#include "character.h"


GameScene::GameScene()
{
	;
}
void GameScene::init()
{
	happy_ending_flag = false;
	interest_count = 0;
	purchase_count= 0;

	background = load_image("game_bg.png");
	hero = new Hero();
	hero->init();
	message = "";
	message2 = "";
	map = new Map();
	map->init(background);
	wallet = new WalletBar();

	top = new Top(0,0, 640,30);
		



	message_box.x = MESSAGE_BOX_X;
	message_box.y = MESSAGE_BOX_Y;
	message_box.w = MESSAGE_BOX_W;
	message_box.h = MESSAGE_BOX_H;
	message_box_clip = message_box;




	if(background == NULL)
	{
		;
	}
	apply_surface(0,0,background,screen);

	show_message_box();
	interest_timer.start();
	wallet->init(0,30,140,450);
	delta.start();
}
void GameScene::clean_up()
{
	hero->clean_up();
	map->clean_up();

	SDL_FreeSurface(background);

	if( hero!= NULL)
		delete(hero);
	delete(map);
	delete(top);
}
void GameScene::do_event()
{
    Building* building;
    std::ostringstream result;
    std::string *msg = NULL;

    hero->handleInput();

    if( event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                change_scene(SCENE_GOODEND);
                break;
            case SDLK_RETURN: 
                break;
            case SDLK_SPACE:
                if( hero->buy()) {
                    purchase_count++;
                    
                    print_message_2("You Purchased Clock");
//                    message2 = "You Purchase Clock";
//                    show_message_box();
//                    message_timer2.start();
                }
                break;
            default: break;
        }
    }
    else if(event.type == SDL_USEREVENT)
    {
        switch(event.user.code)
        {
            case OPEN_DOOR_EVENT:
                building = (Building*)event.user.data1;


                if( building->card_id == 0)
                {
                    print_message_1("please press space bar to purchae");
//                    message = "please press space bar to purchase";
//                    message_timer.start();
                    hero->can_buy();
                } else {
                    fire_lua_event(MESSAGE_BOX_1_EVENT);
                    //print_message_1("You Get the Card");
                    hero->add_card((ECard)building->card_id);
                    hero->select_card((ECard)building->card_id);
                }

                break;
            case MESSAGE_BOX_1_EVENT:
                //fprintf(stderr,"At %s : hereis messageevent",AT);
                msg = (std::string*)event.user.data1;
                print_message_1(*msg);
                delete(msg);
                break;
            case MESSAGE_BOX_2_EVENT:
                //fprintf(stderr,"At %s : hereis messageevent",AT);
                msg = (std::string*)event.user.data1;
                print_message_2(*msg);
                delete(msg);
                break;
            default:
                break;
        }
    }

}
void GameScene::show()
{

	map->show();

	hero->move(delta.get_ticks());

	check_collide();

	top->set_credit_score(hero->get_grade());

	top->set_total_dept(hero->get_depth());

	top->show(background);

	hero->show(screen);
	


	if ( purchase_count > 30 )
	{
		hero->increase_grade();
		purchase_count = 0;
	}


	if( hero->has_card()) {

		uint64_t limit = hero->get_limit();
		uint64_t dept = hero->get_depth();

		//wallet->print_limit(hero->get_current_card(),limit );

		wallet->show_gage(hero->get_current_card(),dept/(float)limit);

		if ( hero-> get_depth() > limit)
			change_scene(SCENE_BADEND);


	}

	if( hero -> get_grade() < 3)
	{
		happy_ending_flag = true;
		if( hero-> get_grade() < 1)
		{
			change_scene(SCENE_BADEND);
		}

	}
	if( happy_ending_flag) {
			
            print_message_1("Hurry up, Press End Key");
            print_message_2("Go to the Abroad!");
//		message = "Hurry up, Press End Key";
//		message2 = "Go to the Abroad!";
//		show_message_box();

	} else {
		if( message_timer.get_ticks()/100.0f > 1)
		{
//			message = "";
//			show_message_box();
                    print_message_1("");
			message_timer.stop();
			hero->cant_buy();

		}
		if( message_timer2.get_ticks()/1000.0f > 1)
		{
//			message2 = "";
//			show_message_box();
                    print_message_2("");
			message_timer2.stop();
		}
	}
	if( interest_timer.get_ticks()/1000.0f > 1)
	{
		wallet->show();
		hero->calc_dept();
		interest_timer.start();
		interest_count++;
		if (interest_count > 12)
		{
			interest_count =0;
			hero->decrease_grade();
		}
	}

	if( SDL_Flip(screen) == -1)
	{
		;

                fprintf(stderr,"screen refresh error");
	//	return 1;
	}
	delta.start();
}
void GameScene::show_message_box(){

	SDL_Surface* message_surface = NULL; 
	apply_surface(message_box.x, message_box.y,background,screen,&message_box_clip);

	message_surface = TTF_RenderText_Solid( font, message.c_str(), textColor);
	apply_surface(message_box.x, message_box.y+1,message_surface,screen);

	message_surface = TTF_RenderText_Solid( font, message.c_str(), whiteColor);
	apply_surface(message_box.x, message_box.y,message_surface,screen);

	message_surface = TTF_RenderText_Solid( font, message2.c_str(), textColor);
	apply_surface(message_box.x, message_box.y+50+1,message_surface,screen);

	message_surface = TTF_RenderText_Solid( font, message2.c_str(), whiteColor);
	apply_surface(message_box.x, message_box.y+50,message_surface,screen);

}
void GameScene::check_collide()
{
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = OPEN_DOOR_EVENT;

	vector<Building*> boxes = map->get_buildings();
	for(int i=0; i<(int)boxes.size();i++) {
		if (hero -> check_collide(boxes[i]) == true) {
			if( hero->check_collide(boxes[i]->get_door())){
				event.user.data1 = (void*)boxes[i];
				SDL_PushEvent(&event);
			} else {
				hero->move_back();
			}

			return;
		}
	}

}

void GameScene::print_message_1(std::string msg)
{
    message = msg;//"please press space bar to purchase";
    show_message_box();
    message_timer.start();
}

void GameScene::print_message_2(std::string msg) 
{

    message2 = msg;//"You Purchase Clock";
    show_message_box();
    message_timer2.start();
}



