#pragma once

#include <string>
#include "common.h"

// ������ �Ⱓ�� �� ������ ���Ѵ�.
double GetNonInterestTime(unsigned short pGrade, ERank pRank);

// �������� ���Ѵ�.
double GetRate(unsigned short pGrade, ERank pRank);

// ī���ѵ��� ���Ѵ�.
uint64_t GetGlobalLimit(unsigned short pGrade, ERank pRank);

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
SDL_Surface *load_image( std::string filename);
void change_scene(int scene_num);
