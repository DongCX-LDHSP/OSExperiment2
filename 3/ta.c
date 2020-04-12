#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h> // 包含消息队列相关函数及数据结构的头文件

struct my_msg_st {
    long int my_msg_type;
    char some_text[BUFSIZ];
};// 消息格式

int main()
{
    int running = 1;
    int msgid;
    struct my_msg_st some_data;
    long int msg_to_receive = 0;
    
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);// 创建标识符为key = 1234 的消息队列，注意发送端与接收端该值的一致性
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }// 错误处理：msgget调用成功返回消息队列标识符，调用失败返回-1
    
    while(running) {
        if (msgrcv(msgid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) { // 从消息队列接收消息，如果接收失败执行if语句并退出
                fprintf(stderr, "msgrcv failed with error: %d\n", errno);
                exit(EXIT_FAILURE);
        }
        printf("You wrote: %s", some_data.some_text);
        if (strncmp(some_data.some_text, "end", 3) == 0) { // 如果接收到文本含有"end"，将running设置为0，效果是：退出while循环
            running = 0;
        }
    }
    
    if (msgctl(msgid, IPC_RMID, 0) == -1) { // 删除消息队列，如果删除失败执行if语句并退出
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
