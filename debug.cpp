#include "common.h"
#include "global.h"
#include "debug.h"

//static TTF_Font *font = NULL;
//static SDL_Color textColor = {0,0,0};

bool debug_init()
{
	font = TTF_OpenFont("SangSangTitleM.ttf", 25);

	if(font == NULL)
	{
		return false;
	}
	return true;
}
void debug_print(std::string debug_string , SDL_Surface* screen )
{
	SDL_Rect debug_box;
	SDL_Surface* debug_message = NULL; 

	debug_box.x = 40;
	debug_box.y = SCREEN_HEIGHT - 110;
	debug_box.w = SCREEN_WIDTH - 80;
	debug_box.h = 100;

	debug_message = TTF_RenderText_Solid( font, debug_string.c_str(), textColor);
	SDL_FillRect(screen, &debug_box, SDL_MapRGB(screen->format, 0,255,255));

	apply_surface(50, SCREEN_HEIGHT-100,debug_message,screen);

}

void debug_clean_up()
{
	TTF_CloseFont( font);
}
