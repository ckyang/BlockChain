//
//  blockChain.h
//  BlockChain
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
    blockChain(bool bGenerateGenesis = false);

    static bool isValidChain(blockChain * const chain);
    static bool isValidBlock(const int index, const string& preHash, const time_t& timeStamp, const string& data, const string& hash, block *preBlock);
    static blockChain* generateChain(const string& chainInfo);

    block* generateNextBlock(const string& data);
    void addBlock(block *newBlock);
    unsigned long long length(){return len;}
    block *getLatestBlock(){return tail;}
    block *getBlock(const string& hash){return hashList[hash];}
    void replaceChain(blockChain * const chain);
    string getChainInfo();
    ~blockChain();

private:
    static string calculateHash(const int index, const string& preHash, const time_t& timeStamp, const string& data);

    block *getGenesisBlock();
    void removeAll();

    block *head;
    block *tail;
    unordered_map<string, block*> hashList;
    unsigned long long len;
};

#endif /* blockChain_h */
