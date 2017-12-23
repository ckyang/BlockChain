//
//  factory.cpp
//  BlockChain
//
//  Created by Chung-kaiYang on 12/17/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <stdio.h>
#include "factory.h"
#include "blockChain.h"
#include "talk.h"
#include "crypto.h"

blockChain* factory::m_blockChain = NULL;
talk* factory::m_talk = NULL;
crypto* factory::m_crypto = NULL;

blockChain* factory::GetBlockChain()
{
    if(!m_blockChain)
        m_blockChain = new blockChain(true);

    return m_blockChain;
}

talk* factory::GetTalk()
{
    if(!m_talk)
        m_talk = new talk();
    
    return m_talk;
}

crypto* factory::GetCrypto()
{
    if(!m_crypto)
        m_crypto = new crypto();
    
    return m_crypto;
}

factory::~factory(void)
{
    if(m_blockChain)
    {
        delete m_blockChain;
        m_blockChain = NULL;
    }

    if(m_talk)
    {
        delete m_talk;
        m_talk = NULL;
    }

    if(m_crypto)
    {
        delete m_crypto;
        m_crypto = NULL;
    }
}
