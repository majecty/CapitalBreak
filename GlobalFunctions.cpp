
#include <stdint.h>
#include "common.h"
#include "GlobalFunctions.h"
#include "Scene.h"
#include "valance.h"

double GetNonInterestTime(unsigned short pGrade, ERank pRank)
{
	switch(pRank)
	{
	case eFirstRank:
		{
			return (double)(pGrade + 7);
		}
		break;
	case eSecondRank:
		{
			return (double)(pGrade + 7)/2;
		}
		break;
	case eThirdRank:
		{
			double rv = (double)(pGrade - 5)/2;
			if(rv < 0)
				return 0;
			else
				return rv;
		}
		break;
	}

	return 0;
};

double GetRate(unsigned short pGrade, ERank pRank)
{
	switch(pRank)
	{
	case eFirstRank:
		{
                    return DEFAULT_RATE + (13-pGrade) * RATE_RATE;
			//return 0.06 + (13 - pGrade) * 0.000006364 * 1000000;
		}
		break;
	case eSecondRank:
		{
			return 30.0 + (13 - pGrade) * 6.362727273;
		}
		break;
	case eThirdRank:
		{
			return 100.0 + (13 - pGrade) * 27.27272727;
		}
		break;
	}

	return 1.0;
};

uint64_t GetGlobalLimit(unsigned short pGrade, ERank pRank)
{
	switch(pRank)
	{
	case eFirstRank:
		{
			return 100000 + 100000 * pGrade;
		}
		break;
	case eSecondRank:
		{
			return 1000000 + 1000000 * pGrade;
		}
		break;
	case eThirdRank:
		{
			return 10000000 + 10000000 * pGrade;
		}
		break;
	}

	return 0;
};
SDL_Surface *load_image( std::string filename) 
{

	SDL_Surface* loadedImage = NULL;

	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load( filename.c_str() );

	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat( loadedImage);

		SDL_FreeSurface( loadedImage);

		if (optimizedImage != NULL)
		{
			SDL_SetColorKey (optimizedImage, SDL_SRCCOLORKEY,
				SDL_MapRGB( optimizedImage->format,0,0xff,0xff));
		}
	}
	return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination,
		SDL_Rect* clip )
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface( source, clip, destination, &offset);
}

void lua_error(lua_State *L, const char *fmt, const char *at, ...);
void error(const char *fmt, const char *at, ...) ;


