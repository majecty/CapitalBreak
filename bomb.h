
#pragma once

#include "common.h"
#include "Object.h"
#include "timer.h"
#include <vector>

class Bomb : public VisualObject 
{
    private:
        Timer timer;
        bool fired;
    public:
        Bomb(SDL_Rect pos);
        virtual void init();
        virtual void update();
        bool is_fired();

};

class BombManager : public Object
{
    private:
        std::vector<Bomb*> bombs;

    public:
        void put_bomb(SDL_Rect pos);
        virtual void update();
        virtual void show();
};




