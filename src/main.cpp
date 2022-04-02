#include <iostream>
#include "encryption.h"
#include "uint256_t.h" 
#include <string>
#include <ctime>

int main(){

    srand(static_cast<unsigned int>(time(0)));

    std::string p = "115792089237316195423570985008687907853269984665640564039457584007908834671663";
    std::string x = "55066263022277343669578718895168534326250603453777594175500187360389116729240";
    std::string y = "32670510020758816978083085130507043184471273380659243275938904335757337482424";
    std::string n = "115792089237316195423570985008687907852837564279074904382605163141518161494337";
    std::string private_key = "115792089237316195423570985008687907853269984665640564039457584007908834671663";
    std::string message = "31272006352818487860575454286046758918581076444685961675641400200272101685731";
    Encryption encr(p,x,y,n);

    encr.SetPrivateKey(private_key);


    encr.signedMessage = encr.Sign(message);

    encr.public_key = encr.CreatePublicKey();
    std::cout << "bool " << encr.Verify(encr.public_key, encr.signedMessage, message); 
    
    return 0;
}