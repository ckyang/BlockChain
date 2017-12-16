//
//  blockChain.h
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef blockChain_h
#define blockChain_h

#include <string>

using namespace std;

class block;

typedef struct blockNode {
    block *m_cur;
    block *m_next;
    blockNode(block* cur, block* next): m_cur(cur), m_next(next){};
} blockNode;

class blockChain
{
public:
    blockChain();

    block* generateNextBlock(const string& data);
    block *getLatestBlock(){return tail->m_cur;}

private:
    block *getGenesisBlock();
    static string calculateHash(const int index, const string& preHash, const time_t& timeStamp, const string& data);

    blockNode *head;
    blockNode *tail;
};

#endif /* blockChain_h */
