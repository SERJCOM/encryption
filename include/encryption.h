#pragma once

#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class Encryption{
public:

    struct sigMessage{
        cpp_int r, message;
    };

    struct PublicKey{
        cpp_int x,y;
    };

    PublicKey CreatePublicKey();

    void SetPrivateKey(std::string private_key);

    bool Verify(PublicKey public_key, Encryption::sigMessage signature, std::string text);

    cpp_int GetPrivateKey();

	cpp_int GenerateSignature(cpp_int private_key, std::string text);

    Encryption(const std::string p_string, const std::string x_string, const std::string y_string, const std::string n_string);

    sigMessage Sign(std::string message_text);

    cpp_int gcd(cpp_int num1, cpp_int num2, cpp_int &x, cpp_int &y); // advanced euclid algorithm

    void point_multiplication(cpp_int multiplier, cpp_int &x, cpp_int &y);

    PublicKey public_key ;
    sigMessage signedMessage;

private:
    cpp_int private_key;
    cpp_int p;
    cpp_int n;
    cpp_int message_hash;
    //base point
    cpp_int x = 0;
    cpp_int y = 0;
    
    cpp_int s(cpp_int x1,cpp_int y1,cpp_int x2,cpp_int y2);

    cpp_int xNew(cpp_int x1, cpp_int x2, cpp_int result_s);

    cpp_int yNew(cpp_int x1, cpp_int x3, cpp_int y1 , cpp_int result_s);
    
};
