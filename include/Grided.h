#ifndef __H_GRIDED_H_
#define __H_GRIDED_H_

#include "Point.h"

struct Grided {
    int w,h;
    Grided(int w, int h) : w{w}, h{h} {}

    Point mapCoordinates(Grided& contained, int x, int y) { 
        return Point{w/contained.w * x, h/contained.h * y};
    }

};

#endif


