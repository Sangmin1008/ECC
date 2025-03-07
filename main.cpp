#include <iostream>
#include "ecc.h"

using namespace std;

int main() {
    // 타원곡선 y^2 = x^3 + 2x + 3 (mod 97)
    Elliptic_Curve curve(2, 3, 97);
    Elliptic_Curve::Point G(3, 6);

    // ECC 객체 생성
    ECC ecc(curve, G);

    // 키 생성
    ECC::Key key_pair = ecc.generate_key();
    cout << "개인키: " << key_pair.private_key << endl;
    cout << "공개키: (" << key_pair.public_key.x << ", " << key_pair.public_key.y << ")" << endl;

    // 메시지
    Elliptic_Curve::Point message(10, 20);  // 예제 메시지
    cout << "\n원본 메시지: (" << message.x << ", " << message.y << ")" << endl;

    // 암호화
    auto ciphertext = ecc.encrypt(message, key_pair.public_key);
    cout << "암호화된 메시지 P1: (" << ciphertext.first.x << ", " << ciphertext.first.y << ")" << endl;
    cout << "암호화된 메시지 P2: (" << ciphertext.second.x << ", " << ciphertext.second.y << ")" << endl;

    // 복호화
    Elliptic_Curve::Point decrypted = ecc.decrypt(ciphertext, key_pair.private_key);
    cout << "복호화된 메시지: (" << decrypted.x << ", " << decrypted.y << ")" << endl;

    return 0;
}
