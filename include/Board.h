#ifndef __H_BOARD_H_
#define __H_BOARD_H_

#include <cstdint>

#include <optional>
#include <vector>
#include <functional>

#include "Drawable.h"
#include "Grided.h"

namespace tetra {

using std::reference_wrapper;
using std::optional;
using std::vector;
using std::move;

class Board : public Drawable, public Grided {
    public:
    vector<uint32_t> blocks;

    //public:
    Board(int w, int h) : Drawable{0,0}, Grided{w,h},  blocks(w*h, 0xFFf0FFff) {}
    Board(Board&& o) :
        Drawable{o.x,o.y}, Grided{o.w, o.h}, blocks{move(o.blocks)} {}

    optional<reference_wrapper<uint32_t>> at(int x, int y);

    private:
    optional<reference_wrapper<uint32_t>> at(int i);
};

}
#endif
