
#ifndef __SCENE_H__
#define __SCENE_H__

#include "common.h"
#include "character.h"
#include "timer.h"
#include "collider.h"
#include "building.h"
#include "map.h"
#include <sstream>
#include <string>
#include "CPlayer.h"
#include "GlobalFunctions.h"

using namespace std;

class Scene {
	protected:
		SDL_Surface *background;
	public:
		virtual void init();
		virtual void clean_up();
		virtual void do_event();
		virtual void show();
                virtual ~Scene();

};

class MessageBox
{
    private:
        SDL_Rect rect;
        SDL_Surface* background;
        std::string message;
        std::string message2;
        Timer message_timer;
        Timer message_timer2;
    public:
        MessageBox(SDL_Surface* bg);
        void show();
        void show_message_box();
        void print_message_1(std::string msg, int duration);
        void print_message_2(std::string msg, int duration);

};

class WalletBar
{
	private:
		int frame;
		SDL_Rect offset;
		SDL_Rect cards[6];
		SDL_Rect cards_clip[6];
		SDL_Rect cards_limits_box[6];
		SDL_Rect cards_limits_clip[6];
		SDL_Rect card_gage[6];
		SDL_Surface* cards_image;
		SDL_Rect face_clip[6];
		SDL_Surface* faces_image;
	public:
		//WalletBar();
		void init(int x, int y, int w, int h);
		void clean_up();
		void show();
		void print_limit(ECard, uint64_t);
		void show_gage(ECard, float);
};

class Top
{
	private:
		SDL_Rect offset;
		std::string credit_str;
		std::string total_str;
	public:
		Top(int x, int y, int w, int h);
		//init();
		void show(SDL_Surface*);
		void set_credit_score(int credit);
		void set_total_dept(int total);

};

class StartScene : public Scene
{
	private:
		int menu;
		SDL_Surface* main_bg;
		SDL_Surface* main_menu1;
		SDL_Surface* main_menu1_over;
		SDL_Surface* main_menu2;
		SDL_Surface* main_menu2_over;
	public:
		StartScene();
		//StartScene();
		virtual void init();
		virtual void clean_up();
		virtual void do_event();
		virtual void show();

};
class BadEndScene : public Scene
{
	public:
		BadEndScene();
		//StartScene();
		virtual void init();
		virtual void clean_up();
		virtual void do_event();
		virtual void show();
};
class GoodEndScene: public Scene
{
	private:
	public:
		GoodEndScene();
		//StartScene();
		virtual void init();
		virtual void clean_up();
		virtual void do_event();
		virtual void show();
};
class CreditScene: public Scene
{
	public:
		CreditScene();
		//StartScene();
		virtual void init();
		virtual void clean_up();
		virtual void do_event();
		virtual void show();
};
class GameScene : public Scene
{
	private:
		bool happy_ending_flag;
		Hero *hero;
		Character* gang;
		Timer delta;
		Timer interest_timer;
		Map* map;
		Top* top;
		WalletBar* wallet;
                MessageBox* message_box_;

		int interest_count;
		int purchase_count;

                void handleInput();
                void handleUserEvent();
                void init_variables();
                void load_background_image();


	public:
		GameScene();
		virtual void init();
		virtual void clean_up();
		virtual void do_event();
		virtual void show();
		void check_collide();
};

#endif
