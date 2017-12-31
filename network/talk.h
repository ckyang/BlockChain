//
//  talk.h
//  BlockChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef talk_h
#define talk_h

class blockChain;
class block;

class talk
{
public:
    talk(){};

    static void Broadcast(block* const bk);

    void connect();
};

#endif /* talk_h */
