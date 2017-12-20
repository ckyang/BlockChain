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

#define REMOTE_COMMAND_NEW "NEW"
#define REMOTE_COMMAND_GET_LAST "GET LAST"
#define REMOTE_COMMAND_GET_ALL "GET ALL"
#define REMOTE_COMMAND_REPLY_LAST "REPLY LAST"
#define REMOTE_COMMAND_REPLY_ALL "REPLY ALL"

#define DEBUG_MODE 0

#if DEBUG_MODE
#define SENDER_PORT 7000
#define RECEIVER_PORT 7001
#else
#define SENDER_PORT 7000
#define RECEIVER_PORT 7000
#endif

#define MAX_BUF_SIZE 1500

using namespace std;

static bool startWith(const string& str, const string& start)
{
    if(str.size() < start.size())
        return false;

    return str.substr(0, start.size()) == start;
}

static void response(int sock_fd, short event, void *arg)
{
    char rbuf[MAX_BUF_SIZE];
    int size = sizeof(struct sockaddr);
    struct sockaddr_in client_addr;

    memset(rbuf, '\0', MAX_BUF_SIZE);
    
    if(recvfrom(sock_fd, rbuf, (size_t)sizeof(rbuf), 0, (struct sockaddr *)&client_addr, (socklen_t *)&size) < 0)
    {
        cout << "Connection Closed" << endl;
        return;
    }

    string readBuf(rbuf), writeBuf;

    if('\n' == readBuf[readBuf.size() - 1])
        readBuf = readBuf.substr(0, readBuf.size() - 1);

//    cout << "receive " << readBuf.size() << "," << readBuf << endl;

    if(readBuf.size() < 7)
    {
        writeBuf = "Invalid command!!!!!!!!!!!!!!!!!";
        sendto(sock_fd, writeBuf.c_str(), writeBuf.size(), 0, (struct sockaddr *)&client_addr, size);
        return;
    }

    blockChain* blockChainObject = factory::GetBlockChain();

    //NEW blockInfo
    if(startWith(readBuf, REMOTE_COMMAND_NEW))
    {
        int index;
        string preHash, data, hash;
        time_t timeStamp;
        block::TransferInfo(readBuf.substr(4), index, preHash, timeStamp, data, hash);

        //If this block is already the top of blockchain, do nothing
        if(blockChainObject->getLatestBlock()->getIndex() == index && blockChainObject->getLatestBlock()->getPreHash() == preHash && blockChainObject->getLatestBlock()->getTimeStamp() == timeStamp && blockChainObject->getLatestBlock()->getData() == data && blockChainObject->getLatestBlock()->getHash() == hash)
        {
//            cout << "This block already in the top of blockchain, do nothing." << endl;
            return;
        }

        //If this block (coming from remote) is valid, just add into currnet blockchain.
        //If it's invalid, ignore this block and request other node's blockchain
        if(blockChain::isValidBlock(index, preHash, timeStamp, data, hash, blockChainObject->getLatestBlock()))
        {
            blockChainObject->addBlock(new block(index, preHash, timeStamp, data, hash));
            return;
        }

        writeBuf = REMOTE_COMMAND_GET_ALL;
        sendto(sock_fd, writeBuf.c_str(), writeBuf.size(), 0, (struct sockaddr *)&client_addr, size);
        return;
    }

    //GET LAST
    if(startWith(readBuf, REMOTE_COMMAND_GET_LAST))
    {
        writeBuf = string(REMOTE_COMMAND_REPLY_LAST) + " " + blockChainObject->getLatestBlock()->getBlockInfo();

        sendto(sock_fd, writeBuf.c_str(), writeBuf.size(), 0, (struct sockaddr *)&client_addr, size);
        return;
    }

    //GET ALL
    if(startWith(readBuf, REMOTE_COMMAND_GET_ALL))
    {
        writeBuf = string(REMOTE_COMMAND_REPLY_ALL) + " " + blockChainObject->getChainInfo();

        sendto(sock_fd, writeBuf.c_str(), writeBuf.size(), 0, (struct sockaddr *)&client_addr, size);
        return;
    }

    //REPLY LAST ...
    if(startWith(readBuf, REMOTE_COMMAND_REPLY_LAST))
    {
        //TBD

        return;
    }

    //REPLY ALL ...
    if(startWith(readBuf, REMOTE_COMMAND_REPLY_ALL))
    {
        blockChain* newChain = blockChain::generateChain(readBuf.substr(10));

        //If other node's blockchain is longer than current, use this one
        if(newChain->length() > blockChainObject->length())
            blockChainObject->replaceChain(newChain);

        delete newChain;
        return;
    }
}

void talk::connect()
{
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        exit(1);
    }

    int yes = 1;

    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
        perror("setsockopt()");
        exit(1);
    }

    struct sockaddr_in sock_in;
    bzero(&sock_in, sizeof(sock_in));
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(RECEIVER_PORT);
    sock_in.sin_addr.s_addr = INADDR_ANY;
    if (::bind(sock_fd, (struct sockaddr *) &sock_in, sizeof(sock_in)) < 0) {
        perror("bind");
        exit(1);
    }

    event_init();

    struct event ev;
    event_set(&ev, sock_fd, EV_READ | EV_PERSIST, response, &ev);

    event_add(&ev, NULL);

    event_dispatch();
    shutdown(sock_fd, 2);
    close(sock_fd);
}

void talk::broadcast(block* const bk)
{
    int sock_fd;
    struct sockaddr_in sock_in;
    int yes = 1;

    memset(&sock_in, 0, sizeof(struct sockaddr_in));

    sock_fd = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
    sock_in.sin_port = htons(0);
    sock_in.sin_family = PF_INET;

    if (::bind(sock_fd, (struct sockaddr *) &sock_in, sizeof(struct sockaddr_in)) < 0) {
        perror("bind");
        exit(1);
    }

    setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));

    sock_in.sin_addr.s_addr = htonl(-1); /* send message to 255.255.255.255 */
    sock_in.sin_port = htons(SENDER_PORT);
    sock_in.sin_family = PF_INET;

    string message = string("NEW ") + bk->getBlockInfo();

    sendto(sock_fd, message.c_str(), message.size() + 1, 0, (struct sockaddr *)&sock_in, sizeof(struct sockaddr_in));

    shutdown(sock_fd, 2);
    close(sock_fd);
}

