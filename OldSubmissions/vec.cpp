#include <bits/stdc++.h>
#define x real()
#define y imag()

using namespace std;

typedef int T;
typedef complex<int> Vector2D;
typedef complex<int> Point2D;

double abs(Vector2D v) { return sqrt(double(v.x * v.x) + double(v.y * v.y)); }
T norm(Vector2D v) { return v.x * v.x + v.y * v.y; }
int dot(Vector2D v1, Vector2D v2) { return v1.x * v2.x + v1.y * v2.y; }
int cross(Vector2D v1, Vector2D v2) { return v1.x * v2.y - v1.y * v2.x; }

double angle_between(Vector2D a, Vector2D b) {
    double cos_theta = dot(a, b) / abs(a) / abs(b);
    cos_theta = max(-1.0, min(1.0, cos_theta));
    return acos(cos_theta);
}

Vector2D vector_between(Point2D p1, Point2D p2) { return p2 - p1; }

int orient(Point2D a, Point2D b, Point2D c) {
    return cross(
        vector_between(a, b),
        vector_between(a, c)
    );
}

bool point_in_angle(Vector2D ab, Vector2D ac, Point2D p) {
    if (cross(ab, ac) < 0) swap(ab, ac);
    Vector2D ap = p;
    return cross(ab, ap) > 0 && cross(ap, ac) > 0;
}

int half(Point2D p) {
    if (p.y > 0 || (p.y == 0 && p.x > 0)) return 0;
    return 1;
}

int main() {
    vector<Point2D> points = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {-1, -1}, {-1, 1}, {1, -1}};
    sort(points.begin(), points.end(), 
        [](Point2D a, Point2D b) {
            if (orient({0, 0}, a, b) == 0) return norm(a) < norm(b); 
            if (half(a) == half(b)) return orient({0, 0}, a, b) > 0;
            return half(a) < half(b);
        });
    for (Point2D p : points) {
        cout << p << endl;
    }
    return 0;
}