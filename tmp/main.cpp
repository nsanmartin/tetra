#include <memory>
#include <iostream>
#include <utility>
#include <variant>
#include <SDL.h>
#include <functional>

//using std::deque;
using std::variant;
using std::pair;
using std::make_pair;
using std::unique_ptr;
using std::move;
using std::make_unique;
using std::function;
using std::same_as;

using WinPtr = unique_ptr<SDL_Window, function<void(SDL_Window *)>>;
using RendPtr = unique_ptr<SDL_Renderer, decltype(SDL_DestroyRenderer)>;
using WinRendPair = pair<WinPtr,RendPtr>;
using EitherWinRend = variant<WinRendPair, int>;


template <typename T>
concept GameBehaviour = requires (T v) {
    {v.keepRunning()} -> same_as<bool>;
    {v.processInput()} -> same_as<void>;
    {v.update()()} -> same_as<void>;
    {v.render()} -> same_as<void>;
};

//template <typename T>
//concept GameBehaviour = requires (T v) {
//    {v.processInput()} -> same_as<void>;
//};

int main () {
    int error = SDL_Init (SDL_INIT_VIDEO);
    if (error) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        return error;
    }

    int w = 640;
    int h = 480;


    WinPtr window (
        SDL_CreateWindow(
           "tetra",
           SDL_WINDOWPOS_CENTERED,
           SDL_WINDOWPOS_CENTERED,
           w,
           h,
           SDL_WINDOW_SHOWN
       ),
        SDL_DestroyWindow
    );
}
