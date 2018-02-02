#include "mylog.h"
#include <unistd.h>


void *log_print(void *arg){
    for (int i = 0; i < MAX_LEN; ++i) {
        LOG_ERROR("thread:%d,%d.\n", (int)arg, i);
        usleep(100);
    }
}


int main() {
    init();

//        char filename[50];
//        snprintf(filename, 50, "log.txt");
    FILE *pfp;

    pthread_t thread;
    pthread_t thread2;
    pthread_create(&thread, NULL, log_print, (void *)1);
    pthread_create(&thread2, NULL, log_print, (void *)2);

    int line;
    int buffer_num, next_num;
    int exit = 0;
    Log_Info *log_info = (Log_Info *)shared_buffer;

    struct timespec abstime;
    abstime.tv_nsec = 0;

    while(!exit){

        pthread_mutex_lock(&log_info->mutex_);
        while(!log_info->write_t){   //防止虚假唤醒
            abstime.tv_sec = time(NULL) + 10; //设置超时时间为10s
            pthread_cond_timedwait(&log_info->cond_, &log_info->mutex_, &abstime);
//            if(!log_info->write_t){
//                pfp = fopen("./log.txt", "w+");
//                line = log_info->cur_line;
//                next_num = log_info->cur_buf;
//                log_info->cur_line = 0;
//                log_info->cur_buf = (log_info->cur_buf + 1) % 3;
//                pthread_mutex_unlock(&log_info->mutex_);
//                char *write_buf = log_info->payload + next_num*MAX_LEN*MAX_LOG_LEN;
//                for (int i = 0; i < line; ++i) {
//                    if(fprintf(pfp, write_buf) < 0){
//                        fclose(pfp);
//                        exit = 1;
//                        break;
//                    }
//                    write_buf += MAX_LOG_LEN;
//                }
//                pthread_mutex_lock(&log_info->mutex_);
//            }
        }
        line = log_info->cur_line;
        buffer_num = log_info->write_t;
        next_num = log_info->cur_buf;
        log_info->write_t = 0;
        log_info->cur_line = 0;
//        for (int j = 0; j < BUF_NUM; ++j) {
//           if(log_info->write_num[j] == 0)
//               log_info->cur_buf = j;
//        }
//        log_info->write_t = 0;
//        log_info->cur_buf = log_info->cur_buf ? 0 : 1;
//        memset(log_info->payload+log_info->cur_buf*MAX_LEN*MAX_LOG_LEN, 0, MAX_LEN*MAX_LOG_LEN);
        pthread_mutex_unlock(&log_info->mutex_);

        pfp = fopen("./log.txt", "w+");
//        printf("line:%d.\n", line);
//        for (int i = 0; i < line; ++i) {
//        if(fwrite(write_buf, MAX_LOG_LEN, line, pfp) < line){
//            fclose(pfp);
//            break;
//        }
        for (int k = 1; k <= buffer_num; ++k) {
//            pthread_mutex_lock(&log_info->mutex_);
//            if(log_info->write_num[k] == 0){
//                pthread_mutex_unlock(&log_info->mutex_);
//                continue;
//            }
//            log_info->write_num[k] = 0;
            int temp_num = (next_num - k + BUF_NUM) % BUF_NUM;
            pthread_mutex_unlock(&log_info->mutex_);
            char *write_buf = log_info->payload + temp_num*MAX_LEN*MAX_LOG_LEN;
            if(k == buffer_num && buffer_num > 1)
                line = MAX_LOG_LEN;
            for (int i = 0; i < line; ++i) {
                if(fprintf(pfp, write_buf) < 0){
                    fclose(pfp);
                    exit = 1;
                    break;
                }
                write_buf += MAX_LOG_LEN;
            }
        }
//        fclose(pfp);
//        pfp = fopen("./log.txt", "r");
//        char read_buf[200];
//        fread(read_buf, 1, 200, pfp);
//        printf("read_buf:%s\n", read_buf);
//            write_buf += MAX_LOG_LEN;
//        }
//        write_buf = log_info->payload + buffer*MAX_LEN*MAX_LOG_LEN;
//        char print_buf[200];
//        for (int i = 0; i < line; ++i) {
//            snprintf(print_buf, 200, )
//            memset(print_buf, 0, 200);
//            strncat(print_buf, write_buf, 200);
//            printf("%s.\n", print_buf);
//            write_buf += MAX_LOG_LEN;
//        }
    }


    return 0;
}

//还可以使用unix域套接字、管道的方法替换
//不使用fwrite,fwrite会将无关字符写入，不能进行格式化输入。  在外部编译需要su权限。