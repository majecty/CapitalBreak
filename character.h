
#ifndef _MAJECTY_CHAR_H__
#define _MEJECTY_CHAR_H__
#include "common.h"
#include "collider.h"
#include "CPlayer.h"
#include "Constants.h"
#include "timer.h"

const int DOWN = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int UP = 3;
const int STOP = 4;

class Character 
{
	private:
		Character* next_person;

	protected:
		int w, h;
		int xVel, yVel;
		SDL_Surface *image;
		int frame;
		SDL_Rect clip[4][3];// 8 ¿∫ ≥À≥À¿‚¿∫ º˝

	public:
		int x, y, p_x, p_y;
                virtual ~Character();
		virtual bool move(Uint32 deltaTicks);
		virtual void init();
		virtual void clean_up();
		virtual void show(SDL_Surface*);
		virtual void set_clip();
		virtual void add_person();
		virtual void set_object(SDL_Rect *object);
		virtual void move_back();
};

class Hero : public Character ,public Collider
{
	private:
		Character* next_person;
		bool is_buyable;
		CPlayer  aPlayer;
                bool indoor;
	public:
		virtual void init();
		virtual void clean_up();
		virtual bool move(Uint32 deltaTicks);
		virtual void show(SDL_Surface*);
		virtual void set_clip();
		virtual void add_person();

		virtual bool check_collide(Collider*);

		virtual SDL_Rect* get_box();
		void handleInput();
		void can_buy();
		void cant_buy();
		bool buy();
		virtual void move_back();

		uint64_t get_depth();
		int calc_dept();
		void add_card(ECard pCard);
		void select_card(ECard pCard);

		ECard get_current_card();
		uint64_t get_limit();

		bool has_card();

		unsigned short get_grade();
		void decrease_grade();
		void increase_grade();

                bool is_indoor();
                void enter_building();
                void exit_building();

                void put_bomb();

};

class Gang: public Character, public Collider
{
	private:
		Gang* next_person;
		SDL_Rect* object_point;
                Timer update_timer;
<<<<<<< HEAD
=======

                void put_bomb();
>>>>>>> big_reafactor

	public:

		virtual void init();
		virtual void clean_up();
		virtual bool move(Uint32 deltaTicks);
		virtual void show(SDL_Surface*);
		virtual void set_clip();
		virtual void add_person();

		virtual bool check_collide(Collider*);
		virtual SDL_Rect* get_box();
		virtual void set_object(SDL_Rect *object);
		virtual void move_back();
                void update();
		bool follow();
                    
		//void handleInput();
		//void move_back();

};
#endif

