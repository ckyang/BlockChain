//
//  main.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <iostream>
#include "time.h"
#include "block.h"
#include "blockChain.h"

using namespace std;

int main(int argc, const char * argv[]) {

    cout << "abc" << endl;

    time_t t;
    time(&t);
    block *b = new block(5, "prehash", t, "data", "hash");
//    cout << "calhash = " << blockChain::calculateHash(9, "ab", t, "cd") << endl;
    cout << "index = " << b->getIndex() << endl;
    blockChain bc;
    cout << bc.getLatestBlock()->getData() << endl;
    cout << bc.generateNextBlock("nnnnnclark")->getData() << endl;
    return 0;
}
