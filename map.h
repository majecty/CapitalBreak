
#ifndef __MAJECTY_MAP_H_
#define __MAJECTY_MAP_H_

#include "common.h"
#include "building.h"
#include <vector>
using namespace std;


const int FIRSTBUILDING_NUM  = 6;
const int SECONDBUILDING_NUM  = 4;
const int THIRDBUILDING_NUM  = 3;

class Map
{
	protected:

		int x,y;
		int w,h;
                SDL_Surface* buildings_image;
		SDL_Surface* background;
		vector<Building*> buildings;
		vector<SDL_Rect*> boxes;
		SDL_Rect clip;

	public:
		void init(SDL_Surface* back);
		void show();
		void clean_up();
		vector<SDL_Rect*> get_boxes(); // for collide
		vector<Building*> get_buildings();


};

#endif
