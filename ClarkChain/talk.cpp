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

using namespace std;

static void connection_time(int fd, short event, void *arg)
{
    char buf[32];
    struct tm t;
    time_t now;

    char rbuf[1500];
    read(fd,rbuf,1500);
    cout << "Received message : "<< rbuf << endl;

    time(&now);
    localtime_r(&now, &t);
    asctime_r(&t, buf);
    
    write(fd, buf, strlen(buf));
    shutdown(fd, SHUT_RDWR);
    
    free(arg);
}

static void connection_accept(int fd, short event, void *arg)
{
    /* for debugging */
    fprintf(stderr, "%s(): fd = %d, event = %d.\n", __func__, fd, event);

    struct sockaddr_in s_in;
    socklen_t len = sizeof(s_in);
    int ns = accept(fd, (struct sockaddr *) &s_in, &len);

    if(ns < 0)
    {
        perror("accept");
        return;
    }

    struct event *ev = (struct event*)malloc(sizeof(struct event));
    event_set(ev, ns, EV_WRITE, connection_time, ev);
    event_add(ev, NULL);
}

void talk::connect()
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
    s_in.sin_port = htons(7000);
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
    cout << "event_dispatch" << endl;
}

