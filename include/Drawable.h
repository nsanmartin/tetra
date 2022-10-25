#ifndef __H_DRAWABLE_H_
#define __H_DRAWABLE_H_

#include "Point.h"

struct Drawable {
    // position within its container
    Point origin, end;
    Drawable(Point origin, Point end) : origin{origin}, end{end} {}
};
#endif


