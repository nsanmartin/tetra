#ifndef __H_BOARD_H_
#define __H_BOARD_H_

#include <cstdint>

#include <optional>
#include <vector>
#include <functional>

#include "DrawableGrid.h"

namespace tetra {

using std::reference_wrapper;
using std::optional;
using std::vector;
using std::move;

class Board : public DrawableGrid {
    public:
    vector<uint32_t> blocks;

    //public:
    Board(Point origin, Point end, int w, int h, uint32_t blocks_color) :
        DrawableGrid{w, h, origin, end}, blocks(w*h, blocks_color) {}
    Board(Board&& o) :
        DrawableGrid{o.w, o.h, o.origin, o.end}, blocks{move(o.blocks)} {}

    optional<reference_wrapper<uint32_t>> at(int x, int y);

    private:
    optional<reference_wrapper<uint32_t>> at(int i);
};

}
#endif
