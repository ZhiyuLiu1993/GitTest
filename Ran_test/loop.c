//
// Created by root on 12/3/17.
//

#include "open.h"
#include <sys/epoll.h>

void loop(void)
{
    int i, listenfd, clifd, nread, epfd, nfds;
    char buf[MAXLINE];
    uid_t uid;
    struct epoll_event ev, events[20];
    epfd = epoll_create(256);
    if(listenfd = serv_listen(CS_OPEN) < 0)
    {
        printf("serv_listen error!\n");
    }
    ev.data.fd = listenfd;
    ev.events = EPOLLET | EPOLLIN;

    client_add(listenfd, 0);
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

    for(;;)
    {
        nfds = epoll_wait(epfd, events, 20, -1);

        for (i = 0; i < nfds; ++i) {
            if(events[i].data.fd == listenfd)
            {
                if((clifd = serv_accept(listenfd, &uid)) < 0)
                {
                    printf("serv_accept error:%d\n", clifd);
                }
                client_add(clifd, uid);
                //j is useless
                ev.data.fd = clifd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clifd, &ev);
                printf("new connection : uid %d, fd %d\n", uid, clifd);
                continue;
            }
            //need foreach array, use maxi, ctl_del ev need event type

            if(events[i].events & EPOLLIN)
            {
                clifd = events[i].data.fd;
                if((nread = read(clifd, buf, MAXLINE)) < 0)
                {
                    printf("read error on fd %d\n", clifd);
                }
                else if(nread == 0)
                {
                    printf("closed: uid %d, fd %d\n", client[i].uid, clifd);
                    client_del(clifd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, clifd, &ev);
                    close(clifd);
                }
                else
                {
                    handle_request(buf, nread, clifd, client[i].uid);
                }
            }
        }
    }
}

