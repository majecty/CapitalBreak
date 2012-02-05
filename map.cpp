


#include "map.h"
#include "global.h"


void Map::init(SDL_Surface* back)
{
    buildings_image = load_image("game_1s_building.png");
    if(buildings_image == NULL)
    {
        error("ERROR: When load default building image",AT);
    }
	Building* building;
	x = MAP_X;
	y = MAP_Y;
	w = MAP_W;
	h = MAP_H;
	//background = load_image("map.png");
	background = back;

	clip.x = x;
	clip.y = y;
	clip.w = w;
	clip.h = h;

	building = new Building(180,70,115,70, buildings_image);
	boxes.push_back(building->get_box());
	buildings.push_back(building);
	building->init(eCardVissa);

	building = new Building(330,70,115,70, buildings_image);
	boxes.push_back(building->get_box());
	buildings.push_back(building);
	building->init(eCardMister);

	building = new Building(480,70,115,70, buildings_image);
	boxes.push_back(building->get_box());
	buildings.push_back(building);
	building->init(eCardAmerican);


	building = new Building(180+130,170,170,70, buildings_image);
	boxes.push_back(building->get_box());
	buildings.push_back(building);
	building->init(eCardNon);


	building = new Building(180,270,115,70, buildings_image);
	boxes.push_back(building->get_box());
	buildings.push_back(building);
	building->init(eCardUnion);

	building = new Building(330,270,115,70, buildings_image);
	boxes.push_back(building->get_box());
	buildings.push_back(building);
	building->init(eCardJHT);

	building = new Building(480,270,115,70, buildings_image);
	boxes.push_back(building->get_box());
	buildings.push_back(building);
	building->init(eCardDC);

}

void Map::show()
{
	apply_surface(x,y,background,screen,&clip);
	for( int i=0;i<(int)buildings.size();i++){
		buildings[i]->show();
	}

}
void Map::clean_up()
{
//    SDL_FreeSurface(buildings_image);
}

vector<SDL_Rect*> Map::get_boxes()
{
	return boxes;
}

vector<Building*> Map::get_buildings()
{
	return buildings;
}
