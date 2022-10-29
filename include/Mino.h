#ifndef __H_TETRA_MINO_H_
#define __H_TETRA_MINO_H_

#include "Point.h"

namespace tetra {

//todo: do we need move ctors?
class Mino {
	public:
	virtual Point pos() const = 0;
	virtual Point* beg() = 0;
	virtual Point* end() = 0;
	virtual void stepDown() = 0;
};


class Tetramino : public Mino {
	Point pos_;

	public:
	Tetramino(Point pos) : pos_{pos} {}
	void stepDown() override { ++pos_.y; }
	Point pos() const override { return pos_; }
};

class TetraminoL : public Tetramino {

	public:
	Point* beg() override;
	Point* end() override;
	TetraminoL(Point pos) : Tetramino{pos} {}
};
} // namespace tetra

#endif 

