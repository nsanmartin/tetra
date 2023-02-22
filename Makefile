SDL_CFLAGS=`sdl2-config --cflags`
SDL_LDFLAGS= `sdl2-config --libs`
CXXFLAGS = -g -std=c++2b -Werror -Wextra -Wall -pedantic -I./include `sdl2-config --cflags --libs`

BUILD_DIR=./build
OBJ_DIR=./obj
SRC_DIR=./src

HEADERS=$(wildcard include/*.h)
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:src/%.cpp=obj/%.o)

tetra: main.cpp $(OBJS) 
	$(CXX) -o $(BUILD_DIR)/$@ $^ $(CXXFLAGS) $(SDL_LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) 
	$(CXX) -c -o $@ $< $(CXXFLAGS) 



TAGS: $(HEADERS) $(SRCS)
	universal-ctags -R -e .

clean:
	find $(BUILD_DIR) -type f -delete
	find $(OBJ_DIR) -type f -delete
