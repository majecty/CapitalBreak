#include "global.h"
#include "Configuration.h"
#include "common.h"
#include "character.h"
#include <stdint.h>

void Character::init() {;}
bool Character::move(Uint32 deltaTicks) {return true ;}
void Character::clean_up(){;}
void Character::show(SDL_Surface*){;}
void Character::set_clip(){;}
void Character::add_person(){
	if (next_person != NULL) {
		next_person->add_person();
	}
	else {
		//next_person = _next_person;
		next_person = new Gang();
		next_person->init();
	}

}
void Character::set_object(SDL_Rect *object){;}
void Character::move_back()
{
	x = p_x;
	y = p_y;
}
Character::~Character()
{

}

void Hero::init()
{
        indoor = false;
	is_buyable = false;
	frame = 0;
	x = SCREEN_WIDTH/2;
	p_x = x;
	y = SCREEN_HEIGHT/2;
	p_y = y;
	w = 20;
	h = 30;
	xVel = 0;
	yVel = 0;
	next_person = NULL;
	image = load_image("character_hero.png");;
	set_clip();

	aPlayer.SetRank(eFirstRank);
}

void Hero::clean_up()
{
	SDL_FreeSurface(image);
}
bool Hero::move(Uint32 deltaTicks)
{
	p_x = x;
	p_y = y;
	x += xVel* ((int32_t)deltaTicks / 10);
	if ( x < MAP_X) x = MAP_X;
	if ( x + w > MAP_X + MAP_W) x = MAP_X + MAP_W - w;
	y += yVel* ((int32_t)deltaTicks / 10);
	if ( y < MAP_Y) y = MAP_Y;
	if ( y  +  h> MAP_Y + MAP_H) y = MAP_Y + MAP_H -h;

	return true;
}
void Hero::show(SDL_Surface* screen)
{
	int status = DOWN;

	if( xVel > 0)
	{
		status = RIGHT;
		frame++;
	} else if ( xVel < 0)
	{
		status = LEFT;
		frame++;
	}else if ( yVel > 0)
	{
		status = DOWN;
		frame++;
	
	}else if (yVel < 0)
	{
		status = UP;
		frame++;
	
	}else {
		frame = 0;
	}
	if( frame > 8) {
		frame = 0;
	}
	if( frame/2 <= 2)
		apply_surface(x,y,image,screen, &clip[status][frame/2]);
	else if( frame/2 == 3)
		apply_surface(x,y,image,screen, &clip[status][1]);
	else
		apply_surface(x,y,image,screen, &clip[status][0]);

}

// ------ Hero's private method 
//
void Hero::put_bomb()
{
    
}

void Hero::handleInput()
{
	int div = CHAR_VELOCITY;
	//int div = 1/CHAR_VELOCITY;

	if( event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: yVel -= UNIT_HEIGHT/div;
				//y-=UNIT_HEIGHT/div;
				break;
			case SDLK_DOWN: yVel += UNIT_HEIGHT/div; break;
			case SDLK_LEFT: xVel -= UNIT_WIDTH/div; 
				//x-=UNIT_HEIGHT/div;
				break;
			case SDLK_RIGHT: xVel += UNIT_WIDTH/div; break;
			default: break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: yVel += UNIT_HEIGHT/div; break;
			case SDLK_DOWN: yVel -= UNIT_HEIGHT/div; break;
			case SDLK_LEFT: xVel += UNIT_WIDTH/div; break;
			case SDLK_RIGHT: xVel -= UNIT_WIDTH/div; break;
			default: break;
		}
	}
}

