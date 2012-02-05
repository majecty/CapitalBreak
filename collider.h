
#ifndef __MAJECTY_COLLIDER_H__
#define __MAJECTY_COLLIDER_H__
#include "common.h"

class Collider
{
	public:
		virtual bool check_collide(Collider*)=0;
		virtual SDL_Rect* get_box()=0;
};

#endif
