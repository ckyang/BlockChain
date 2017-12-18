//
//  factory.h
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/17/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef factory_h
#define factory_h

class blockChain;
class talk;

class factory
{
public:
    static blockChain* GetBlockChain();
    static talk* GetTalk();
    ~factory();

private:
    static blockChain* m_blockChain;
    static talk* m_talk;
};

#endif /* factory_h */
