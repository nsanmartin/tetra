#ifndef __H_TETRA_MINO_H_
#define __H_TETRA_MINO_H_

#include <cstdio>
#include <vector>

#include "Point.h"

namespace tetra {

using std::vector;

//todo: do we need move ctors?
class Mino {
	public:
	virtual Point pos() const = 0;
	virtual const Point* beg() const = 0;
	virtual const Point* end() const = 0;
	virtual void stepDown() = 0;
};


class Tetramino : public Mino {
	Point pos_;
        vector<Point> data_;

	public:
	Tetramino(Point pos, Point* beg, Point* end) :
                pos_{pos}, data_{beg, end}
        {}
	void stepDown() override { ++pos_.y; }
	Point pos() const override { return pos_; }
	const Point* beg() const override { return &*data_.begin(); }
	const Point* end() const override { return &*data_.end(); }

        static Tetramino* L(Point pos);
};

} // namespace tetra

#endif 

