#include <bits/stdc++.h>                                                        
using namespace std;                                                            
using ll = long long;                                                           
using pii = pair<int,int>;                                                      
using pll = pair<long long int, long long int>; 
#define x real()
#define y imag()                                
const int inf = numeric_limits<int>::max();                                     
const ll INF = numeric_limits<ll>::max();                                       
const char sp = ' ';                                                            
const char nl = '\n';                                                           

// int main(){   
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     // freopen("paint.in", "r", stdin);
//     // freopen("paint.out", "w", stdout);                                                                 
    
// }    


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
    if (!r1.overlaps(r2)) return {{0, 0}, {0, 0}};
    Interval xint = interval_intersection(r1.xint, r2.xint);
    Interval yint = interval_intersection(r1.yint, r2.yint);
    return {{xint.left, yint.left}, {xint.right, yint.right}};
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout); 
    int a1,a2,a3,a4;
    int b1,b2,b3,b4;
    int tr1,tr2,tr3,tr4;
    cin >> a1 >> a2 >> a3 >> a4;
    cin >> b1 >> b2 >> b3 >> b4;
    cin >> tr1 >> tr2 >> tr3 >> tr4;
    Rectangle a{{a1, a2}, {a3, a4}};
    Rectangle b{{b1, b2}, {b3, b4}};
    Rectangle tr{{tr1, tr2}, {tr3, tr4}};
    // cout << r.area() << endl;
    Rectangle atotr = rectangle_intersection(a,tr);
    Rectangle btotr = rectangle_intersection(b,tr);
    int area = a.area() + b.area();
    // Rectangle shit{{0,0},{-1,-1}};
    area -= atotr.area();
    area -= btotr.area();
    cout << area << nl;
    return 0;
}