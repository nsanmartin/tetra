#ifndef __H_MINO_H_
#define __H_MINO_H_

class Mino : pubic DrawabeGrid {
    public:
    Mino(Point origin, Point end, int x, int y) : DrawableGrid{w, h, origin, end} {}
};

#endif


