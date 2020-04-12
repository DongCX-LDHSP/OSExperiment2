#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[MAX_TEXT];
};// 消息格式，与接收端一致
int main()
{
    int running = 1;
    struct my_msg_st some_data;
    int msgid;
    char buffer[BUFSIZ];
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);// 创建消息标识符key = 1234的消息队列。如果该队列已经存在，则直接返回该队列的标识符，以便向该消息队列收发消息
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }// 错误处理，同接收者msg1
    while(running) {
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);// 由控制台输入文本，并将其存放在buffer之中
        some_data.my_msg_type = 1;// 类型填充，在本例中没有特别含义
        strcpy(some_data.some_text, buffer);// 将buffer数据复制到some_text之中
        if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) { // 向消息队列发送消息，如果发送失败执行if语句并退出
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer, "end", 3) == 0) {// 如果发送的"end"，则在发送"end"之后，退出while，结束程序
            running = 0;
        }
    }
    exit(EXIT_SUCCESS);
}
