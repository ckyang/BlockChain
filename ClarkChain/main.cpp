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
#include "crypto.h"

using namespace std;

enum USER_COMMAND
{
    USER_COMMAND_QUIT = 0,
    USER_COMMAND_ADD_BLOCK = 1,
    USER_COMMAND_LIST_BLOCKCHAIN = 2,
    USER_COMMAND_MAX
};

void* create_talk(void *talkClass)
{
    pthread_detach(pthread_self());
    ((talk*)talkClass)->connect();
    pthread_exit(0);
}

int main(int argc, const char * argv[]) {

    cout << "Blockchain demo program." << endl;
    blockChain* blockChainObject = factory::GetBlockChain();

    pthread_t thread;
    talk* talkObject = factory::GetTalk();
    pthread_create(&thread, NULL , create_talk, (void*) talkObject);

    crypto* cryptoObject = factory::GetCrypto();
//    ECDSA_SIG* sig = cryptoObject->sign("abc");
//    cout << cryptoObject->verify("abc", sig, NULL) << endl;

    //Handle user input
    while(true)
    {
        int input = 0;
        cout << "Please input your choice:" << endl;
        cout << USER_COMMAND_QUIT << ") : Quit" << endl;
        cout << USER_COMMAND_ADD_BLOCK << ") : Add block" << endl;
        cout << USER_COMMAND_LIST_BLOCKCHAIN << ") : List blockchain" << endl;
        cin >> input;

        switch(input)
        {
            case USER_COMMAND_QUIT:
                return 0;
            case USER_COMMAND_ADD_BLOCK:
            {
                char str[20] = {'\0'};
                cout << "Please input your block content:" << endl;
                scanf("%s", str);
                blockChainObject->addBlock(blockChainObject->generateNextBlock(string(str)));
                talk::broadcast(blockChainObject->getLatestBlock());
                break;
            }
            case USER_COMMAND_LIST_BLOCKCHAIN:
            {
                block* cur = blockChainObject->getLatestBlock();

                if(cur)
                    cout << "Index PreHash TimeStamp Data Hash" << endl;

                while(cur)
                {
                    cout << cur->getIndex() << " " << cur->getPreHash() << " " << cur->getTimeStamp() << " " << cur->getData() << " " << cur->getHash() << endl;
                    cur = blockChainObject->getBlock(cur->getPreHash());
                }
            }
            default:
                break;
        }
    }
    
    return 0;
}
