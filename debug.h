
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
bool debug_init();
void debug_print(std::string, SDL_Surface* screen );
void debug_clean_up();
