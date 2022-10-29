SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

CFLAGS = -std=c++2b -Werror -Wextra -Wall  -pedantic -I./include 
#CC = clang++
CC = g++

BUILD = build
ODIR=./obj
HEADERS=$(wildcard include/*.h)
SRCS=$(wildcard src/*.cpp)
OBJ=$(SRCS:src/%.cpp=obj/%.o)

#SRCS=src/SdlMedia.cpp src/Game.cpp src/util.cpp

tetra: $(OBJ)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.cpp $(SRCS) $(SDL_LDFLAGS)

$(ODIR)/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c -o $@ $< $(SDL_LDFLAGS)

debug:build
	$(CC) -g $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.cpp $(SRCS) $(SDL_LDFLAGS)


build:
	if [ ! -d build ]; then mkdir build; fi


tags:
	ctags -R -e .


clean:
	rm $(ODIR)/*.o build/*
