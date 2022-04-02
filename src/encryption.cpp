#include <iostream>
#include "encryption.h"
#include "uint256_t.h" 
#include <string>
#include <vector>
#include <ctime>

// TO DO
// СДЕЛАТЬ РЕАЛИЗАЦИЮ ФУНКЦИИ S, SetPrivateKey, Verify, GetPrivateKey, GenerateSignature, 
// ПОМЕНЯТЬ ПЕРЕМЕННУЮ n НА КОНСТАНТУ 

Encryption::Encryption(const std::string p_string, const std::string x_string, const std::string y_string, const std::string n_string){
    uint8_t base = 10;
    this->p = uint256_t(p_string, base);
    this->x = uint256_t(x_string, base);
    this->y = uint256_t(y_string, base);
    this->n = uint256_t(n_string, base);
}

void Encryption::SetPrivateKey(const std::string privatekey){
    
    uint8_t base = 10;
    this->private_key = uint256_t(privatekey, base);
}

uint256_t Encryption::GetPrivateKey(){
    return this->private_key;
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

uint256_t Encryption::s(uint256_t x1,uint256_t y1,uint256_t x2,uint256_t y2){
    if(x1 == x2 && y1 == y2){
        uint256_t y,x;
        uint256_t ynew = gcd(p, 2 * y2, x,y);
        return (3 * x1 * x1 * y) % this->p;
    }
    else{
        uint256_t y,x;
        uint256_t ynew = gcd(p, x2 - x1, x,y);
        return ((y2 - y1) * y) % this->p;
    }
}

uint256_t Encryption::xNew(uint256_t x1, uint256_t x2, uint256_t result_s){
    return (result_s * result_s - x1 - x2) % this->p;
}

uint256_t Encryption::yNew(uint256_t x1, uint256_t x3, uint256_t y1 , uint256_t result_s){
    return (result_s * (x1 - x3) - y1) % this->p;
}

void Encryption::point_multiplication(uint256_t multiplier, uint256_t &x, uint256_t &y){

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
            uint256_t result = s(xa,ya,xa,ya);
            uint256_t xa1 = xNew(xa,xa,result);
            ya = yNew(xa,xa1, ya, result);
            xa = xa1;
        }
        else{
            for(size_t i = a.size() - 1; i > -1; i--){
                if(new_multiplier + a[i] <= multiplier){
                    new_multiplier = new_multiplier + a[i];
                    uint256_t result = s(xa,ya, b[i].x, b[i].y);
                    uint256_t xa1 = xNew(xa,b[i].x, result);
                    ya = yNew(xa,xa1, ya, result);
                    xa = xa1;
                }
            }
        }
        count++;
    }
}

uint256_t getRandomNumber(uint256_t min, uint256_t max)
{
    static const uint256_t fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<uint256_t>(rand() * fraction * (max - min + 1) + min);
}

Encryption::sigMessage Encryption::Sign(std::string message_text){
    uint256_t message = uint256_t(message_text, 10);
    uint256_t r = 0;
    sigMessage sig;
    uint256_t k = 0;
    while(k == 0 || r == 0 || message == 0){
        //k = getRandomNumber(1, this->n - 1);
        k = 9;
        uint256_t x = this->x, y = this->y, xgcd, ygcd;
        point_multiplication(k, x,y);
        r = x % n;
        uint256_t gcdnew = gcd(this->n, k, xgcd,ygcd);
        message = ((message + r * this->private_key) * ygcd) % this->n;
    }

    sig.message = message;
    sig.r = r;

    return sig;
}

Encryption::PublicKey Encryption::CreatePublicKey(){
    PublicKey pr;
    point_multiplication(this->private_key, pr.x, pr.y);
    return pr;
}

bool Encryption::Verify(Encryption::PublicKey public_key, Encryption::sigMessage signature, std::string message_text){
    uint256_t text = uint256_t(message_text, 10);

    bool flag = false;
    if(signature.r >= 1 && signature.r < this->n - 1 && signature.message >= 1 && signature.message < this->n - 1){
        uint256_t xgcd, ygcd, w, u, v, xuG, yuG, xvQ = public_key.x, yvQ = public_key.y;
        w = gcd(n, signature.message, xgcd, ygcd);
        w = ygcd;

        u = (text * w) % this->n;

        v = (signature.r * w) % this->n;

        point_multiplication(u,  xuG, yuG);
        point_multiplication(v, xvQ , yvQ);

        uint256_t result = (xuG, yuG, xvQ, yvQ);

        uint256_t xv, yv;
        xv = xNew(xuG, xvQ, result);
        yv = yNew(xuG, xv, yuG, result);

        if(signature.r == xv % this->n){
            flag = true;
        }
    }
    return flag;
}