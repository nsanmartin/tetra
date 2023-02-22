#ifndef __H_BOARD_H_
#define __H_BOARD_H_

#include <cstdint>

#include <memory>
#include <optional>
#include <vector>
#include <functional>

#include "DrawableGrid.h"
#include "Mino.h"

namespace tetra {

using std::reference_wrapper;
using std::optional;
using std::vector;
using std::unique_ptr;

class Board : public DrawableGrid {
    public:
    //todo: use vector of points instead
    vector<uint32_t> blocks;
    unique_ptr<Mino> mino;

    //public:
    Board(Point origin, Point end, int w, int h, uint32_t blocks_color) :
        DrawableGrid{w, h, origin, end},
	blocks(w*h, blocks_color),
	mino(unique_ptr<Mino>(Tetramino::Rand(Point{w/2,1})))
 	{}
    Board(Board&& o) :
        DrawableGrid{o.w, o.h, o.origin, o.end},
        blocks{std::move(o.blocks)},
	mino{std::move(o.mino)}
    {}

    optional<reference_wrapper<uint32_t>> at(int x, int y);
    //optional<bool> is_empty_at(Point p);
    vector<int> getLines() ;
    void clearLines(const vector<int>& lines);
    void dropLines(int nlines, int lowest);

    private:
    optional<reference_wrapper<uint32_t>> at(int i);
};

}
#endif
