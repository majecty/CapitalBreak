#include "common.h"
#include "Scene.h"
#include "lua_glue.h"


GameScene::GameScene()
{
	;
}

void GameScene::init()
{
    init_variables();

    load_background_image();

    apply_surface(0,0,background,screen);

    init_GUI_objects();

    interest_timer.start();

    fire_message_event(eDescription);

    delta_time.start();

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

void GameScene::do_logic()
{

    check_collide();

    hero->move(delta_time.get_ticks());

    increase_grade();

    show_gage();

    print_happy_end_message();

    update_interest();
}

void GameScene::update_interest()
{
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
}
void GameScene::show()
{

    do_logic();

    top->set_credit_score(hero->get_grade());

    top->set_total_dept(hero->get_depth());


    map->show();

    top->show(background);

    hero->show(screen);

    message_box_->show();



    if( SDL_Flip(screen) == -1)
    {
        ;
        fprintf(stderr,"screen refresh error");
        //	return 1;
    }

    delta_time.start();

    check_game_end();
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
                message_box_->print_message_1(*msg, *duration);
                delete(msg);
                delete(duration);
                break;
            case MESSAGE_BOX_2_EVENT:
                msg = (std::string*)event.user.data1;
                duration = (int*)event.user.data2;
                message_box_->print_message_2(*msg, *duration);
                delete(msg);
                delete(duration);
                break;
            default:
                break;
        }
    }

}

void GameScene::init_variables()
{

    happy_ending_flag = false;
    interest_count = 0;
    purchase_count= 0;

}

void GameScene::load_background_image()
{
    background = load_image("game_bg.png");

    if(background == NULL)
    {
        error("Failt to load GameScene's background\n",AT);
    }
}

void GameScene::init_GUI_objects()
{

    hero = new Hero();
    map = new Map();
    wallet = new WalletBar();
    top = new Top(0,0, 640,30);
    message_box_ = new MessageBox(background);

    hero->init();
    map->init(background);
    wallet->init(0,30,140,450);
}

void GameScene::increase_grade()
{

    if ( purchase_count > SHOP_COUNT_FOR_UPGRADE)
    {
        hero->increase_grade();
        purchase_count = 0;
    }
}

void GameScene::show_gage()
{
    if( hero->has_card()) {

        uint64_t limit = hero->get_limit();
        uint64_t dept = hero->get_depth();


        wallet->show_gage(hero->get_current_card(),dept/(float)limit);


    }
}
void GameScene::check_game_end()
{
    if( hero->has_card()) {
        uint64_t limit = hero->get_limit();
        if ( hero-> get_depth() > limit)
            change_scene(SCENE_BADEND);
    }
    if( hero-> get_grade() < 1)
    {
        change_scene(SCENE_BADEND);
    }
}

void GameScene::print_happy_end_message()
{
    if( hero -> get_grade() < 3)
    {
        happy_ending_flag = true;

        fire_message_event(eHappyEnd);
    }


}
