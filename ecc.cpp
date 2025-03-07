#include "ecc.h"
#include <random>

ECC::ECC(const Elliptic_Curve& curve, const Elliptic_Curve::Point& G) : curve(curve), G(G) {
    if (!curve.is_on_curve(G)) {
        throw std::invalid_argument("점 G가 곡선 위에 없음");
    }
}

int64_t generate_random_private_key(int64_t p) {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<int64_t> dist(1, p - 1);
    return dist(gen);
}

ECC::Key ECC::generate_key() {
    int64_t private_key = generate_random_private_key(curve.p);
    Elliptic_Curve::Point public_key = curve.scalar_multiply(G, private_key);
    return {private_key, public_key};
}

pair<Elliptic_Curve::Point, Elliptic_Curve::Point> ECC::encrypt(const Elliptic_Curve::Point& message, const Elliptic_Curve::Point& public_key) {
    if (!curve.is_on_curve(public_key)) {
        throw invalid_argument("공개 키가 곡선 위에 없음");
    }
    int64_t random_k;
    Elliptic_Curve::Point P1;
    do {
        random_k = generate_random_private_key(curve.p);
        P1 = curve.scalar_multiply(G, random_k);
    } while (P1.x == 0 && P1.y == 0);
    Elliptic_Curve::Point P2 = curve.add(message, curve.scalar_multiply(public_key, random_k));
    return {P1, P2};
}

Elliptic_Curve::Point ECC::decrypt(const pair<Elliptic_Curve::Point, Elliptic_Curve::Point>& ciphertext, int64_t private_key) {
    Elliptic_Curve::Point P1 = ciphertext.first;
    Elliptic_Curve::Point P2 = ciphertext.second;
    Elliptic_Curve::Point neg_P1(P1.x, -P1.y);
    return curve.add(P2, curve.scalar_multiply(neg_P1, private_key));
}