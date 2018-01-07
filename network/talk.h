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
#define REMOTE_COMMAND_GET_LAST "GET_LAST"
#define REMOTE_COMMAND_GET_ALL "GET_ALL"
#define REMOTE_COMMAND_REPLY_LAST "REPLY_LAST"
#define REMOTE_COMMAND_REPLY_ALL "REPLY_ALL"

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
    static bool StartWith(const char* str, int len, const char* start_str);

    //Message Format: [BLOCKCHAIN_HEADER][MessageLen][Message][Signature]
    //BLOCKCHAIN_HEADER : strlen(BLOCKCHAIN_HEADER)
    //MessageLen : 4 (0000 ~ FFFF)
    //Message : MessageLen
    //Signature : Remained characters

    static void SendMsg(const int sock_fd, const struct sockaddr_in* sock_in, const string& msg);
    static void SendMsg(const int sock_fd, const struct sockaddr_in* sock_in, const char* msg, const int len);
    static bool RcvMsg(const int sock_fd, struct sockaddr_in* client_addr, char* msg, int& len);
    static void itoHex(int number, char hex[]);
    static void hextoI(int& number, const char hex[]);
};

#endif /* talk_h */
