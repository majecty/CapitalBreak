#include "common.h"
#include "global.h"
#include "valance.h"
#include "Scene.h"
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
	while( SDL_PollEvent( &event))
	{
		hero->handleInput();
		if( event.type == SDL_QUIT)
		{
			quit = true;
		}
		else if( event.type == SDL_KEYDOWN)
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
						message2 = "You Purchase Clock";
						show_message_box();
						message_timer2.start();
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
						message = "please press space bar to purchase";
						message_timer.start();
						hero->can_buy();
					} else {
						hero->add_card((ECard)building->card_id);
						hero->select_card((ECard)building->card_id);
					}


					break;
				default:
					break;
			}
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
			
		message = "Hurry up, Press End Key";
		message2 = "Go to the Abroad!";
		show_message_box();

	} else {
		if( message_timer.get_ticks()/100.0f > 1)
		{
			message = "";
			show_message_box();
			message_timer.stop();
			hero->cant_buy();

		}
		if( message_timer2.get_ticks()/100.0f > 1)
		{
			message2 = "";
			show_message_box();
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


void GameScene::init_building()
{
	//first_building = new Building(180,70);
	//first_building->init();
}

Top::Top(int x, int y, int w, int h)
{
	offset.x = x;
	offset.y = y;
	offset.w = w;
	offset.h = h;


	credit_str = "";
	total_str = "";
}

void Top::set_credit_score(int credit)
{

	credit_str = gGradeName[credit];

}

void Top::set_total_dept(int total)
{
	total_str = "";
	std::ostringstream result;
	result << total;
	total_str += result.str();
}
void Top::show(SDL_Surface* background)
{
	SDL_Surface depth;
	SDL_Surface grade;
//	set_total_dept(hero->get_depth());
	depth = *TTF_RenderText_Solid( font, total_str.c_str(), textColor);
	grade = *TTF_RenderText_Solid(font, credit_str.c_str(), textColor);
	
	apply_surface(offset.x,offset.y,background,screen,&offset);
	apply_surface(400,5,&depth,screen);
	apply_surface(240,5,&grade,screen);
}
void WalletBar::init(int x, int y, int w, int h)
{
	cards_image = load_image("game_1s_card.png");
	faces_image = load_image("game_face.png");
	offset.x = x; offset.y = y; offset.w = w; offset.h = h;

	for(int i=0;i<6;i++) {
		cards[i].x = 10;
		cards[i].y = 175 + i* 50;
		cards[i].w = 120;
		cards[i].h = 50;
	}
	for(int i=0;i<6;i++) {
		cards_clip[i].x = 0;
		cards_clip[i].y = 50*i;
		cards_clip[i].w = 120;
		cards_clip[i].h = 50;
	}
	for(int i=0;i<6;i++)
	{
		cards_limits_box[i].x = 13 + cards[i].x;
		cards_limits_box[i].y = 13 + cards[i].y;
		cards_limits_box[i].w = 60;
		cards_limits_box[i].h = 10;
	}
	for(int i=0;i<6;i++)
	{
		cards_limits_clip[i].x = 20 + cards_clip[i].x;
		cards_limits_clip[i].y = 13 + cards_clip[i].y;
		cards_limits_clip[i].w = 60;
		cards_limits_clip[i].h = 10;
	}
	for( int i=0;i<6;i++)
	{
		face_clip[i].x = (i%2) * 116;
		face_clip[i].y = (i/2) * 116;
		face_clip[i].w = 116;
		face_clip[i].h = 116;
	}

	for(int i=0;i<6;i++) {
		apply_surface(cards[i].x,cards[i].y, cards_image, screen, &cards_clip[i]);
	}
}

void WalletBar::clean_up()
{

	SDL_FreeSurface(cards_image);
	SDL_FreeSurface(faces_image);
}

void WalletBar::show( )
{
	apply_surface(12,42,faces_image, screen, &face_clip[frame%6]);
	frame++;
	;
}
void WalletBar::show_gage(ECard i, float ratio)
{
    int building_id = i - 1; // building id  is start from 1
	SDL_Rect box;
	box.x = cards_limits_box[building_id].x;
	box.y = cards_limits_box[building_id].y;
	box.w = (int)(cards_limits_box[building_id].w * ratio);
	box.h = cards_limits_box[building_id].h;
	SDL_FillRect(screen,&box, SDL_MapRGB(screen->format, 0,0,0));

}

void WalletBar::print_limit(ECard i, uint64_t money)
{
	std::ostringstream result;
	result << money;
	//total_str += result.str();
	SDL_Surface* message_surface = NULL; 

	apply_surface(cards_limits_box[i].x, cards_limits_box[i].y,cards_image,screen,&cards_limits_clip[i]);

	message_surface = TTF_RenderText_Solid( font, result.str().c_str(), textColor);
	apply_surface(cards_limits_box[i].x, cards_limits_box[i].y+1,message_surface,screen);

	
}


