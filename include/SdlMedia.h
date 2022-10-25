#ifndef __H_SDL_MEDIA_H_
#define __H_SDL_MEDIA_H_

//#include <deque>
#include <memory>
#include <iostream>
#include <utility>
#include <variant>
#include <functional>
#include <SDL.h>

#include "Grided.h"

namespace tetra {
//using std::deque;
using std::variant;
using std::pair;
using std::make_pair;
using std::unique_ptr;
using std::move;
using std::function;


class SdlMedia : public Grided {

    struct WinDestroyer { void operator()(SDL_Window *w) const { SDL_DestroyWindow(w); } };
    struct RendDestroyer { void operator()(SDL_Renderer *r) const { SDL_DestroyRenderer(r); } };

    using WinPtr = unique_ptr<SDL_Window, WinDestroyer>;
    using RendPtr = unique_ptr<SDL_Renderer, RendDestroyer>;
    using WinRendPair = pair<WinPtr,RendPtr>;
    using EitherWinRend = variant<WinRendPair, int>;
    using Either = variant<SdlMedia,int>;
    WinPtr window;
    RendPtr renderer;

    //deque keyQueue;

    SdlMedia(SdlMedia const& m) = delete;
    SdlMedia& operator=(const SdlMedia& o) = delete;

    SdlMedia(int width, int height, WinPtr win, RendPtr rend)
        : Grided{width, height}, window{move(win)}, renderer{move(rend)} { }
    static EitherWinRend init(int w, int h);

    public:
    SdlMedia(SdlMedia&& m) noexcept :
        Grided{m.w, m.h}, window{move(m.window)}, renderer{move(m.renderer)} { }

    //todo: use expected instead of variant
    static variant<SdlMedia,int> withDimensions(int w, int h);

    SdlMedia& operator=(SdlMedia&& o) noexcept = delete;

    pair<int,int> getDimensions() { return make_pair(w,h); }

    SDL_Renderer* getRenderer() { return renderer.get(); }

    SDL_Rect toSdlRect(Grided& contained, int x, int y) { 
        const int block_width {w/contained.w};
        const int block_height {h/contained.h};

        return SDL_Rect{
            x * block_width, 
            y * block_height,
            block_width,
            block_height
        };
    }

};
}

#endif
