#pragma once

#include <string>
#include "common.h"
extern "C" {
#include "lua/lua.h"
}
//#include "lua/lua.hpp"

// 무이자 기간을 초 단위로 구한다.
double GetNonInterestTime(unsigned short pGrade, ERank pRank);

// 이자율을 구한다.
double GetRate(unsigned short pGrade, ERank pRank);

// 카드한도를 구한다.
uint64_t GetGlobalLimit(unsigned short pGrade, ERank pRank);

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface*
        destination, SDL_Rect* clip = NULL);
SDL_Surface *load_image( std::string filename);
void change_scene(int scene_num);

//void error_in_lua(lua_State *L, const char *fmt, const char *at, ...);
void maj_lua_error(lua_State*, const char*, const char*, ...);
void error(const char *fmt, const char *at, ...) ;
