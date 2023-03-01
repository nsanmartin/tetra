#include <SdlMedia.h>
#include "util.h"

namespace tetra {

using std::unexpected;


SdlMedia::EitherWinRend SdlMedia::init(int w, int h) {
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    int error = 0;
    error = SDL_Init (SDL_INIT_VIDEO);
    if (error) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        return unexpected(error);
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
        return unexpected(-1);
    }
    
    //todo: use fullscreen?
    //error = SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    //if (error) {
    //    SDL_DestroyWindow(window);
    //    return SdlMedia::EitherWinRend(error);
    //}

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return unexpected(-1);
    }

    return make_pair(
        SdlMedia::WinPtr(window), SdlMedia::RendPtr(renderer)
    );
}

SdlMedia::Either SdlMedia::withDimensions(int w, int h) {
    SdlMedia::EitherWinRend either = init(w, h);
    if (either) {
        return SdlMedia::Either(SdlMedia( w, h, std::move(either->first), std::move(either->second)));
    } else {
        return unexpected(either.error());
    }

}

}
