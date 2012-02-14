


#include "bomb.h"
#include "Object.h"


Bomb::Bomb(SDL_Rect pos)
{
    position.x = pos.x;
    position.y = pos.y;
    init();
}

void Bomb::init()
{
    fired = false;
    timer.start(100000);
    ImageManager* im = ImageManager::get_instance();
    set_image(im->get_image(ImageList::eBomb ));
    
}

void Bomb::update()
{
    if( timer.period > timer.get_ticks()) {
        // add fire event and delete bomb
        fired = true;
    }
}

bool Bomb::is_fired()
{
    return fired;
}

void BombManager::put_bomb(SDL_Rect pos)
{
    bombs.push_back( new Bomb(pos));
}

void BombManager::update()
{
    std::vector<Bomb*>::iterator it;

    for( it=bombs.begin(); it < bombs.end(); ) {
        (*it )-> update();

//        if( (*it) -> is_fired()) {
//            delete(*it);
//            it = bombs.erase(it);
//        } else
            it++;
    }
    // update bomb's timer
}

void BombManager::show()
{
    std::vector<Bomb*>::iterator it;
    for( it=bombs.begin(); it< bombs.end(); it++) {
        (*it)->show();
        fprintf(stderr,"showing bombs in bm at : %s\n",AT);
    }
}
