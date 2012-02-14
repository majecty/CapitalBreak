

#pragma once
#include <map>


class Object
{

    public:
        virtual void init();
        virtual void update();
        virtual void show();
        virtual void clean_up();
        virtual void print();
};

class VisualObject : public Object 
{
    public:
        SDL_Surface* image;
        SDL_Rect position;
        SDL_Rect* clips;
        virtual void set_image(SDL_Surface* img);
        virtual void show();

};

class ImageManager
{
    private:
        std::map<ImageList::Enum, SDL_Surface*> image_map;
        ImageManager();


    public:
        ~ImageManager();
        void init();
        void clean_up();
        static ImageManager* get_instance();
        SDL_Surface* get_image(ImageList::Enum name);
};
