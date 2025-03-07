#include "elliptic_curve.h"

Elliptic_Curve::Elliptic_Curve(int64_t a, int64_t b, int64_t p) : a(a), b(b), p(p) {
    if (!is_valid_curve()) {
        throw invalid_argument("잘못된 타원 곡선");
    }
}

int64_t mod(int64_t x, int64_t p) {
    return ((x % p) + p) % p;
}

int64_t mod_inv(int64_t x, int64_t p) {
    int64_t res = 1, y = p - 2;
    while (y) {
        if (y & 1) res = (res * x) % p;
        x = (x * x) % p;
        y >>= 1;
    }
    return res;
}

bool Elliptic_Curve::is_valid_curve() const {
    return mod(4 * a * a * a + 27 * b * b, p) != 0;
}

Elliptic_Curve::Point Elliptic_Curve::add(const Elliptic_Curve::Point &P, const Elliptic_Curve::Point &Q) {
    if (P.is_infinity) return Q;
    if (Q.is_infinity) return P;

    if (P.x == Q.x && P.y != Q.y) return Point();

    int64_t lambda;
    if (P == Q) lambda = mod((3 * P.x * P.x + a) * mod_inv(2 * P.y, p), p);
    else lambda = mod((Q.y - P.y) * mod_inv(Q.x - P.x, p), p);

    int64_t x3 = mod(mod(lambda * lambda, p) - P.x - Q.x, p);
    int64_t y3 = mod(mod(lambda * (P.x - x3), p) - P.y, p);

    return Point(x3, y3);
}

/*
Elliptic_Curve::Point Elliptic_Curve::scalar_multiply(const Point& P, int64_t k) {
    Point result;
    Point base = P;
    while (k) {
        if (k & 1) result = add(result, base);
        base = add(base, base);
        k >>= 1;
    }
    return result;
}
*/

Elliptic_Curve::Point Elliptic_Curve::scalar_multiply(const Point& P, int64_t k) {
    Point R0, R1 = P;
    R0.is_infinity = true;

    for (int i = 63; i >= 0; --i) {
        if (k & (1LL << i)) {
            R1 = add(R0, R1);
            R0 = add(R0, R0);
        } else {
            R0 = add(R0, R1);
            R1 = add(R1, R1);
        }
    }
    return R0;
}

bool Elliptic_Curve::is_on_curve(const Point& P) const {
    if (P.is_infinity) return true;
    return mod(P.y * P.y, p) == mod(P.x * P.x * P.x + a * P.x + b, p);
}