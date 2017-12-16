//
//  main.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <iostream>
#include "block.h"
#include "blockChain.h"
#include "talk.h"

using namespace std;

int main(int argc, const char * argv[]) {

    cout << "Blockchain demo program." << endl;

    talk t;
    t.connect();

/*
    blockChain bc;
    cout << bc.getLatestBlock()->getData() << ", len = " << bc.length() << " " << blockChain::isValidChain(&bc) << endl;
    bc.addBlock(bc.generateNextBlock("nnnnnclark"));
    bc.addBlock(bc.generateNextBlock("nnclark"));
    bc.addBlock(bc.generateNextBlock("nclark"));
    cout << bc.getLatestBlock()->getData() << ", len = " << bc.length() << " " << blockChain::isValidChain(&bc) << endl;

    blockChain bd;
    cout << bd.getLatestBlock()->getData() << ", len = " << bd.length() << " " << blockChain::isValidChain(&bd) << endl;
    bd.addBlock(bd.generateNextBlock("clark2"));
    bd.addBlock(bd.generateNextBlock("clark3"));
    cout << bd.getLatestBlock()->getData() << ", len = " << bd.length() << " " << blockChain::isValidChain(&bd) << endl;

    bd.replaceChain(&bc);
    cout << bd.getLatestBlock()->getData() << ", len = " << bd.length() << " " << blockChain::isValidChain(&bd) << endl;
*/
    
    return 0;
}
