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

using namespace std;

typedef struct {
    unsigned char data[64];
    unsigned int datalen;
    unsigned int bitlen[2];
    unsigned int state[8];
} SHA256_CTX;

class crypto
{
public:
    static string SHA256(char *dat);

private:
    static void SHA256Transform(SHA256_CTX *ctx, unsigned char data[]);
    static void SHA256Init(SHA256_CTX *ctx);
    static void SHA256Update(SHA256_CTX *ctx, unsigned char data[], unsigned int len);
    static void SHA256Final(SHA256_CTX *ctx, unsigned char hash[]);
};

#endif /* crypto_h */
