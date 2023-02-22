#ifndef __H_TETRA_MINO_H_
#define __H_TETRA_MINO_H_

#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

#include "Point.h"

namespace tetra {

using std::for_each;
using std::vector;
using std::function;
using std::cout;

struct MinoSz {
    Point* ps;
    int sz;
};


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

    virtual void rotate90deg() = 0;
    virtual Mino* clone() = 0;
    virtual ~Mino() = default;
};


class Tetramino : public Mino {
	Point pos_;
    vector<Point> data_;
    static int _tmp;

	public:
	Tetramino(Point pos, Point* beg, Point* end) :
                pos_{pos}, data_{beg, end}
        {}

    Tetramino(Tetramino& o) : pos_{o.pos_}, data_{o.data_.begin(), o.data_.end()} {}

    Mino* clone() override { return new Tetramino(*this); }

	void stepDown() override { 
        ++pos_.y;
    }

	Point pos() const override { return pos_; }
	const Point* beg() const override { return &*data_.begin(); }
	const Point* end() const override { return &*data_.end(); }

        Point& getPos() override { return pos_; }
        static Tetramino* Rand(Point pos);


        void for_each_block(function<void(Point&)> f) override {
                for_each(data_.begin(), data_.end(), f);
        }

        Point& min(function<bool(const Point&,const Point&)> comp) override {
            return *min_element(data_.begin(), data_.end(), comp);
        }

        Point& max(function<bool(const Point&,const Point&)> comp) override {
            return *max_element(data_.begin(), data_.end(), comp);
        }

        bool all(function<bool(const Point&)> prop) override {
            return all_of(data_.begin(), data_.end(), prop);
        }

        virtual void rotate90deg() override {
            for_each_block([](auto& p) { p.rotate90deg(); });
        }
};

class Tetramino_2rotations : public Tetramino {
    bool rotated;
    public:
    Tetramino_2rotations(Point pos, MinoSz tetra) ;
    void rotate90deg() override {
        if (rotated) {
            for_each_block([](auto& p) { p.rotate270deg(); });
            rotated = false;
        } else {
            for_each_block([](auto& p) { p.rotate90deg(); });
            rotated = true;
        }
    }
};

class Tetramino_I : public Tetramino_2rotations {
    public:
    Tetramino_I(Point pos);
};

class Tetramino_O : public Tetramino {
    public:
    Tetramino_O(Point pos);
    void rotate90deg() override {}
};

class Tetramino_T : public Tetramino {
    public:
    Tetramino_T(Point pos);
};

class Tetramino_J : public Tetramino {
    public:
    Tetramino_J(Point pos);
    //void rotate90deg() { }
};

class Tetramino_L : public Tetramino {
    public:
    Tetramino_L(Point pos);
    //void rotate90deg() { }
};

class Tetramino_S : public Tetramino_2rotations {
    public:
    Tetramino_S(Point pos);
    //void rotate90deg() { }
};

class Tetramino_Z : public Tetramino_2rotations {
    public:
    Tetramino_Z(Point pos);
    //void rotate90deg() { }
};


} // namespace tetra

#endif 

