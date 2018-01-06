//
//  talk.cpp
//  BlockChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include "talk.h"
#include "unistd.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "event.h"
#include "factory.h"
#include "blockChain.h"
#include "block.h"
#include "dialog.h"

#define DEBUG_MODE 0

#if DEBUG_MODE
#define SENDER_PORT 7000
#define RECEIVER_PORT 7001
#else
#define SENDER_PORT 7000
#define RECEIVER_PORT 7000
#endif

#define MAX_BUF_SIZE 65535
#define BLOCKCHAIN_HEADER "__ThisIsBlockChainPacketByClarkYang__"

using namespace std;

void talk::Response(int sock_fd, short event, void *arg)
{
    (void)event;
    (void)arg;

    static string g_localIP;
    struct sockaddr_in client_addr;
    dialog* dialog = factory::GetDialog();
    string readBuf = RcvMsg(sock_fd, &client_addr);

    if(readBuf.empty())
    {
        dialog->appendLog("Connection Closed");
        return;
    }

    dialog->appendLog(QString("Received packet from ").append(inet_ntoa(client_addr.sin_addr)).append(" : ").append(to_string(ntohs(client_addr.sin_port)).c_str()));
    dialog->appendLog(QString("Received: ").append(readBuf.c_str()));

    if(g_localIP.empty() || g_localIP == inet_ntoa(client_addr.sin_addr))
    {
        if(g_localIP.empty())
        {
            g_localIP = inet_ntoa(client_addr.sin_addr);
            dialog->appendLog(QString("Local IP : ").append(g_localIP.c_str()));
        }

        dialog->appendLog("Received packet is from myself, ignore it.");
        return;
    }

    string writeBuf;
    client_addr.sin_port = htons(SENDER_PORT);

    if(readBuf.size() < 7)
    {
        writeBuf = "Invalid command!";
        SendMsg(sock_fd, &client_addr, writeBuf);
        return;
    }

    blockChain* blockChainObject = factory::GetBlockChain();

    //NEW blockInfo
    if(StartWith(readBuf, REMOTE_COMMAND_NEW))
    {
        int index;
        string preHash, data, hash;
        time_t timeStamp;
        block::TransferInfo(readBuf.substr(4), index, preHash, timeStamp, data, hash);

        //If this block is already the top of blockchain, do nothing
        if(blockChainObject->getLatestBlock()->getIndex() == index && blockChainObject->getLatestBlock()->getPreHash() == preHash && blockChainObject->getLatestBlock()->getTimeStamp() == timeStamp && blockChainObject->getLatestBlock()->getData() == data && blockChainObject->getLatestBlock()->getHash() == hash)
        {
            dialog->appendLog("This block already in the top of blockchain, do nothing.");
            return;
        }

        //If this block (coming from remote) is valid, just add into currnet blockchain.
        //If it's invalid, ignore this block and request other node's blockchain
        if(blockChain::IsValidBlock(index, preHash, timeStamp, data, hash, blockChainObject->getLatestBlock()))
        {
            blockChainObject->addBlock(new block(index, preHash, timeStamp, data, hash));
            factory::GetDialog()->updateBlockChainList();
            return;
        }

        writeBuf = REMOTE_COMMAND_GET_ALL;
        SendMsg(sock_fd, &client_addr, writeBuf);
        return;
    }

    //GET LAST
    if(StartWith(readBuf, REMOTE_COMMAND_GET_LAST))
    {
        writeBuf = string(REMOTE_COMMAND_REPLY_LAST) + " " + blockChainObject->getLatestBlock()->getBlockInfo();

        SendMsg(sock_fd, &client_addr, writeBuf);
        return;
    }

    //GET ALL
    if(StartWith(readBuf, REMOTE_COMMAND_GET_ALL))
    {
        writeBuf = string(REMOTE_COMMAND_REPLY_ALL) + " " + blockChainObject->getChainInfo();
        SendMsg(sock_fd, &client_addr, writeBuf);
        return;
    }

    //REPLY LAST ...
    if(StartWith(readBuf, REMOTE_COMMAND_REPLY_LAST))
    {
        //TBD

        return;
    }

    //REPLY ALL ...
    if(StartWith(readBuf, REMOTE_COMMAND_REPLY_ALL))
    {
        blockChain* newChain = blockChain::GenerateChain(readBuf.substr(10));

        //If other node's blockchain is longer than current, use this one
        if(newChain->length() > blockChainObject->length())
        {
            blockChainObject->replaceChain(newChain);
            factory::GetDialog()->updateBlockChainList();
        }

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
    event_set(&ev, sock_fd, EV_READ | EV_PERSIST, Response, &ev);

    event_add(&ev, NULL);

    event_dispatch();
    shutdown(sock_fd, 2);
    close(sock_fd);
}

void talk::Broadcast(block* const bk)
{
    Broadcast(string("NEW ") + bk->getBlockInfo());
}

void talk::Broadcast(const string& message)
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

    SendMsg(sock_fd, &sock_in, message);

    factory::GetDialog()->appendLog(QString("Message is broadcasted."));
//    factory::GetDialog()->appendLog(message.c_str());

    shutdown(sock_fd, 2);
    close(sock_fd);
}

bool talk::StartWith(const string& str, const string& start)
{
    if(str.size() < start.size())
        return false;
    
    return str.substr(0, start.size()) == start;
}

void talk::SendMsg(const int sock_fd, const struct sockaddr_in* sock_in, const string& rawMessage)
{
    if(rawMessage.empty())
        return;

    string message = string(BLOCKCHAIN_HEADER) + rawMessage;

    sendto(sock_fd, message.c_str(), message.size() + 1, 0, (struct sockaddr *)sock_in, sizeof(struct sockaddr_in));
}

string talk::RcvMsg(const int sock_fd, struct sockaddr_in* client_addr)
{
    static char rbuf[MAX_BUF_SIZE];
    int size = sizeof(struct sockaddr);
    memset(rbuf, '\0', MAX_BUF_SIZE);

    if(recvfrom(sock_fd, rbuf, (size_t)sizeof(rbuf), 0, (struct sockaddr *)client_addr, (socklen_t *)&size) < 0)
        return "";

    string res(rbuf);

    if(!StartWith(res, BLOCKCHAIN_HEADER))
        return "";

    res = res.substr(strlen(BLOCKCHAIN_HEADER));

    if('\n' == res[res.size() - 1])
        res = res.substr(0, res.size() - 1);

    return res;
}

