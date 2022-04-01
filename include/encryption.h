#pragma once

#include <string>
#include "uint256_t.h"  

class Encryption{
private:
    uint256_t private_key = 0;
    uint256_t public_key = 0;
    uint256_t p = 0;
    //base point
    uint256_t x = 0;
    uint256_t y = 0;
    uint256_t n;
    uint256_t message_hash;
public:
    uint256_t get_private_key(){return this->private_key;}
};
