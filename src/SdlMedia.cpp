#include <SdlMedia.h>
#include "util.h"

namespace tetra {


std::expected<SdlMedia::WinRendPair,int> SdlMedia::initialize(int w, int h) {
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    int error = 0;
    error = SDL_Init (SDL_INIT_VIDEO);
    if (error) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        return std::unexpected(error);
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
        return std::unexpected(-1);
    }
    
    //todo: use fullscreen?
    //error = SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    //if (error) {
    //    SDL_DestroyWindow(window);
    //    return std::unexpected(error);
    //}

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return std::unexpected(-1);
    }

    return make_pair(SdlMedia::WinPtr(window), SdlMedia::RendPtr(renderer));
}


std::expected<SdlMedia,int> SdlMedia::withDimensions(int w, int h) {
    //return initialize(w, h).transform([&w, &h](WinRendPair& p) {
    //    return SdlMedia( w, h, std::move(p.first), std::move(p.second));
    //});
    auto p = SdlMedia::initialize(w, h);
    if (p.has_value()) {
        return SdlMedia(w, h, std::move(p->first), std::move(p->second));
    }
    return std::unexpected(p.error());
}

}
