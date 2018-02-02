//
// Created by root on 1/31/18.
//

#ifndef MYLOG_H
#define MYLOG_H

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

struct LOG_INFO_;

#define MAX_LOG_LEN 256
#define MAX_LEN 5000
#define BUF_NUM 4        //todo:此处可扩展
#define HEADER_LEN sizeof(struct LOG_INFO_)

typedef  struct LOG_INFO_{
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
//    pthread_mutex_t cond_mutex_;
    int cur_line;    //当前buf的行号
    short cur_buf;     //当前buf的编号
    short write_t;     //当前待写buf数
//    char write_num[BUF_NUM];       //当前待写buf编号 1表示待写，0则为空
    char payload[0];
} Log_Info;

time_t cur_time;
char str[50];
char tmp[MAX_LOG_LEN];
char shared_buffer[MAX_LEN*MAX_LOG_LEN*BUF_NUM + HEADER_LEN];
Log_Info *log_info = (Log_Info *)shared_buffer;


void init(){
    log_info->cur_line = 0;
    log_info->cur_buf = 0;
    log_info->write_t = 0;
    pthread_mutexattr_t mattr;
    pthread_mutexattr_init(&mattr);
    pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&log_info->mutex_, &mattr);
//    pthread_mutex_init(&log_info->cond_mutex_, &mattr);
    pthread_mutexattr_destroy(&mattr);

    pthread_condattr_t cattr;
    pthread_condattr_init(&cattr);
    pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&log_info->cond_, &cattr);
    pthread_condattr_destroy(&cattr);

//    memset(log_info->payload, 0, MAX_LEN*MAX_LOG_LEN*2);
}

//struct tm 的空间由内核自动分配，不要释放
#define LOG_ERROR(fmt...)  \
        do{\
            pthread_mutex_lock(&log_info->mutex_);\
            cur_time = time(NULL);\
            struct tm *ptr = localtime(&cur_time);\
            strftime(str, 50, "%F %T", ptr);\
            snprintf(log_info->payload+log_info->cur_buf*MAX_LEN*MAX_LOG_LEN+log_info->cur_line*MAX_LOG_LEN,\
            MAX_LOG_LEN,\
            "[%s]-[%s %s]-[line %d]:", str, __FILE__, __FUNCTION__, __LINE__);\
            snprintf(tmp, MAX_LOG_LEN, fmt);\
            strcat(log_info->payload+log_info->cur_buf*MAX_LEN*MAX_LOG_LEN+log_info->cur_line*MAX_LOG_LEN, tmp);\
            if(++log_info->cur_line > 4999){\
                ++log_info->write_t;\
                log_info->cur_buf = (log_info->cur_buf + 1) % 3;\
                pthread_cond_signal(&log_info->cond_);\
            }\
            pthread_mutex_unlock(&log_info->mutex_);\
        }while(0)

#endif //MYLOG_H
