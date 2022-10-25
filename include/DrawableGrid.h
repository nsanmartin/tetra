#ifndef __H_DRAWAABLE_GRID_H_
#define __H_DRAWAABLE_GRID_H_

#include "SDL.h"

#include "Drawable.h"
#include "Grided.h"

struct DrawableGrid : public Drawable, public Grided {
    const int block_width;
    const int block_height;

    DrawableGrid(int w, int h, Point origin, Point end) :
        Drawable{origin, end},
        Grided{w,h},
        block_width{(end.x-origin.x)/w},
        block_height{(end.y-origin.y)/h}
    {}

    SDL_Rect toSdlRect(int x, int y) { 

        return SDL_Rect{
            origin.x + x * block_width, 
            origin.y + y * block_height,
            block_width,
            block_height
        };
    }

};
#endif

