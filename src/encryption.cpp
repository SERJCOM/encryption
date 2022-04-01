#include <iostream>
#include "encryption.h"
#include "uint256_t.h" 
#include <string>

Encryption::Encryption(const std::string p_string, const std::string x_string, const std::string y_string, const std::string n_string){
    uint8_t base = 10;
    this->p = uint256_t(p_string, base);
    this->x = uint256_t(x_string, base);
    this->y = uint256_t(y_string, base);
    this->n = uint256_t(n_string, base);
}
