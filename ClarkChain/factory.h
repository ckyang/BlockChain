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
class crypto;

class factory
{
public:
    static blockChain* GetBlockChain();
    static talk* GetTalk();
    static crypto* GetCrypto();
    ~factory();

private:
    static blockChain* m_blockChain;
    static talk* m_talk;
    static crypto* m_crypto;
};

#endif /* factory_h */
