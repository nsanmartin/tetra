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

using WinPtr = unique_ptr<SDL_Window, function<void(SDL_Window *)>>;
//using WinPtr = unique_ptr<SDL_Window,decltype(SDL_DestroyWindow)>;
//using WinPtr = unique_ptr<SDL_Window, void(SDL_Window*)>;
using RendPtr = unique_ptr<SDL_Renderer, decltype(SDL_DestroyRenderer)>;
using WinRendPair = pair<WinPtr,RendPtr>;
using EitherWinRend = variant<WinRendPair, int>;

int main () {
    int error = SDL_Init (SDL_INIT_VIDEO);
    if (error) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        return error;
    }

    int w = 640;
    int h = 480;

    //auto window = WinPtr(
    //    SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0),
    //    SDL_DestroyWindow
    //);

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
    //RendPtr renderer;
}