bool Hero::check_collide(Collider* other)
{
	SDL_Rect* other_box;
	SDL_Rect offset;
	other_box = other->get_box();

	

	if( x + w > other_box->x +5 &&
			other_box->x + other_box->w - 5> x)
	{
		if( y + h > other_box->y + 5&&
				other_box->y + other_box->h - 5 > y)
		{
			
			//x = other_box->x + other_box->w;
			//y = other_box->y + other_box->h;
			return true;
		}
	}

	delete(other_box);

	return false;
}
void Hero::set_clip()
{
	clip[DOWN][0].x = 0;
	clip[DOWN][0].y = 0;
	clip[DOWN][0].w = UNIT_WIDTH;
	clip[DOWN][0].h = UNIT_HEIGHT;

	clip[DOWN][1].x = UNIT_WIDTH;
	clip[DOWN][1].y = 0;
	clip[DOWN][1].w = UNIT_WIDTH;
	clip[DOWN][1].h = UNIT_HEIGHT;

	clip[DOWN][2].x = UNIT_WIDTH * 2;
	clip[DOWN][2].y = 0;
	clip[DOWN][2].w = UNIT_WIDTH;
	clip[DOWN][2].h = UNIT_HEIGHT;

	clip[LEFT][0].x = 0;
	clip[LEFT][0].y = UNIT_HEIGHT;
	clip[LEFT][0].w = UNIT_WIDTH;
	clip[LEFT][0].h = UNIT_HEIGHT;

	clip[LEFT][1].x = UNIT_WIDTH;
	clip[LEFT][1].y = UNIT_HEIGHT;
	clip[LEFT][1].w = UNIT_WIDTH;
	clip[LEFT][1].h = UNIT_HEIGHT;

	clip[LEFT][2].x = UNIT_WIDTH * 2;
	clip[LEFT][2].y = UNIT_HEIGHT;
	clip[LEFT][2].w = UNIT_WIDTH;
	clip[LEFT][2].h = UNIT_HEIGHT;

	clip[RIGHT][0].x = 0;
	clip[RIGHT][0].y = UNIT_HEIGHT * 2;
	clip[RIGHT][0].w = UNIT_WIDTH;
	clip[RIGHT][0].h = UNIT_HEIGHT;

	clip[RIGHT][1].x = UNIT_WIDTH;
	clip[RIGHT][1].y = UNIT_HEIGHT * 2;
	clip[RIGHT][1].w = UNIT_WIDTH;
	clip[RIGHT][1].h = UNIT_HEIGHT;

	clip[RIGHT][2].x = UNIT_WIDTH * 2;
	clip[RIGHT][2].y = UNIT_HEIGHT * 2;
	clip[RIGHT][2].w = UNIT_WIDTH;
	clip[RIGHT][2].h = UNIT_HEIGHT;

	clip[UP][0].x = 0;
	clip[UP][0].y = UNIT_HEIGHT * 3;
	clip[UP][0].w = UNIT_WIDTH;
	clip[UP][0].h = UNIT_HEIGHT;

	clip[UP][1].x = UNIT_WIDTH;
	clip[UP][1].y = UNIT_HEIGHT * 3;
	clip[UP][1].w = UNIT_WIDTH;
	clip[UP][1].h = UNIT_HEIGHT;

	clip[UP][2].x = UNIT_WIDTH * 2;
	clip[UP][2].y = UNIT_HEIGHT * 3;
	clip[UP][2].w = UNIT_WIDTH;
	clip[UP][2].h = UNIT_HEIGHT;
}


SDL_Rect* Hero::get_box()
{
	SDL_Rect* box = new SDL_Rect();
	box->x = x;
	box->y = y;
	box->w = w;
	box->h = h;

	return box;

	
}

void Hero::move_back()
{
	x = p_x;
	y = p_y;
	if( next_person != NULL)
		next_person->move_back();
}

void Hero::add_person( ){
	if (next_person != NULL) {
		next_person->add_person();
	}
	else {
		next_person = new Gang();
		next_person->init();
		next_person->move(100);
	}

}

bool Hero::buy()
{
	if( is_buyable) {
		aPlayer.BuySomething(100000);
		return true;
	}
	else return false;
}

void Hero::can_buy()
{
	is_buyable = true;
}
void Hero::cant_buy()
{
	is_buyable = false;
}
uint64_t Hero::get_depth()
{
	return aPlayer.GetDept();
}
int Hero::calc_dept()
{
	return aPlayer.CalcDept();
}

void Hero::add_card(ECard pCard )
{
	aPlayer.AddCard(pCard);
}
void Hero::select_card(ECard pCard )
{
	aPlayer.SelectCard(pCard);
}

ECard Hero::get_current_card()
{
	CCard* card;
	card = aPlayer.GetCurrentCard();
	return (ECard)card->GetCardNo();
	
}

uint64_t Hero::get_limit()
{
	CCard* card;
	card = aPlayer.GetCurrentCard();
	return card->GetLimit();
}
bool Hero::has_card()
{
	CCard* card;
	card = aPlayer.GetCurrentCard();
	if (card != NULL)
		return true;
	else
		return false;
}

unsigned short Hero::get_grade()
{
	return aPlayer.GetGrade();
}

void Hero::decrease_grade()
{
	aPlayer.DecreaseGrade();
}
void Hero::increase_grade()
{
	aPlayer.IncreaseGrade();
}
bool Hero::is_indoor()
{
    return  indoor;
}
void Hero::enter_building()
{
    indoor = true;
}
void Hero::exit_building()
{
    indoor = false;
}
