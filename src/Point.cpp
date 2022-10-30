#include "Point.h"

Point operator+(const Point& p, const Point& q) {
        return Point {p.x + q.x, p.y + q.y };
}

Point rotate90deg(Point p) {
    p.rotate90deg();
    return p;
}

