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

vector<int> Board::getLines() {
    vector<int> res{};
    for (int i = 0; i < h; ++i) {
        bool line = true;
        //todo: use lambda
        for (int j = 0; j < w; ++j) {
            if (auto color = at(j, i)) {
                if (color == 0) {
                   line = false; 
                   break;
                }
            }
        }
        if (line) { res.push_back(i); }
    }
    return res;
}

void Board::clearLines(const vector<int>& lines) {
    for (auto l: lines) {
        for (int col = 0; col < w; ++col) {
            if (auto color = at(col, l)) {
                color->get() = 0x0;
            }
        }
    }
}

void Board::dropLines(int nlines, int lowest) {
    for (; lowest > 0; --lowest) {
        for (int col = 0; col < w; ++col) {
            if (auto color = at(col, lowest - nlines)) {
                if (auto cleared = at(col, lowest)) {
                    cleared ->get() = color->get();
                }
            }
        }
    }
}

} // namespace tetra
