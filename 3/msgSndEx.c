#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <errno.h>
 
#define MAX_TEXT 512
 
struct msg_st
{
    long int msg_type;
    char text[MAX_TEXT];
};
 
int main(int argc, char **argv)
{
    struct msg_st data;
    char buffer[BUFSIZ];
    int msgid = -1;
 
    // 建立消息队列
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
 
    // 向消息队里中写消息，直到写入end
    while (1)
    {
        printf("Enter some text: \n");
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type = 1; // 注意2
        strcpy(data.text, buffer);
 
        // 向队列里发送数据
        if (msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
 
        // 输入end结束输入
        if (strncmp(buffer, "end", 3) == 0)
        {
            break;
        }
 
        sleep(1);
    }
 
    exit(EXIT_SUCCESS);
}
