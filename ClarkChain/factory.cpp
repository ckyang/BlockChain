//
//  factory.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/17/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <stdio.h>
#include "factory.h"
#include "blockChain.h"
#include "talk.h"

blockChain* factory::m_blockChain = NULL;
talk* factory::m_talk = NULL;

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
}
