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
#include <unordered_map>

using namespace std;

class block;

class blockChain
{
public:
    blockChain();

    block* generateNextBlock(const string& data);
    void addBlock(block *newBlock);
    unsigned long long length(){return len;}
    block *getLatestBlock(){return tail;}
    block *getBlock(const string& hash){return hashList[hash];}
    void replaceChain(blockChain * const chain);

    static bool isValidChain(blockChain * const chain);

private:
    block *getGenesisBlock();

    static string calculateHash(const int index, const string& preHash, const time_t& timeStamp, const string& data);
    static bool isValidBlock(block *newBlock, block *preBlock);

    block *head;
    block *tail;
    unordered_map<string, block*> hashList;
    unsigned long long len;
};

#endif /* blockChain_h */
