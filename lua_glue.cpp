
#include "common.h"
#include "Scene.h"
#include <stdio.h>
extern "C" {
#include "lua/lauxlib.h"

}
#define LuaGlue  static int

extern"C" {
    LuaGlue lua_p_msg_1(lua_State*);
    LuaGlue lua_p_msg_2(lua_State*);
}

static char* g_strEventHandler = "lua_event_handler";
static char* g_messageEventHalder = "message_handler";

LuaGlue lua_p_msg_1(lua_State *L) 
{
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = MESSAGE_BOX_1_EVENT;

    std::string* msg = new std::string(lua_tolstring(L,1,NULL));
    int duration = lua_tointeger(L,2);

    event.user.data1 = (void*)msg;
    event.user.data2 = (void*)duration;

    SDL_PushEvent(&event);
    //print_message_1(msg);
    return 0;
}
LuaGlue lua_p_msg_2(lua_State *L) 
{
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = MESSAGE_BOX_2_EVENT;
    std::string* msg = new std::string(lua_tolstring(L,1,NULL));
    int duration = lua_tointeger(L,2);

    event.user.data1 = (void*)msg;
    event.user.data2 = (void*)duration;
    SDL_PushEvent(&event);
    //print_message_2(msg);
    return 0;
}

static luaL_Reg ConsoleGlue[] = 
{
    {"print_message_1", lua_p_msg_1},
    {"print_message_2", lua_p_msg_2},
    {NULL, NULL}
};

void init_glue()
{
//    luaL_register(L, "mylib", ConsoleGlue);

//    lua_register(L, "print_message_1", lua_p_msg_1);
//    lua_register(L, "print_message_2", lua_p_msg_2);
    for(int i=0; ConsoleGlue[i].name; i++) {
        lua_register(L,
                ConsoleGlue[i].name, ConsoleGlue[i].func);
    }
}

void fire_lua_event(int event_id)
{
    if( g_strEventHandler != "")
    {
        char buf[254];
        //sprintf(buf, "%s(%d)", g_strEventHandler, event_id);
        sprintf(buf, "%s(\"%s\")", g_strEventHandler, Script_Name[event_id]);
        luaL_dostring(L,buf);
        //fprintf(stderr, "return value is %d",luaL_dostring(L,buf));
    }

}

void fire_message_event(int message_id)
{
    if( g_messageEventHalder != "")
    {
        char buf[254];
        sprintf(buf, "%s(\"%s\")", g_messageEventHalder
                , Script_Name[message_id]);
        luaL_dostring(L,buf);
    }
}

