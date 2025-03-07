#ifndef ECC_CAPSTONE_ECC_H
#define ECC_CAPSTONE_ECC_H
#include "elliptic_curve.h"

class ECC {
private:
    Elliptic_Curve curve;
    Elliptic_Curve::Point G;
    //int64_t private_key;
public:
    struct Key {
        int64_t private_key;
        Elliptic_Curve::Point public_key;
    };

    ECC(const Elliptic_Curve& curve, const Elliptic_Curve::Point& G);
    Key generate_key();
    pair<Elliptic_Curve::Point, Elliptic_Curve::Point> encrypt(const Elliptic_Curve::Point& message, const Elliptic_Curve::Point& public_key);
    Elliptic_Curve::Point decrypt(const std::pair<Elliptic_Curve::Point, Elliptic_Curve::Point>& ciphertext, int64_t private_key);
    int64_t get_order(const Elliptic_Curve::Point& G);
};

#endif //ECC_CAPSTONE_ECC_H
