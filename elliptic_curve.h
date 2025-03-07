#ifndef ECC_CAPSTONE_ELLIPTIC_CURVE_H
#define ECC_CAPSTONE_ELLIPTIC_CURVE_H

#include <bits/stdc++.h>
using namespace std;

class Elliptic_Curve {
private:
    int64_t a, b, p;

public:
    friend class ECC;
    Elliptic_Curve(int64_t a, int64_t b, int64_t p);
    bool is_valid_curve() const;

    struct Point {
        int64_t x, y;
        bool is_infinity;
        Point() : x(0), y(0), is_infinity(true) {}
        Point(int64_t x, int64_t y) : x(x), y(y), is_infinity(false) {}

        bool operator==(const Point& other) const {
            return (is_infinity && other.is_infinity) ||
                   (!is_infinity && !other.is_infinity && x == other.x && y == other.y);
        }

        bool operator!=(const Point& other) const {
            return !(*this == other);
        }
    };

    Point add(const Point& P, const Point& Q);
    Point scalar_multiply(const Point& P, int64_t k);
    bool is_on_curve(const Point& P) const;
};

#endif //ECC_CAPSTONE_ELLIPTIC_CURVE_H
