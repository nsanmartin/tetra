SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

#CFLAGS = -std=c++2b -Wextra -Werror -Wall  -pedantic -I./include 
CFLAGS = -std=c++2b 
#CC = clang++
CC = g++

BUILD = build

SRCS=$(wildcard src/*.cpp)
#SRCS=src/SdlMedia.cpp src/Game.cpp src/util.cpp

foo:build
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.cpp $(SDL_LDFLAGS)

debug:build
	$(CC) -g $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.c $(SDL_LDFLAGS)


build:
	if [ ! -d build ]; then mkdir build; fi


tags:
	ctags -R -e .


clean:
	rm build/*
