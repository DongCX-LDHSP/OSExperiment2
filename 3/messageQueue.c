#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stropts.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define TXTLEN (512)

struct msg
{
    long msg_type;
    char msg_buf[TXTLEN];
};

int main()
{
    printf("作者：181110305董成相\n\n");
    int qid;
    pid_t pid;
    struct msg pmsg;

    //这里的赋值语句应当由一对括弧包裹，然后才能进行比较，不然就是赋值语句的返回值与0进行比较i
    if ((qid = msgget((key_t)1234, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget\n");
        exit(1);
    }
    printf("The queue id is: %d\n", qid);

    pid = fork();//生成一个子进程与父进程通信

    if (pid == 0)
    {
        //写入待发送消息
        sprintf(pmsg.msg_buf, "Hello! This is child！ My parent's pid is : %d. And my pid is %d", getppid(), getpid());
        //这个msg_type暂时有点迷
        pmsg.msg_type = 1;
        //接下来就是发送消息啦
        //qid是指消息队列号，pmsg是消息结构体，TXLEN是消息的长度，0是指
        if (msgsnd(qid, (void*)&pmsg, TXTLEN, 0) < 0)
        {
            perror("msgsnd\n");
            exit(1);
        }
        printf("\nChild successfully send a message to the queue: %d\n\n", qid);
    }

    if (pid > 0)
    {
        //这个msg_type暂时有点迷
        pmsg.msg_type = 0;
        //接收消息
        if (msgrcv(qid, (void*)&pmsg, TXTLEN, 0, 0) < 0)
        {
            perror("msgrcv\n");
            exit(1);
        }

        //输出消息
        printf("Hello! I'm the parent. I revieved a message from my child that is \n\"%s\"\n", pmsg.msg_buf);
        
        //删除消息队列
        if (msgctl(qid, IPC_RMID, NULL) < 0)
        {
            perror("msgctl\n");
            exit(1);
        }
        printf("\nThe queue was deleted by parent process.\n");
    }
    return 0;
}
