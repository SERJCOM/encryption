#include <iostream>
#include "encryption.h"
#include "uint256_t.h" 
#include <string>
#include <vector>

// TO DO
// СДЕЛАТЬ РЕАЛИЗАЦИЮ ФУНКЦИИ S, SetPrivateKey, Verify, GetPrivateKey, GenerateSignature, 
// 

Encryption::Encryption(const std::string p_string, const std::string x_string, const std::string y_string, const std::string n_string){
    uint8_t base = 10;
    this->p = uint256_t(p_string, base);
    this->x = uint256_t(x_string, base);
    this->y = uint256_t(y_string, base);
    this->n = uint256_t(n_string, base);
}

uint256_t Encryption::gcd(uint256_t num1, uint256_t num2, uint256_t &x, uint256_t &y){
    if (num1 == 0) {
		x = 0; y = 1;
		return num2;
	}
	uint256_t x1, y1;
	uint256_t d = gcd(num2%num1, num1, x1, y1);
	x = y1 - (num2 / num1) * x1;
	y = x1;
	return d;
}

uint256_t Encryption::s(uint256_t x1,uint256_t y1,uint256_t x2,uint256_t y2, uint256_t p){
    if(x1 == x2 && y1 == y2){
        uint256_t y,x;
        uint256_t ynew = gcd(p, 2 * y2, x,y);
        return (3 * x1 * x1 * y) % p;
    }
    else{
        uint256_t y,x;
        uint256_t ynew = gcd(p, x2 - x1, x,y);
        return ((y2 - y1) * y) % p;
    }
}

uint256_t Encryption::xNew(uint256_t x1, uint256_t x2, uint256_t result_s, uint256_t p){
    return (result_s * result_s - x1 - x2) % p;
}

uint256_t Encryption::yNew(uint256_t x1, uint256_t x3, uint256_t y1 , uint256_t result_s, uint256_t p){
    return (result_s * (x1 - x3) - y1) % p;
}

void Encryption::point_multiplication(uint256_t multiplier, uint256_t &x, uint256_t &y, uint256_t p){

    struct point{
        uint256_t x, y;
    };

    std::vector <uint256_t> a;
    std::vector <point> b; 
    
    uint256_t xa = x;
    uint256_t ya = y;

    uint256_t new_multiplier = 1;

    int count = 0;

    while(new_multiplier != multiplier && new_multiplier < multiplier){
        a.push_back(new_multiplier);
        b.push_back({xa,ya});
        
        if(new_multiplier * 2 <= multiplier){
            new_multiplier = new_multiplier * 2;
            uint256_t result = s(xa,ya,xa,ya,p);
            uint256_t xa1 = xNew(xa,xa,result,p);
            ya = yNew(xa,xa1, ya, result, p);
            xa = xa1;
        }
        else{
            for(int i = a.size() - 1; i > -1; i--){
                if(new_multiplier + a[i] <= multiplier){
                    new_multiplier = new_multiplier + a[i];
                    uint256_t result = s(xa,ya, b[i].x, b[i].y, p);
                    uint256_t xa1 = xNew(xa,b[i].x, result, p);
                    ya = yNew(xa,xa1, ya, result, p);
                    xa = xa1;
                }
            }
        }
        count++;
    }
}

