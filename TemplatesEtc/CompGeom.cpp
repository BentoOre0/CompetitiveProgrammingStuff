#include <bits/stdc++.h>
#define x real()
#define y imag()


using namespace std;


typedef int T;
typedef complex<int> Point2D;


struct Interval {
    T left;
    T right;


    bool operator==(const Interval& other) const {
        return left == other.left && right == other.right;
    }


    bool operator!=(const Interval& other) const {
        return left != other.left || right != other.right;
    }


    bool operator<(const Interval& other) const {
        return left < other.left || (left == other.left && right < other.right);
    }


    bool overlaps(const Interval& other) const {
        return left <= other.right && right >= other.left;
    }


    bool contains(T val) {
        return left <= val && val <= right;
    }


    T size() {
        return right - left;
    }
};


ostream& operator<<(ostream& os, const Interval& interval) {
    return os << "[" << interval.left << ", " << interval.right << "]";
}


Interval interval_union(Interval &i1, Interval &i2) {
    if (!i1.overlaps(i2)) return {0, -1};
    return {min(i1.left, i2.left), max(i1.right, i2.right)};
}


Interval interval_intersection(Interval &i1, Interval &i2) {
    if (!i1.overlaps(i2)) return {0, -1};
    return {max(i1.left, i2.left), min(i1.right, i2.right)};
}


/**
 * ------------U
 * |           |  [y1, y2]
 * |           |
 * L------------
 *    [x1, x2]
 */


struct Rectangle {
    Point2D ll, ur;
    Interval xint, yint;


    Rectangle(Point2D ll, Point2D ur) {
        this->ll = ll;
        this->ur = ur;
        this->xint = {ll.x, ur.x};
        this->yint = {ll.y, ur.y};
    }


    T area() {
        return xint.size() * yint.size();
    }


    bool overlaps(Rectangle& other) {
        return xint.overlaps(other.xint) && yint.overlaps(other.yint);
    }
};


Rectangle rectangle_intersection(Rectangle& r1, Rectangle& r2) {
    if (!r1.overlaps(r2)) return {{0, 0}, {-1, -1}};
    Interval xint = interval_intersection(r1.xint, r2.xint);
    Interval yint = interval_intersection(r1.yint, r2.yint);
    return {{xint.left, yint.left}, {xint.right, yint.right}};
}




int main() {
    Rectangle r{{1, 2}, {3, 4}};
    cout << r.area() << endl;
    return 0;
}
