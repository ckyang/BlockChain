//
//  block.h
//  BlockChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef block_h
#define block_h

#include <string>
#include "time.h"

using namespace std;

class block
{
public:
    block(block * const b);
    block(const int index, const string& preHash, const time_t& timeStamp, const string& data, const string& hash);

    static void TransferInfo(const string& totalInfo, int& index, string& preHash, time_t& timeStamp, string& data, string& hash);

    int getIndex() {return m_index;}
    string getPreHash() {return m_preHash;}
    time_t getTimeStamp() {return m_timeStamp;}
    string getData() {return m_data;}
    string getHash() {return m_hash;}
    string getBlockInfo(bool bTransferHuman = false){return to_string(m_index) + " " + (bTransferHuman ? "" : (m_preHash + " ")) + (bTransferHuman ? (to_string(gmtime(&m_timeStamp)->tm_year + 1900) + "/" + to_string(gmtime(&m_timeStamp)->tm_mon + 1) + "/" + to_string(gmtime(&m_timeStamp)->tm_mday) + "," + to_string(gmtime(&m_timeStamp)->tm_hour) + ":" + to_string(gmtime(&m_timeStamp)->tm_min) + ":" + to_string(gmtime(&m_timeStamp)->tm_sec)) : to_string(m_timeStamp)) + " " + m_data + " " + m_hash;}

private:
    int m_index;
    string m_preHash;
    time_t m_timeStamp;
    string m_data;
    string m_hash;
};

#endif /* block_h */
