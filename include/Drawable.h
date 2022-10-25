#ifndef __H_DRAWABLE_H_
#define __H_DRAWABLE_H_

struct Drawable {
    // position within its container
    int x,y;
    Drawable(int x, int y) : x{x}, y{y} {}
};
#endif


