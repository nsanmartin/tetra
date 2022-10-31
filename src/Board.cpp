#include "Board.h"

namespace tetra {
using std::nullopt;
//using std::reference_wrapper;
//using std::optional;
//using tetra::Board;

optional<reference_wrapper<uint32_t>> Board::at(int i) {
    return  0 <= i && static_cast<size_t>(i) < blocks.size() 
        ? optional<reference_wrapper<uint32_t>>{ blocks[i] }
        : nullopt;
}

optional<reference_wrapper<uint32_t>> Board::at(int x, int y) {
    return 0 <= x && x < w && 0 <= y && y < h
        ?  at(y*w + x)
        : nullopt;
}

}
