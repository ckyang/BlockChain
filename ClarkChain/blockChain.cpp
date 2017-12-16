//
//  blockChain.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <iostream>
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
    head = getGenesisBlock();
    tail = head;
    len = 1;
    hashList[head->getHash()] = head;
}

block* blockChain::getGenesisBlock()
{
    return new block(0, "0", 1465154705, "Clark Chain Genesis Block", "816534932c2b7154836da6afc367695e6337db8a921823784c14378abed4f7d7");
}

block* blockChain::generateNextBlock(const string& data)
{
    time_t timeStamp;
    time(&timeStamp);
    return new block(tail->getIndex() + 1, tail->getHash(), timeStamp, data, calculateHash(tail->getIndex() + 1, tail->getHash(), timeStamp, data));
}

void blockChain::addBlock(block *newBlock)
{
    tail = newBlock;
    hashList[newBlock->getHash()] = newBlock;
    ++len;
}

bool blockChain::isValidBlock(block* newBlock, block* preBlock)
{
    if(preBlock->getIndex() + 1 != newBlock->getIndex())
    {
        cout << "Invalid index" << endl;
        return false;
    }

    if(preBlock->getHash() != newBlock->getPreHash())
    {
        cout << "Invalid previoushash" << endl;
        return false;
    }

    string newHash = calculateHash(newBlock->getIndex(), newBlock->getPreHash(), newBlock->getTimeStamp(), newBlock->getData());

    if(newHash != newBlock->getHash())
    {
        cout << "Invalid hash: " << newHash << " " << newBlock->getHash() << endl;
        return false;
    }

    return true;
}

bool blockChain::isValidChain(blockChain * const chain)
{
    block *cur = chain->getLatestBlock();

    while(cur)
    {
        block *pre = chain->getBlock(cur->getPreHash());

        if(!pre)
            return true;

        if(!isValidBlock(cur, pre))
            return false;

        cur = pre;
    }

    return true;
}

void blockChain::replaceChain(blockChain * const newChain)
{
    if(!isValidChain(newChain) || newChain->length() <= len)
    {
        cout << "Received blockchain invalid, not replaced." << endl;
        return;
    }

    cout << "Received blockchain is valid. Replacing current blockchain with received blockchain." << endl;

    block *cur = getLatestBlock();

    while(cur)
    {
        block *pre = hashList[cur->getPreHash()];
        delete cur;
        cur = pre;
    }

    hashList.clear();

    tail = newChain->getLatestBlock();
    cur = tail;

    while(cur)
    {
        block *pre = newChain->getBlock(cur->getPreHash());
        hashList[cur->getHash()] = new block(cur);
        head = cur;
        cur = pre;
    }

    len = newChain->length();
//    broadcast(responseLatestMsg());
}
