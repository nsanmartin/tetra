#ifndef __H_POINT_H_
#define __H_POINT_H_

struct Point {
    int x,y;
    //Point operator+(const Point& o) { return Point{x+o.x, y+o.y}; }
};

Point operator+(const Point& p, const Point& q);
#endif

