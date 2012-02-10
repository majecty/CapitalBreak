#include "common.h"
#include "Scene.h"
#include "lua_glue.h"


GameScene::GameScene()
{
	;
}

void GameScene::init_variables()
{

    happy_ending_flag = false;
    interest_count = 0;
    purchase_count= 0;
    message = "";
    message2 = "";

}

void GameScene::load_background_image()
{
    background = load_image("game_bg.png");

    if(background == NULL)
    {
        error("Failt to load GameScene's background\n",AT);
    }
}

void GameScene::init()
{
    init_variables();

    load_background_image();

    hero = new Hero();
    hero->init();
    map = new Map();
    wallet = new WalletBar();
    top = new Top(0,0, 640,30);
    message_box_ = new MessageBox(background);
    //message_box_->init();

    //message_box.x = MESSAGE_BOX_X;
    //message_box.y = MESSAGE_BOX_Y;
    //message_box.w = MESSAGE_BOX_W;
    //message_box.h = MESSAGE_BOX_H;
    //message_box_clip = message_box;



    apply_surface(0,0,background,screen);
    map->init(background);
    wallet->init(0,30,140,450);

    show_message_box();
    interest_timer.start();


    fire_message_event(eDescription);
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
    hero->handleInput();

    this->handleInput();

    this->handleUserEvent();

}
void GameScene::show()
{
	check_collide();


	hero->move(delta.get_ticks());


	top->set_credit_score(hero->get_grade());

	top->set_total_dept(hero->get_depth());


	map->show();

	top->show(background);

	hero->show(screen);

        message_box_->show();
	


	if ( purchase_count > SHOP_COUNT_FOR_UPGRADE)
	{
		hero->increase_grade();
		purchase_count = 0;
	}


	if( hero->has_card()) {

		uint64_t limit = hero->get_limit();
		uint64_t dept = hero->get_depth();


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
            fire_message_event(eHappyEnd);
			
	} else {
		//if( message_timer.get_ticks()> message_timer.period  )
		//{
                //        print_message_1("",1000);
		//	message_timer.stop();

		//}
		//if( message_timer2.get_ticks() > message_timer2.period  )
		//{
                //        print_message_2("",1000);
		//	message_timer2.stop();
		//}
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

//	SDL_Surface* message_surface = NULL; 
//	apply_surface(message_box.x, message_box.y,background,screen,&message_box_clip);
//
//	message_surface = TTF_RenderText_Solid( font, message.c_str(), textColor);
//	apply_surface(message_box.x, message_box.y+1,message_surface,screen);
//
//	message_surface = TTF_RenderText_Solid( font, message.c_str(), whiteColor);
//	apply_surface(message_box.x, message_box.y,message_surface,screen);
//
//	message_surface = TTF_RenderText_Solid( font, message2.c_str(), textColor);
//	apply_surface(message_box.x, message_box.y+50+1,message_surface,screen);
//
//	message_surface = TTF_RenderText_Solid( font, message2.c_str(), whiteColor);
//	apply_surface(message_box.x, message_box.y+50,message_surface,screen);

}

void GameScene::print_message_1_(std::string msg, int duration)
{
    message = msg;//"please press space bar to purchase";
    show_message_box();
    message_timer.start(duration);
}
void GameScene::print_message_1(std::string msg, int duration)
{
    message_box_->print_message_1(msg,duration);
}

void GameScene::print_message_2(std::string msg, int duration) 
{
    message_box_->print_message_2(msg,duration);

}
void GameScene::print_message_2_(std::string msg, int duration) 
{

    message2 = msg;//"You Purchase Clock";
    show_message_box();
    message_timer2.start(duration);

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
                                if (hero->is_indoor() == false ) {
                                    event.user.data1 = (void*)boxes[i];
                                    SDL_PushEvent(&event);
                                }
                                hero->enter_building();
			} else {
				hero->move_back();

			}

			return;
		}
	}
        hero->exit_building();
        hero->cant_buy();

}
void GameScene::handleInput()
{
    
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
                    
                    fire_message_event(eBuy);
                }
                break;
            default: break;
        }
    }
}

void GameScene::handleUserEvent()
{
    std::string *msg = NULL;
    Building* building = NULL;
    int* duration = NULL;

    if(event.type == SDL_USEREVENT)
    {
        switch(event.user.code)
        {
            case OPEN_DOOR_EVENT:
                building = (Building*)event.user.data1;


                if( building->card_id == 0)
                {
                    fire_message_event(eEnterShop);
                    hero->can_buy();
                } else {
                    fire_message_event(eEnterCardShop);
                    hero->add_card((ECard)building->card_id);
                    hero->select_card((ECard)building->card_id);
                }

                break;
            case MESSAGE_BOX_1_EVENT:
                msg = (std::string*)event.user.data1;
                duration = (int*)event.user.data2;
                //print_message_1(*msg, (int)event.user.data2);
                print_message_1(*msg, *duration);
                //fprintf(stderr, "duration is : %d",(int)event.user.data2);
                delete(msg);
                delete(duration);
                break;
            case MESSAGE_BOX_2_EVENT:
                msg = (std::string*)event.user.data1;
                duration = (int*)event.user.data2;
                print_message_2(*msg,*duration);
                //print_message_2(*msg, (int)event.user.data2);
                delete(msg);
                delete(duration);
                break;
            default:
                break;
        }
    }

}

