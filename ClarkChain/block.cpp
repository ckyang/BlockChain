//
//  block.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include "block.h"

block::block(block* const b)
{
    m_index = b->getIndex();
    m_preHash = b->getPreHash();
    m_timeStamp = b->getTimeStamp();
    m_data = b->getData();
    m_hash = b->getHash();
}

block::block(const int index, const string& preHash, const time_t& timeStamp, const string& data, const string& hash)
{
    m_index = index;
    m_preHash = preHash;
    m_timeStamp = timeStamp;
    m_data = data;
    m_hash = hash;
}

block::block(const string& totalInfo)
{
    
}
