//
//  talk.h
//  BlockChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef talk_h
#define talk_h

#include <string>

#define REMOTE_COMMAND_NEW "NEW"
#define REMOTE_COMMAND_GET_LAST "GET LAST"
#define REMOTE_COMMAND_GET_ALL "GET ALL"
#define REMOTE_COMMAND_REPLY_LAST "REPLY LAST"
#define REMOTE_COMMAND_REPLY_ALL "REPLY ALL"

using namespace std;

class blockChain;
class block;

class talk
{
public:
    talk(){};

    static void Broadcast(block* const bk);
    static void Broadcast(const string& message);

    void connect();

private:
    static void Response(int sock_fd, short event, void *arg);
    static bool StartWith(const string& str, const string& start);
    static void SendMsg(const int sock_fd, const struct sockaddr_in* sock_in, const string& rawMessage);
    static string RcvMsg(const int sock_fd, struct sockaddr_in* client_addr);
};

#endif /* talk_h */
