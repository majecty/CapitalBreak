
#include "common.h"
#include "Object.h"

void Object::init() { ;}
void Object::update() {;}
void Object::show() {;}
void Object::clean_up(){;}
void Object::print(){
    fprintf(stderr, "Here is Default Object's print function");
}

void VisualObject::set_image(SDL_Surface* img)
{
    image = img;
}

void VisualObject::show()
{
    apply_surface(position.x, position.y,image,screen);
}

ImageManager::ImageManager() { ; }
ImageManager::~ImageManager() 
{
    clean_up();
        
}

ImageManager* ImageManager::get_instance() 
{
    static ImageManager* p_instance = NULL;
    if ( p_instance == NULL) {
        p_instance = new ImageManager();
        p_instance->init();
    }

    return p_instance;
}

void ImageManager::init()
{
    static int count = 0;
    typedef std::pair<ImageList::Enum, SDL_Surface*> image_pair;
    struct {
        SDL_Surface* operator()(ImageList::Enum eName ) {
            return load_image( Image_Name[eName] );
        }
    } load;

    for( int enu = ImageList::ImageFirst; enu <= ImageList::ImageLast; enu++)
    {
        image_map.insert( image_pair((ImageList::Enum)enu , load((ImageList::Enum)enu)) );
    }

}

void ImageManager::clean_up()
{
    for(int enu = ImageList::ImageFirst;
            enu <= ImageList::ImageLast; enu++)
    {
        SDL_FreeSurface( image_map[(ImageList::Enum)enu] );
    }
}

SDL_Surface* ImageManager::get_image(ImageList::Enum name)
{
  return image_map[name];  
}
