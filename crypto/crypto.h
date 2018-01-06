//
//  crypto.h
//  BlockChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef crypto_h
#define crypto_h

#include <string>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>

using namespace std;

#define MAX_SIGNATURE_LEN 256
#define MAX_PUBLICKEY_LEN 256

class crypto
{
public:
    crypto();
    ~crypto();

    static string HASH(const char *data);

    void getPublicKey(unsigned char *pubKey, unsigned int& pubKeyLen);
    void sign(const string& message, unsigned char *signature, unsigned int& signatureLen);
    bool verify(const string& message, const unsigned char *signature, const unsigned int signatureLen, const unsigned char *pubKey, const unsigned int pubKeyLen);

private:
    void generateKeyPair();

    EC_KEY* m_pECCKeyPair;
};

#endif /* crypto_h */
