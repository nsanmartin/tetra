#ifndef __H_TETRA_MINO_H_
#define __H_TETRA_MINO_H_

#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

#include "Point.h"

namespace tetra {

using std::for_each;
using std::vector;
using std::function;

//todo: do we need move ctors?
class Mino {
	public:
	virtual Point pos() const = 0;
	virtual const Point* beg() const = 0;
	virtual const Point* end() const = 0;
	virtual void stepDown() = 0;
    virtual Point& getPos() = 0; //todo change this, receive lamda
    virtual void for_each_block(function<void(Point&)> f) = 0;
    virtual Point& min(function<bool(const Point&,const Point&)> comp) = 0;
    virtual Point& max(function<bool(const Point&,const Point&)> comp) = 0;
    virtual bool all(function<bool(const Point&)> prop) = 0;


};


class Tetramino : public Mino {
	Point pos_;
        vector<Point> data_;

	public:
	Tetramino(Point pos, Point* beg, Point* end) :
                pos_{pos}, data_{beg, end}
        {}
	void stepDown() override { 
        ++pos_.y;
    }

	Point pos() const override { return pos_; }
	const Point* beg() const override { return &*data_.begin(); }
	const Point* end() const override { return &*data_.end(); }

        Point& getPos() override { return pos_; }
        static Tetramino* L(Point pos);


        void for_each_block(function<void(Point&)> f) override {
                for_each(data_.begin(), data_.end(), f);
        }

        Point& min(function<bool(const Point&,const Point&)> comp) {
            return *min_element(data_.begin(), data_.end(), comp);
        }

        Point& max(function<bool(const Point&,const Point&)> comp) {
            return *max_element(data_.begin(), data_.end(), comp);
        }

        bool all(function<bool(const Point&)> prop) {
            return all_of(data_.begin(), data_.end(), prop);
        }
};

} // namespace tetra

#endif 

