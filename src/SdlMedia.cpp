#include <SdlMedia.h>
#include "util.h"

namespace tetra {

using std::variant;
using std::visit;
using std::move;


SdlMedia::EitherWinRend SdlMedia::init(int w, int h) {
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    int error = 0;
    error = SDL_Init (SDL_INIT_VIDEO);
    if (error) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        return SdlMedia::EitherWinRend(error);
    }

    atexit (SDL_Quit);

    window = SDL_CreateWindow(
        "tetra",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w,
        h,
        SDL_WINDOW_SHOWN
    );
    
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        return SdlMedia::EitherWinRend(-1);
    }
    
    error = SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (error) {
        SDL_DestroyWindow(window);
        return SdlMedia::EitherWinRend(error);
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return SdlMedia::EitherWinRend(-1);
    }

    return SdlMedia::EitherWinRend(make_pair(
        SdlMedia::WinPtr(window), SdlMedia::RendPtr(renderer)
    ));
}

SdlMedia::Either SdlMedia::withDimensions(int w, int h) {
    SdlMedia::EitherWinRend either = init(w, h);
    return variant(visit(overloaded{
        [&w, &h](WinRendPair& p) {
            return SdlMedia::Either(SdlMedia( w, h, move(p.first), move(p.second)));
        },
        [](int error) { return SdlMedia::Either{error}; },
        }, either
    ));
}

}
