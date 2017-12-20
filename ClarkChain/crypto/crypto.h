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

class crypto
{
public:
    static string HASH(char *data);
};

#endif /* crypto_h */
