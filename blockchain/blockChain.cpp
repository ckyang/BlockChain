//
//  blockChain.cpp
//  BlockChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <stack>
#include "blockChain.h"
#include "crypto.h"
#include "block.h"
#include "factory.h"
#include "talk.h"
#include "dialog.h"

string blockChain::calculateHash(const int index, const string& preHash, const time_t& timeStamp, const string& data)
{
    string s(to_string(index) + data + to_string(timeStamp) + preHash);
    char *tmp = new char[s.length() + 1];
    strcpy(tmp, s.c_str());
    s = crypto::HASH(tmp);
    delete []tmp;
    return s;
}

blockChain::blockChain(bool bGenerateGenesis)
{
    dialog* dialog = factory::GetDialog();
    dialog->AppendLog("Initialize blockchain...");

    head = NULL;
    tail = NULL;
    len = 0;

    if(bGenerateGenesis)
        addBlock(getGenesisBlock());

    dialog->AppendLog("Blockchain initialized.");
}

block* blockChain::getGenesisBlock()
{
    return new block(0, "816534932c2b7154836da6afc367695e6337db8a921823784c14378abed4f7d7", 1513598789, "Clark_Chain_Genesis_Block", "a8b407b3c63fed132d8313960335c63c25a705e4fe558ba2e70e5bde6e10abfc");
}

block* blockChain::generateNextBlock(const string& data)
{
    time_t timeStamp;
    time(&timeStamp);
    return new block(tail->getIndex() + 1, tail->getHash(), timeStamp, data, calculateHash(tail->getIndex() + 1, tail->getHash(), timeStamp, data));
}

void blockChain::addBlock(block *newBlock)
{
    head = !head ? newBlock : head;
    tail = newBlock;
    hashList[newBlock->getHash()] = newBlock;
    ++len;
}

bool blockChain::isValidBlock(const int index, const string& preHash, const time_t& timeStamp, const string& data, const string& hash, block* preBlock)
{
    dialog* dialog = factory::GetDialog();

    if(preBlock->getIndex() + 1 != index)
    {
        dialog->AppendLog("Invalid index");
        return false;
    }

    if(preBlock->getHash() != preHash)
    {
        dialog->AppendLog("Invalid previoushash");
        return false;
    }

    string newHash = calculateHash(index, preHash, timeStamp, data);

    if(newHash != hash)
    {
        dialog->AppendLog(string("Invalid hash: ") + newHash + " " + hash);
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

        if(!isValidBlock(cur->getIndex(), cur->getPreHash(), cur->getTimeStamp(), cur->getData(), cur->getHash(), pre))
            return false;

        cur = pre;
    }

    return true;
}

void blockChain::replaceChain(blockChain * const newChain)
{
    dialog* dialog = factory::GetDialog();

    if(!isValidChain(newChain) || newChain->length() <= len)
    {
        dialog->AppendLog("Received blockchain invalid, not replaced.");
        return;
    }

    dialog->AppendLog("Received blockchain is valid. Replacing current blockchain with received blockchain.");

    removeAll();

    block* cur = newChain->getLatestBlock();

    while(cur)
    {
        block *pre = newChain->getBlock(cur->getPreHash());
        hashList[cur->getHash()] = new block(cur);
        tail = !tail ? hashList[cur->getHash()] : tail;
        head = hashList[cur->getHash()];
        cur = pre;
    }

    len = newChain->length();
}

string blockChain::getChainInfo()
{
    string res;
    block* cur = getLatestBlock();
    
    while(cur)
    {
        if(!res.empty())
            res += ",";

        res += cur->getBlockInfo();
        cur = getBlock(cur->getPreHash());
    }

    return res;
}

blockChain* blockChain::generateChain(const string& chainInfo)
{
    string info = chainInfo;
    size_t found = info.find(",");
    int index;
    string preHash, data, hash;
    time_t timeStamp;
    stack<block*> s;

    factory::GetDialog()->AppendLog(string("generateChain ") + chainInfo);

    while(found != string::npos)
    {
        block::TransferInfo(info.substr(0, found), index, preHash, timeStamp, data, hash);
        s.push(new block(index, preHash, timeStamp, data, hash));
        info = info.substr(found + 1);
        found = info.find(",");
    }

    block::TransferInfo(info, index, preHash, timeStamp, data, hash);
    s.push(new block(index, preHash, timeStamp, data, hash));
    
    blockChain* newChain = new blockChain();

    while(!s.empty())
    {
        newChain->addBlock(s.top());
        s.pop();
    }

    return newChain;
}

blockChain::~blockChain()
{
    removeAll();
}

void blockChain::removeAll()
{
    block *cur = getLatestBlock();
    
    while(cur)
    {
        block *pre = hashList[cur->getPreHash()];
        delete cur;
        cur = pre;
    }
    
    hashList.clear();
    len = 0;
    tail = NULL;
}

