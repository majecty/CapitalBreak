
#include "common.h"
#include "Scene.h"
#include <stdio.h>
extern "C" {
#include "lua/lauxlib.h"

}
#define LuaGlue extern "C" int

static char* g_strEventHandler = "lua_event_handler";

LuaGlue lua_p_msg_1(lua_State *L) 
{
    fprintf(stderr,"At %s : \n",AT);
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = MESSAGE_BOX_1_EVENT;

    std::string* msg = new std::string(lua_tolstring(L,1,NULL));
    event.user.data1 = (void*)msg;

    SDL_PushEvent(&event);
    //print_message_1(msg);
    return 0;
}
LuaGlue lua_p_msg_2(lua_State *L) 
{
    fprintf(stderr,"At %s : \n",AT);
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = MESSAGE_BOX_2_EVENT;
    std::string* msg = new std::string(lua_tolstring(L,1,NULL));

    event.user.data1 = (void*)msg;
    SDL_PushEvent(&event);
    //print_message_2(msg);
    return 0;
}

static luaL_Reg ConsoleGlue[] = 
{
    {"pirnt_message_1", lua_p_msg_1},
    {"pirnt_message_2", lua_p_msg_2},
    {NULL, NULL}
};

void init_glue()
{
//    luaL_register(L, "mylib", ConsoleGlue);

//    for(int i=0; ConsoleGlue[i].name; i++) {
//        lua_register(L,
//                ConsoleGlue[i].name, ConsoleGlue[i].func);
//    }
}

void fire_lua_event(int event_id)
{
    if( g_strEventHandler != "")
    {
        char buf[254];
        sprintf(buf, "%s(%d)", g_strEventHandler, event_id);
        luaL_dostring(L,buf);
    }

}

