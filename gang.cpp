
#include "global.h"
#include "common.h"
#include "character.h"
#include <stdint.h>
#include <time.h>
#include "timer.h"
<<<<<<< HEAD
=======
#include "object.h"
>>>>>>> big_reafactor

void Gang::init()
{
    srand(time(0));
	frame = 0;
	x = SCREEN_WIDTH/2 ;
	p_x = x;
	y = SCREEN_HEIGHT/2;
	p_y = y;
	w = 20;
	h = 30;
        xVel=0, yVel=0;
<<<<<<< HEAD
        if( image != NULL)
            image = load_image("character_gang.png");;
=======

        ImageManager* im = ImageManager::get_instance();
        image = im->get_image( ImageList::eGang);
        //image = load_image("character_gang.png");;
>>>>>>> big_reafactor
	set_clip();
}
void Gang::clean_up()
{
	//if( object_point != NULL)
	//	delete(object_point);
<<<<<<< HEAD
        if( image != NULL)
            SDL_FreeSurface(image);
=======
//        if( image != NULL)
//            SDL_FreeSurface(image);
>>>>>>> big_reafactor
}
void Gang::update()
{

    if( update_timer.is_started()) {
        if ( update_timer.get_ticks() > 500 ) {
            xVel = (rand() % 5-2);
            yVel = (rand() % 5-2);
            update_timer.start();
        }
    } else {
        update_timer.start();
    }

}
bool Gang::move(Uint32 deltaTicks)
{
	//if( follow() == false)
	//	return false;

	p_x = x;
	p_y = y;
	x += xVel * ((int32_t)deltaTicks / 10);
	if ( x < MAP_X) x = MAP_X;
	if ( x + w> MAP_X + MAP_W) x = MAP_X + MAP_W -w;
	y += yVel * ((int32_t)deltaTicks / 10);
	if ( y < MAP_Y) y = MAP_Y;
	if ( y  + h> MAP_Y + MAP_H) y = MAP_Y + MAP_H -h;


	//if( x == object_point->x && y == object_point->y) {
	//	object_point = NULL;
	//}

	return true;
	
}
void Gang::show(SDL_Surface* screen)
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

void Gang::set_clip()
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

bool Gang::check_collide(Collider* other)
{
	SDL_Rect* other_box;
	//SDL_Rect offset;
	other_box = other->get_box();

	if( x + w > other_box->x &&
			other_box->x + other_box->w > x)
	{
		if( y + h > other_box->y &&
				other_box->y + other_box->h > y)
		{
			
			//x = other_box->x + other_box->w;
			//y = other_box->y + other_box->h;
			return true;
		}
	}

	delete(other_box);

	return false;
}


SDL_Rect* Gang::get_box()
{
	SDL_Rect* box = new SDL_Rect();
	box->x = x;
	box->y = y;
	box->w = w;
	box->h = h;

	return box;

	
}

bool Gang::follow()
{
	if(object_point == NULL)
	{
		return false;
	} else {
		int div = CHAR_VELOCITY;
		//int div = 1/CHAR_VELOCITY;
		if(object_point->x < x) {
			xVel = -UNIT_WIDTH/div;
		} else if (object_point->x > x) {
			xVel = UNIT_WIDTH/div;
		} else {
			xVel = 0;
		}
		if(object_point->y < y) {
			yVel = -UNIT_HEIGHT/div;
		} else if (object_point->y > y) {
			yVel = UNIT_HEIGHT/div;
		} else {
			yVel = 0;
		}
	}
	return true;
}

void Gang::set_object(SDL_Rect* object)
{
	if( object_point != NULL)
		delete(object_point);
	object_point = object;
}

void Gang::move_back()
{
	x = p_x;
	y = p_y;
}
void Gang::add_person( ){
	if (next_person != NULL) {
		next_person->add_person();
	}
	else {
		next_person = new Gang();
		next_person->init();
	}

}
