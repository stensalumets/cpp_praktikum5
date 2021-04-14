#ifndef LINE2_H
#define LINE2_H

#include <iostream>
#include "point2.h"
using std::ostream;

class Line2 {

public:
    Point2 p1;
    Point2 p2;

    Line2() = default;

    Line2(Point2 np1, Point2 np2) {
        p1 = np1;
        p2 = np2;
    }

    float length() {
        return p1.distanceFrom(p2);
    }

    bool operator==(const Line2& two) const {
        return (p1 == two.p1 && p2 == two.p2) || (p1 == two.p2 && p2 == two.p1);
    }

    friend ostream& operator<<(ostream& out, const Line2& l) {
        out << "(" << l.p1 << " - " << l.p2 << ")";
        return out;
    }
};
#endif // LINE2_H
