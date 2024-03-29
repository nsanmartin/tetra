#ifndef __H_SDL_MEDIA_H_
#define __H_SDL_MEDIA_H_

//#include <deque>
#include <expected>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <SDL.h>

#include "Grided.h"

namespace tetra {
//using std::deque;
using std::pair;
using std::make_pair;
using std::unique_ptr;
using std::function;


class SdlMedia : public Grided {

    struct WinDestroyer { void operator()(SDL_Window *w) const { SDL_DestroyWindow(w); } };
    struct RendDestroyer { void operator()(SDL_Renderer *r) const { SDL_DestroyRenderer(r); } };

    using WinPtr = unique_ptr<SDL_Window, WinDestroyer>;
    using RendPtr = unique_ptr<SDL_Renderer, RendDestroyer>;
    using WinRendPair = pair<WinPtr,RendPtr>;
    WinPtr window;
    RendPtr renderer;

    //deque keyQueue;

    SdlMedia(SdlMedia const& m) = delete;
    SdlMedia& operator=(const SdlMedia& o) = delete;

    SdlMedia(int width, int height, WinPtr win, RendPtr rend)
        : Grided{width, height}, window{std::move(win)}, renderer{std::move(rend)} { }

    static std::expected<WinRendPair,int> initialize(int w, int h);

    public:
    SdlMedia(SdlMedia&& m) noexcept :
        Grided{m.w, m.h}, window{std::move(m.window)}, renderer{std::move(m.renderer)} { }

    //todo: use expected instead of variant
    static std::expected<SdlMedia,int> withDimensions(int w, int h);

    SdlMedia& operator=(SdlMedia&& o) noexcept = delete;

    pair<int,int> getDimensions() { return make_pair(w,h); }

    SDL_Renderer* getRenderer() { return renderer.get(); }

};
}

#endif
