#pragma once

#include <string>
#include "uint256_t.h" 


class Encryption{
public:

    void SetPrivateKey(uint256_t private_key);

    bool Verify(uint256_t public_key, uint256_t signature, std::string text);

    uint256_t GetPrivateKey();

	uint256_t GenerateSignature(uint256_t private_key, std::string text);
    
    Encryption(const std::string p_string, const std::string x_string, const std::string y_string, const std::string n_string);

private:
    uint256_t private_key = 0;
    uint256_t public_key = 0;
    uint256_t p;
    uint256_t n;
    uint256_t message_hash;
    //base point
    uint256_t x = 0;
    uint256_t y = 0;
    
    uint256_t s(uint256_t x1,uint256_t y1,uint256_t x2,uint256_t y2);

    
};
