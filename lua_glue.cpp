
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
    int *duration = new int(lua_tointeger(L,2));

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
    int *duration = new int(lua_tointeger(L,2));

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
void lua_init()
{
    L = luaL_newstate();
    luaL_openlibs(L);
    fprintf(stderr, "in lua_init function start %s\n",AT );

    if ( luaL_loadfile(L, "Configuration.lua") || lua_pcall(L,0,0,0))
    //if ( luaL_loadfile(L, "luac.out") || lua_pcall(L,0,0,0))
        maj_lua_error(L, "cannot run config. file: %s\n", lua_tostring(L,-1));
    fprintf(stderr, "in after lua_loadfile");

    lua_getglobal(L, "default_frame_rate");
    lua_getglobal(L, "default_rate");
    lua_getglobal(L, "rate_rate");
    lua_getglobal(L, "default_limit");
    lua_getglobal(L, "limit_rate");
    lua_getglobal(L, "start_grade");

    lua_getglobal(L, "is_full_screen");
    lua_getglobal(L, "char_velocity");
    lua_getglobal(L, "shop_count_for_upgrade");


    DEFAULT_FRAME_RATE = lua_tointeger(L,1);
    DEFAULT_RATE = lua_tonumber(L,2);
    RATE_RATE = lua_tonumber(L,3);
    DEFAULT_LIMIT = lua_tointeger(L,4);
    LIMIT_RATE = lua_tointeger(L,5);
    START_GRADE = lua_tointeger(L,6);
    IS_FULL_SCREEN = lua_toboolean(L,7);
    CHAR_VELOCITY = lua_tointeger(L,8);
    SHOP_COUNT_FOR_UPGRADE = lua_tointeger(L,9);

    fprintf(stderr, "default frame rate is %d\n", LIMIT_RATE);
    fprintf(stderr, "LIMIT_RATE is %d\n", LIMIT_RATE);


    init_glue();
}
