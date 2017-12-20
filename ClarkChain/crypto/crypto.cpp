//
//  crypto.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include "crypto.h"
#include "sha.h"

string crypto::HASH(char *data)
{
    return SHA256(data);
}

