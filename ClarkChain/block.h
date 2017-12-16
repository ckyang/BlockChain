//
//  block.h
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef block_h
#define block_h

#include <string>

using namespace std;

class block
{
public:
    block(block * const b);
    block(const int index, const string& preHash, const time_t& timeStamp, const string& data, const string& hash);
    int getIndex() {return m_index;}
    string getPreHash() {return m_preHash;}
    time_t getTimeStamp() {return m_timeStamp;}
    string getData() {return m_data;}
    string getHash() {return m_hash;}
    
private:
    int m_index;
    string m_preHash;
    time_t m_timeStamp;
    string m_data;
    string m_hash;
};

#endif /* block_h */
