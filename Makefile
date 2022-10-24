SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

CFLAGS = -std=c++2b -Werror -Wextra -Wall  -pedantic -I./include 
#CC = clang++
CC = g++

BUILD = build

MALLOCTIMES := 9

SRCS=$(wildcard src/*.cpp)
#SRCS=src/SdlMedia.cpp src/Game.cpp src/util.cpp

tetra:build
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.cpp $(SRCS) $(SDL_LDFLAGS)

tmalloc0:build
	$(CC) -DMALLOC_TIMES$(MALLOCTIMES) $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.c $(SRCS) $(SDL_LDFLAGS)

debug:build
	$(CC) -g $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.c $(SRCS) $(SDL_LDFLAGS)


build:
	if [ ! -d build ]; then mkdir build; fi


tags:
	ctags -R -e .


clean:
	rm build/*
