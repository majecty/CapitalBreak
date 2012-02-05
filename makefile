.SUFFIXES : .cpp .o

OBJECTS = main.o  Scene.o GameScene.o character.o  collider.o building.o map.o gang.o CCard.o CPlayer.o  GlobalFunctions.o timer.o GameScene_GUI.o lua_glue.o
SRCS = main.cpp debug.cpp Scene.cpp GameScene.cpp character.cpp collider.cpp building.cpp map.cpp gang.cpp CCard.cpp CPlayer.cpp GlobalFunctions.cpp Timer.cpp GameScene_GUI.cpp lua_glue.cpp

CC = gcc
CXX = g++
CXXFLAGS = -g -c -Wall
TARGET = capitalBreak.exe
LIBS =  -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -llua52
LIBDIRS = -Llua/
INC = -Ilua/

all : $(TARGET)
	
$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LIBDIRS) $(LIBS)

.cpp.o :
	$(CXX) $(INC) $(CXXFLAGS) $< -o $@ 

clean:
	rm $(OBJECTS) $(TARGET)

#capitalBreak.exe: main.o  debug.o Scene.o GameScene.o character.o  collider.o building.o map.o gang.o CCard.o CPlayer.o  GlobalFunctions.o timer.o
#	g++ main.o  debug.o Scene.o GameScene.o character.o  building.o collider.o map.o gang.o CCard.o CPlayer.o  GlobalFunctions.o  timer.o -o capitalBreak.exe -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf 
#
#lua: main.o  debug.o Scene.o GameScene.o character.o  collider.o building.o map.o gang.o CCard.o CPlayer.o  GlobalFunctions.o timer.o
#	g++ main.o  debug.o Scene.o GameScene.o character.o  building.o collider.o map.o gang.o CCard.o CPlayer.o  GlobalFunctions.o  timer.o -o capitalBreak.exe -Llua/ -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf  -llua52
#
#clean:
#	rm *.o
#
#CCard.o: CCard.cpp
#	g++ CCard.cpp -c -Wall -g
#CPlyaer.o: CPlyaer.cpp
#	g++ CPlayer.cpp -c -Wall -g
#
#GlobalFunctions.o: GlobalFunctions.cpp
#	g++ GlobalFunctions.cpp -c -Wall -g
#
#stdafx.o: stdafx.cpp
#	g++ stdafx.cpp -c -Wall -g
#
#main.o: main.cpp
#	g++ main.cpp -c -Wall -g
#debug.o: debug.cpp debug.h
#	g++ debug.cpp -c -Wall -g
#
#test: Scene.o test.o
#	g++ test.o Scene.o -o test.exe -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
#
#test.o:  test.cpp
#	g++ test.cpp -c -Wall -g
#Scene.o: Scene.cpp
#	g++ Scene.cpp -c -Wall -g
#GameScene.o: GameScene.cpp
#	g++ GameScene.cpp -c -Wall -g
#
#character.o: character.cpp
#	g++ character.cpp -c -Wall -g
#timer.o: Timer.cpp
#	g++ Timer.cpp -c -Wall -g -o timer.o
#building.o: building.cpp
#	g++ building.cpp -c -Wall -g
#collider.o: collider.cpp
#	g++ collider.cpp -c -Wall -g
#map.o: map.cpp
#	g++ map.cpp -c -Wall -g
#gang.o: gang.cpp
#	g++ gang.cpp -c -Wall -g
#
