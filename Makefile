SDL_CFLAGS:=`sdl2-config --cflags`
SDL_LDFLAGS:= `sdl2-config --libs`
CXXFLAGS = -g -std=c++23 -Werror -Wextra -Wall -pedantic -I./include `sdl2-config --cflags --libs`
FANALYZER_FLAGS:= -Wanalyzer-double-fclose -Wanalyzer-double-free \
				  -Wanalyzer-exposure-through-output-file -Wanalyzer-file-leak \
				  -Wanalyzer-free-of-non-heap -Wanalyzer-malloc-leak \
				  -Wanalyzer-mismatching-deallocation -Wanalyzer-null-argument \
				  -Wanalyzer-null-dereference -Wanalyzer-possible-null-argument \
				  -Wanalyzer-possible-null-dereference \
				  -Wanalyzer-shift-count-negative -Wanalyzer-shift-count-overflow \
				  -Wanalyzer-stale-setjmp-buffer \
				  -Wanalyzer-unsafe-call-within-signal-handler \
				  -Wanalyzer-use-after-free \
				  -Wanalyzer-use-of-uninitialized-value -Wanalyzer-write-to-const \
				  -Wanalyzer-write-to-string-literal

# -Wanalyzer-use-of-pointer-in-stale-stack-frame 

BUILD_DIR=./build
OBJ_DIR=./obj
SRC_DIR=./src

HEADERS=$(wildcard include/*.h)
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:src/%.cpp=obj/%.o)

tetra: main.cpp $(OBJS) 
	$(CXX) -o $(BUILD_DIR)/$@ $^ $(FANALYZER_FLAGS) $(CXXFLAGS) $(SDL_LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(FANALYZER_FLAGS)  



TAGS: $(HEADERS) $(SRCS)
	universal-ctags -R -e .

clean:
	find $(BUILD_DIR) -type f -delete
	find $(OBJ_DIR) -type f -delete
