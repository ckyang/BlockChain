//
//  crypto.h
//  ClarkChain
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

class crypto
{
public:
    crypto();
    ~crypto();
    static string HASH(const char *data);

    ECDSA_SIG* sign(const string& message);
    bool verify(const string& message, ECDSA_SIG const * signature, EC_KEY* public_key);

private:
    void generateKeyPair();

    EVP_PKEY* m_pkey;
    EC_KEY* m_myecc;
    BIO* m_pbio_key_file;
};

#endif /* crypto_h */
