# encryption
ECC ENCRYPTION C++  secp256k1 SECP256K1 Elliptic curve cryptography LIBRARY library

To use my library first of all you need to download this repository with command 

`git clone --recursive https://github.com/SERJCOM/encryption`

after that, you can initialize the encryption with the parameters you need.
'''
- std::string p; // the number that characterizes the finite field
- std::string x; // x coordinate of your base point
- std::string y; // y coordinate of your base point
- std::string n; // the random number
- std::string private_key; // the random number
- std::string message; // sha256 of your message
'''
and enter these parameters when creating a class object.

To set your private key you need use this method: SetPrivateKey(private_key);

To create public key you need call this method CreatePublicKey() without any parameters and assign to object PublicKey of the class obect you use.

To do sign you need call this method Sign(message)() with sha256 of your text in std::string  and assign to object signedMessage of the class obect you use.

To verify any signature you need call this method Verify(object.public_key, object.signedMessage, message). object.public_key and object.signedMessage are public key and the signature of your message that you have made in the previos steps.
Message is sha256 written in std::string

in short, look at main.cpp and you'll understand everything yourself. It's like I'm explaining to a pythonist.


