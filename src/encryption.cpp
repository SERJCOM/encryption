#include <iostream>
#include "encryption.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random.hpp>
using namespace boost::multiprecision;
namespace mp = boost::multiprecision;
using namespace boost::random;
#include <string>
#include <vector>
#include <ctime>
#include <random>


// TO DO
// СДЕЛАТЬ РЕАЛИЗАЦИЮ ФУНКЦИИ S, SetPrivateKey, Verify, GetPrivateKey, GenerateSignature, 
// ПОМЕНЯТЬ ПЕРЕМЕННУЮ n НА КОНСТАНТУ 

mt19937 mt;
uniform_int_distribution<cpp_int> ui(-(cpp_int(1) << 256), cpp_int(1) << 256);

cpp_int remainder(cpp_int a, cpp_int m){
    if(a > 0){
        return a % m;
    }
    return (a % m + m) % m;
}

Encryption::Encryption(const std::string p_string, const std::string x_string, const std::string y_string, const std::string n_string){
    uint8_t base = 10;
    this->p = cpp_int(p_string);
    this->x = cpp_int(x_string);
    this->y = cpp_int(y_string);
    this->n = cpp_int(n_string);
}

void Encryption::SetPrivateKey(const std::string privatekey){
    
    uint8_t base = 10;
    this->private_key = cpp_int(privatekey);
}

cpp_int Encryption::GetPrivateKey(){
    return this->private_key;
}

cpp_int Encryption::gcd(cpp_int num1, cpp_int num2, cpp_int &x, cpp_int &y){
    if (num1 == 0) {
		x = 0; y = 1;
		return num2;
	}
	cpp_int x1, y1;
	cpp_int d = gcd(remainder(num2,num1), num1, x1, y1);
	x = y1 - (num2 / num1) * x1;
	y = x1;
	return d;
}

cpp_int Encryption::s(cpp_int x1,cpp_int y1,cpp_int x2,cpp_int y2){
    if(x1 == x2 && y1 == y2){
        cpp_int y,x;
        cpp_int ynew = gcd(p, 2 * y2, x,y);
        return remainder(3 * x1 * x1 * y, this->p);
    }
    else{
        cpp_int y,x;
        cpp_int ynew = gcd(p, x2 - x1, x,y);
        return remainder((y2 - y1) * y,  this->p);
    }
}

cpp_int Encryption::xNew(cpp_int x1, cpp_int x2, cpp_int result_s){
    return remainder(result_s * result_s - x1 - x2, this->p);
}

cpp_int Encryption::yNew(cpp_int x1, cpp_int x3, cpp_int y1 , cpp_int result_s){
    
    cpp_int vit = x1 - x3;
    cpp_int umn = result_s * vit - y1;
    
    return remainder(umn, this->p);
}
void Encryption::point_multiplication(cpp_int multiplier, cpp_int &x, cpp_int &y){

    struct point{
        cpp_int x, y;
    };

    std::vector <cpp_int> a;
    std::vector <point> b; 

    cpp_int xa = x;
    cpp_int ya = y;

    cpp_int new_multiplier = 1;

    int count = 0;
    while(new_multiplier != multiplier && new_multiplier < multiplier){
        a.push_back(new_multiplier);
        b.push_back({xa,ya});
        
        if(new_multiplier * 2 <= multiplier){
            new_multiplier = new_multiplier * 2;
            cpp_int result = s(xa,ya,xa,ya);
            cpp_int xa1 = xNew(xa,xa,result);
            ya = yNew(xa,xa1, ya, result);
            xa = xa1;
        }
        if(new_multiplier * 2 > multiplier){
            for(int i = a.size() - 1; i > -1; i--){
                if(new_multiplier + a[i] <= multiplier){
                    new_multiplier = new_multiplier + a[i];
                    cpp_int result = s(xa,ya, b[i].x, b[i].y);
                    cpp_int xa1 = xNew(xa,b[i].x, result);
                    ya = yNew(xa,xa1, ya, result);
                    xa = xa1;
                }
            }
        }
        count++;
    }
    x = xa;
    y = ya;
}

Encryption::sigMessage Encryption::Sign(std::string message_text){
    cpp_int message = cpp_int(message_text);
    cpp_int r = 0;
    sigMessage sig;
    cpp_int k = 0;
    k = ui(mt);
    cpp_int x = this->x, y = this->y, xgcd, ygcd;
    point_multiplication(k, x,y);
    r = x % n;
    cpp_int gcdnew = gcd(this->n, k, xgcd,ygcd);
    message = remainder((message + r * this->private_key) * ygcd, this->n);
    sig.message = message;
    sig.r = r;
    return sig;
}

Encryption::PublicKey Encryption::CreatePublicKey(){
    PublicKey pr;
    pr.x = this->x;
    pr.y = this->y;
    point_multiplication(this->private_key, pr.x, pr.y);
    return pr;
}

bool Encryption::Verify(Encryption::PublicKey public_key, Encryption::sigMessage signature, std::string message_text){
    cpp_int text = cpp_int(message_text);

    bool flag = false;
    if(signature.r >= 1 && signature.r < this->n - 1 && signature.message >= 1 && signature.message < this->n - 1){
        cpp_int xgcd, ygcd, w, u, v, xuG = this->x, yuG = this->y, xvQ = public_key.x, yvQ = public_key.y;
        w = gcd(n, signature.message, xgcd, ygcd);

        w = ygcd;

        u = remainder((text * w), this->n);

        v = remainder((signature.r * w), this->n);  
        point_multiplication(u,  xuG, yuG);
        point_multiplication(v, xvQ , yvQ);
        cpp_int result = s(xuG, yuG, xvQ, yvQ);
        cpp_int xv, yv;
        xv = xNew(xuG, xvQ, result);
        yv = yNew(xuG, xv, yuG, result);
        if(signature.r == remainder(xv, this->n)){
            flag = true;
        }
    }
    return flag;
}