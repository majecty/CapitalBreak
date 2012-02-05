
#ifndef __MAJECTY_BUILDING_H_
#define __MAJECTY_BUILDING_H_

#include "common.h"
#include "collider.h"
#include "global.h"
#include "Constants.h"


class Door : public Collider
{
	private:
		int x,y;
		int w,h;
	public:
		Door(int building_x, int building_y, int _x = DOOR_X, int _y = DOOR_Y, int _w= DOOR_W, int _h = DOOR_H);
		virtual bool check_collide(Collider*);
		virtual SDL_Rect* get_box();
};

class Building : public Collider
{
	private:
		int x,y;
		int w,h;
		SDL_Surface *depart_image;
                SDL_Surface *buildings_image;
		Door *door;
		SDL_Rect clip;
	public:
		int card_id;
		Building(int _x, int _y,int _w, int _h, SDL_Surface* bs_image);
		//void init(int id);
		void init(ECard pCard);
		virtual bool check_collide(Collider*);
		virtual SDL_Rect* get_box();
		void clean_up();
		void show();
		Door* get_door();

};
#endif
