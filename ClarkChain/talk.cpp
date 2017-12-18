//
//  talk.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <iostream>
#include "talk.h"
#include "unistd.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "event.h"
#include "factory.h"
#include "blockChain.h"
#include "block.h"

using namespace std;

#define REMOTE_COMMAND_NEW "NEW"
#define REMOTE_COMMAND_GET_LAST "GET LAST"
#define REMOTE_COMMAND_GET_ALL "GET ALL"
#define REMOTE_COMMAND_REPLY_LAST "REPLY LAST"
#define REMOTE_COMMAND_REPLY_ALL "REPLY ALL"

static void response(int fd, short event, void *arg)
{
    char rbuf[1500] = {'\0'};
    read(fd,rbuf,1500);
    string readBuf(rbuf), writeBuf;
    readBuf = readBuf.substr(0, readBuf.size() - 2);
//    cout << "Received message : " << readBuf.size() << "=" << readBuf << "..." << endl;
    
    if(readBuf.size() < 7)
    {
        writeBuf = "Invalid command!";
        write(fd, writeBuf.c_str(), writeBuf.size());
        shutdown(fd, SHUT_RDWR);
        free(arg);
        return;
    }

    blockChain* blockChainObject = factory::GetBlockChain();

    //NEW blockInfo
    if(readBuf.substr(0, 3) == REMOTE_COMMAND_NEW)
    {
        int index;
        string preHash, data, hash;
        time_t timeStamp;
        block::TransferInfo(readBuf.substr(4), index, preHash, timeStamp, data, hash);

        //If this block is already the top of blockchain, do nothing
        if(blockChainObject->getLatestBlock()->getIndex() != index || blockChainObject->getLatestBlock()->getPreHash() != preHash || blockChainObject->getLatestBlock()->getTimeStamp() != timeStamp || blockChainObject->getLatestBlock()->getData() != data || blockChainObject->getLatestBlock()->getHash() != hash)
        {
            //If this block (coming from remote) is valid, just add into currnet blockchain.
            //If it's invalid, ignore this block and request other node's blockchain
            if(blockChain::isValidBlock(index, preHash, timeStamp, data, hash, blockChainObject->getLatestBlock()))
                blockChainObject->addBlock(new block(index, preHash, timeStamp, data, hash));
            else
                writeBuf = REMOTE_COMMAND_GET_ALL;
        }
        else
            cout << "This block already in the top of blockchain, do nothing." << endl;
    }
    //GET LAST
    else if(readBuf == REMOTE_COMMAND_GET_LAST)
        writeBuf = string(REMOTE_COMMAND_REPLY_LAST) + " " + blockChainObject->getLatestBlock()->getBlockInfo();
    //GET ALL
    else if(readBuf == REMOTE_COMMAND_GET_ALL)
        writeBuf = string(REMOTE_COMMAND_REPLY_ALL) + " " + blockChainObject->getChainInfo();
    //REPLY LAST ...
    else if(readBuf.substr(0, 10) == REMOTE_COMMAND_REPLY_LAST)
    {
        //TBD

    }
    //REPLY ALL ...
    else if(readBuf.substr(0, 9) == REMOTE_COMMAND_REPLY_ALL)
    {
        blockChain* newChain = blockChain::generateChain(readBuf.substr(10));

        //If other node's blockchain is longer than current, use this one
        if(newChain->length() > blockChainObject->length())
            blockChainObject->replaceChain(newChain);

        delete newChain;
    }

    write(fd, writeBuf.c_str(), writeBuf.size());
    shutdown(fd, SHUT_RDWR);
    free(arg);
}

static void connection_accept(int fd, short event, void *arg)
{
    struct sockaddr_in s_in;
    socklen_t len = sizeof(s_in);
    int ns = accept(fd, (struct sockaddr *) &s_in, &len);

    if(ns < 0)
    {
        perror("accept");
        return;
    }

    struct event *ev = (struct event*)malloc(sizeof(struct event));
    event_set(ev, ns, EV_WRITE, response, ev);
    event_add(ev, NULL);
}

void talk::connect(int port)
{
    /* Request socket. */
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
        exit(1);
    }

    /* bind() */
    struct sockaddr_in s_in;
    bzero(&s_in, sizeof(s_in));
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(port);
    s_in.sin_addr.s_addr = INADDR_ANY;
    if (::bind(s, (struct sockaddr *) &s_in, sizeof(s_in)) < 0) {
        perror("bind");
        exit(1);
    }
    
    /* listen() */
    if (listen(s, 5) < 0) {
        perror("listen");
        exit(1);
    }
    
    /* Initial libevent. */
    event_init();
    
    /* Create event. */
    struct event ev;
    event_set(&ev, s, EV_READ | EV_PERSIST, connection_accept, &ev);

    /* Add event. */
    event_add(&ev, NULL);

    event_dispatch();
    close(s);
}

void talk::broadcast(block* const bk)
{
    //TBD
    string message = string("NEW ") + bk->getBlockInfo();
    cout << "Broadcast " << message << endl;
}
