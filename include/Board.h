#ifndef __H_BOARD_H_
#define __H_BOARD_H_

#include <cstdint>

#include <optional>
#include <vector>
#include <functional>

namespace tetra {

using std::reference_wrapper;
using std::optional;
using std::vector;
using std::move;

class Board {
    public:
    int w, h;
    vector<uint32_t> blocks;

    //public:
    Board(int w, int h) : w{w}, h{h}, blocks(w*h, 0x1f122120) {}
    Board(Board&& o) : w{o.w}, h{o.h}, blocks{move(o.blocks)} {}

    optional<reference_wrapper<uint32_t>> at(int x, int y);

    private:
    optional<reference_wrapper<uint32_t>> at(int i);
};

}
#endif
