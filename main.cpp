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
    cout << "Private Key: " << key_pair.private_key << endl;
    cout << "Public Key: (" << key_pair.public_key.x << ", " << key_pair.public_key.y << ")" << endl;

    // 메시지
    Elliptic_Curve::Point message(10, 20);
    cout << "\nMessage: (" << message.x << ", " << message.y << ")" << endl;

    // 암호화
    auto ciphertext = ecc.encrypt(message, key_pair.public_key);
    cout << "P1: (" << ciphertext.first.x << ", " << ciphertext.first.y << ")" << endl;
    cout << "P2: (" << ciphertext.second.x << ", " << ciphertext.second.y << ")" << endl;

    // 복호화
    Elliptic_Curve::Point decrypted = ecc.decrypt(ciphertext, key_pair.private_key);
    cout << "result: (" << decrypted.x << ", " << decrypted.y << ")" << endl;


    return 0;
}
