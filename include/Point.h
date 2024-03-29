#ifndef __H_POINT_H_
#define __H_POINT_H_

#include <utility>

struct Point {
    int x,y;
    //Point operator+(const Point& o) { return Point{x+o.x, y+o.y}; }
    void rotate90deg() {
        y = -y;
        std::swap(x,y);
    }

    void rotate270deg() {
        // Rv = [ 0, 1][x] = [y]
        //      [-1, 0][y]   [-x]
        x = -x;
        std::swap(x,y);
    }
};

Point operator+(const Point& p, const Point& q);

Point rotate90deg(Point p);
#endif

