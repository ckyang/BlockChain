//
//  talk.h
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef talk_h
#define talk_h

using namespace std;

class blockChain;
class block;

class talk
{
public:
    talk(){};
    void connect(int port);
    void broadcast(block* const bk);
};

#endif /* talk_h */
