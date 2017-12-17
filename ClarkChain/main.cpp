//
//  main.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <iostream>
#include "block.h"
#include "factory.h"
#include "blockChain.h"
#include "talk.h"

using namespace std;

enum COMMAND
{
    COMMAND_QUIT = 0,
    COMMAND_ADD_BLOCK = 1,
    COMMAND_LIST_BLOCKCHAIN = 2,
    COMMAND_MAX
};

void* create_talk(void *talkClass)
{
    pthread_detach(pthread_self());
    ((talk*)talkClass)->connect(7000);
    pthread_exit(0);
}

int main(int argc, const char * argv[]) {

    cout << "Blockchain demo program." << endl;
    cout << "Initialize blockchain..." << endl;
    blockChain* blockChainObject = factory::GetBlockChain();
    cout << "Blockchain initialized." << endl;
/*
    cout << blockChainObject->getLatestBlock()->getData() << ", len = " << blockChainObject->length() << " " << blockChain::isValidChain(blockChainObject) << endl;
    blockChainObject->addBlock(blockChainObject->generateNextBlock("nnnnnclark"));
    blockChainObject->addBlock(blockChainObject->generateNextBlock("nnclark"));
    blockChainObject->addBlock(blockChainObject->generateNextBlock("nclark"));
    cout << blockChainObject->getLatestBlock()->getData() << ", len = " << blockChainObject->length() << " " << blockChain::isValidChain(blockChainObject) << endl;
*/

    pthread_t thread;
    talk* talkObject = factory::GetTalk();
    pthread_create(&thread, NULL , create_talk, (void*) talkObject);

    while(true)
    {
        int input = 0;
        cout << "Please input your choice:" << endl;
        cout << COMMAND_QUIT << ") : Quit" << endl;
        cout << COMMAND_ADD_BLOCK << ") : Add block" << endl;
        cout << COMMAND_LIST_BLOCKCHAIN << ") : List blockchain" << endl;
        cin >> input;

        switch(input)
        {
            case COMMAND_QUIT:
                return 0;
            case COMMAND_ADD_BLOCK:
            {
                char str[20] = {'\0'};
                cout << "Please input your block content:" << endl;
                scanf("%s", str);
                blockChainObject->addBlock(blockChainObject->generateNextBlock(string(str)));
                talkObject->broadcast(string("NEW ") + blockChainObject->getLatestBlock()->getBlockInfo());
                break;
            }
            default:
                break;
        }

        
    }
//    cin >> input;
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
