//
//  blockChain.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include "blockChain.h"
#include "crypto.h"
#include "block.h"

string blockChain::calculateHash(const int index, const string& preHash, const time_t& timeStamp, const string& data)
{
    string s(to_string(index) + data + to_string(timeStamp) + preHash);
    char *tmp = new char[s.length() + 1];
    strcpy(tmp, s.c_str());
    s = crypto::SHA256(tmp);
    delete []tmp;
    return s;
}

blockChain::blockChain()
{
    head = new blockNode(getGenesisBlock(), NULL);
    tail = head;
}

block* blockChain::getGenesisBlock()
{
    return new block(0, "0", 1465154705, "Clark Chain Genesis Block", "816534932c2b7154836da6afc367695e6337db8a921823784c14378abed4f7d7");
}

block* blockChain::generateNextBlock(const string& data)
{
    time_t timeStamp;
    time(&timeStamp);
    return new block(tail->m_cur->getIndex() + 1, tail->m_cur->getHash(), timeStamp, data, calculateHash(tail->m_cur->getIndex() + 1, tail->m_cur->getHash(), timeStamp, data));
}
