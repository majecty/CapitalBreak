
#include "common.h"
#include "Scene.h"
#include "object.h"

Top::Top(int x, int y, int w, int h)
{
	offset.x = x;
	offset.y = y;
	offset.w = w;
	offset.h = h;


	credit_str = "";
	total_str = "";
}

void Top::set_credit_score(int credit)
{

        //fprintf(stderr,"credit is %d At : %s\n", credit,AT);
	credit_str = gGradeName[credit];


}

void Top::set_total_dept(int total)
{
	total_str = "";
	std::ostringstream result;
	result << total;
	total_str += result.str();
}
void Top::show(SDL_Surface* background)
{
	SDL_Surface depth;
	SDL_Surface grade;
//	set_total_dept(hero->get_depth());
	depth = *TTF_RenderText_Solid( font, total_str.c_str(), textColor);
	grade = *TTF_RenderText_Solid(font, credit_str.c_str(), textColor);
	
	apply_surface(offset.x,offset.y,background,screen,&offset);
	apply_surface(400,5,&depth,screen);
	apply_surface(240,5,&grade,screen);
}
void WalletBar::init(int x, int y, int w, int h)
{

        ImageManager* im = ImageManager::get_instance();
        cards_image = im->get_image( ImageList::eCard);
        faces_image = im->get_image( ImageList::eHeroFace);

//	cards_image = load_image("game_1s_card.png");
//	faces_image = load_image("game_face.png");
	offset.x = x; offset.y = y; offset.w = w; offset.h = h;

	for(int i=0;i<6;i++) {
		cards[i].x = 10;
		cards[i].y = 175 + i* 50;
		cards[i].w = 120;
		cards[i].h = 50;
	}
	for(int i=0;i<6;i++) {
		cards_clip[i].x = 0;
		cards_clip[i].y = 50*i;
		cards_clip[i].w = 120;
		cards_clip[i].h = 50;
	}
	for(int i=0;i<6;i++)
	{
		cards_limits_box[i].x = 13 + cards[i].x;
		cards_limits_box[i].y = 13 + cards[i].y;
		cards_limits_box[i].w = 60;
		cards_limits_box[i].h = 10;
	}
	for(int i=0;i<6;i++)
	{
		cards_limits_clip[i].x = 20 + cards_clip[i].x;
		cards_limits_clip[i].y = 13 + cards_clip[i].y;
		cards_limits_clip[i].w = 60;
		cards_limits_clip[i].h = 10;
	}
	for( int i=0;i<6;i++)
	{
		face_clip[i].x = (i%2) * 116;
		face_clip[i].y = (i/2) * 116;
		face_clip[i].w = 116;
		face_clip[i].h = 116;
	}

	for(int i=0;i<6;i++) {
		apply_surface(cards[i].x,cards[i].y, cards_image, screen, &cards_clip[i]);
	}
}

void WalletBar::clean_up()
{

//	SDL_FreeSurface(cards_image);
//	SDL_FreeSurface(faces_image);
}

void WalletBar::show( )
{
	apply_surface(12,42,faces_image, screen, &face_clip[frame%6]);
	frame++;
	;
}
void WalletBar::show_gage(ECard i, float ratio)
{
    int building_id = i - 1; // building id  is start from 1
	SDL_Rect box;
	box.x = cards_limits_box[building_id].x;
	box.y = cards_limits_box[building_id].y;
	box.w = (int)(cards_limits_box[building_id].w * ratio);
	box.h = cards_limits_box[building_id].h;
	SDL_FillRect(screen,&box, SDL_MapRGB(screen->format, 0,0,0));

}

void WalletBar::print_limit(ECard i, uint64_t money)
{
	std::ostringstream result;
	result << money;
	//total_str += result.str();
	SDL_Surface* message_surface = NULL; 

	apply_surface(cards_limits_box[i].x, cards_limits_box[i].y,cards_image,screen,&cards_limits_clip[i]);

	message_surface = TTF_RenderText_Solid( font, result.str().c_str(), textColor);
	apply_surface(cards_limits_box[i].x, cards_limits_box[i].y+1,message_surface,screen);

	
}

MessageBox::MessageBox(SDL_Surface* bg)
{
    rect.x = MESSAGE_BOX_X;
    rect.y = MESSAGE_BOX_Y;
    rect.w = MESSAGE_BOX_W;
    rect.h = MESSAGE_BOX_H;
    background = bg;
}

void MessageBox::show()
{
    if( message_timer.get_ticks()> message_timer.period  )
    {
        print_message_1("",1000);
        message_timer.stop();

    }
    if( message_timer2.get_ticks() > message_timer2.period  )
    {
        print_message_2("",1000);
        message_timer2.stop();
    }
}

void MessageBox::show_message_box()
{


    SDL_Surface* message_surface = NULL; 
    apply_surface(rect.x, rect.y,background,screen,&rect);

    message_surface = TTF_RenderText_Solid( font, message.c_str(), textColor);
    apply_surface(rect.x, rect.y+1,message_surface,screen);

    message_surface = TTF_RenderText_Solid( font, message.c_str(), whiteColor);
    apply_surface(rect.x, rect.y,message_surface,screen);

    message_surface = TTF_RenderText_Solid( font, message2.c_str(), textColor);
    apply_surface(rect.x, rect.y+50+1,message_surface,screen);

    message_surface = TTF_RenderText_Solid( font, message2.c_str(), whiteColor);
    apply_surface(rect.x, rect.y+50,message_surface,screen);


}

void MessageBox::print_message_1(std::string msg, int duration)
{
    message = msg;//"please press space bar to purchase";
    show_message_box();
    message_timer.start(duration);
}

void MessageBox::print_message_2(std::string msg, int duration) 
{

    message2 = msg;//"You Purchase Clock";
    show_message_box();
    message_timer2.start(duration);
}

