#ifndef __H_SDL_MEDIA_H_
#define __H_SDL_MEDIA_H_

//#include <deque>
#include <memory>
#include <iostream>
#include <utility>
#include <variant>
#include <functional>
#include <SDL.h>

namespace tetra {
//using std::deque;
using std::variant;
using std::pair;
using std::make_pair;
using std::unique_ptr;
using std::move;
using std::function;


class SdlMedia {
    struct WinDestroyer { void operator()(SDL_Window *w) const { SDL_DestroyWindow(w); } };
    struct RendDestroyer { void operator()(SDL_Renderer *r) const { SDL_DestroyRenderer(r); } };

    using WinPtr = unique_ptr<SDL_Window, WinDestroyer>;
    using RendPtr = unique_ptr<SDL_Renderer, RendDestroyer>;
    using WinRendPair = pair<WinPtr,RendPtr>;
    using EitherWinRend = variant<WinRendPair, int>;
    using Either = variant<SdlMedia,int>;
    int w, h;
    WinPtr window;
    RendPtr renderer;

    //deque keyQueue;

    SdlMedia(SdlMedia const& m) = delete;
    SdlMedia& operator=(const SdlMedia& o) = delete;

    SdlMedia(int width, int height, WinPtr win, RendPtr rend)
        : w{width} , h{height}, window{move(win)}, renderer{move(rend)} { }
    static EitherWinRend init(int w, int h);

    public:
    SdlMedia(SdlMedia&& m) noexcept :
        w{m.w}, h{m.h}, window{move(m.window)}, renderer{move(m.renderer)} { }

    //todo: use expected instead of variant
    static variant<SdlMedia,int> withDimensions(int w, int h);

    SdlMedia& operator=(SdlMedia&& o) noexcept = delete;

    pair<int,int> getDimensions() { return make_pair(w,h); }

    SDL_Renderer* getRenderer() { return renderer.get(); }
};
}

#endif
