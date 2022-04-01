#include <iostream>
#include <encryption.h>

int main(){
    Encryption encr;
    std::cout << encr.get_private_key() << std::endl;
    return 0;
}