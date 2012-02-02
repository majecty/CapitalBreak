

#include "building.h"
#include "global.h"
#include "Configuration.h"

Building::Building(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}
void Building::init(ECard pCard)
{
	card_id = (int)pCard;
	if( card_id ==  0) {
		depart_image = load_image("game_dept.png");
		door = new Door(x,y, 35, 55, 110,15);
	} else {
		depart_image = NULL;
		door = new Door(x,y);
	}

	clip.x = 0;
	clip.y =  card_id * 70 - 70;
	clip.w = 120;
	clip.h = 70;

	if( card_id ==  0) {
		clip.x = 0;
		clip.y = 0;
		clip.w = 115;
		clip.h = 70;
	}


	if(depart_image== NULL)
	{
		;
	}
}
void Building::show()
{
	if(depart_image == NULL) {
		apply_surface(x,y,buildings_image,screen,&clip);
	} else {
		apply_surface(x,y,depart_image,screen);
	}
}
void Building::clean_up()
{
	if (depart_image != NULL)
		SDL_FreeSurface(depart_image);
}

bool Building::check_collide(Collider* other)
{
	SDL_Rect* other_box;
	other_box = other->get_box();

	if( x + w > other_box->x &&
			other_box->x + other_box->w > x)
	{
		if( y + h > other_box->y &&
				other_box->y + other_box->h > y)
		{
			return true;
		}
	}

	delete(other_box);

	return false;
}

SDL_Rect* Building::get_box()
{
	SDL_Rect* box = new SDL_Rect();
	box->x = x;
	box->y = y;
	box->w = w;
	box->h = h;

	return box;

	
}
Door* Building::get_door()
{
	return door;
}
Door::Door(int building_x,int building_y, int _x , int _y, int _w, int _h)
{
	x = _x+ building_x;
	y = _y+ building_y;
	w = _w;
	h = _h;
}

bool Door::check_collide(Collider* other)
{
	SDL_Rect* other_box;
	other_box = other->get_box();

	if( x + w > other_box->x &&
			other_box->x + other_box->w > x)
	{
		if( y + h > other_box->y &&
				other_box->y + other_box->h > y)
		{
			return true;
		}
	}

	delete(other_box);

	return false;
}

SDL_Rect* Door::get_box()
{
	SDL_Rect* box = new SDL_Rect();
	box->x = x;
	box->y = y;
	box->w = w-20;
	box->h = h;

	return box;

	
}



