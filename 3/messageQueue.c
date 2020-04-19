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

    pid = fork();//生成一个子进程与父进程通信

    if ((qid = msgget((key_t)1234, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget\n");
        exit(1);
    }

    printf("The queue id is: %d\n", qid);

    if (pid == 0)
    {
        sprintf(pmsg.msg_buf, "Hello! This is child！ My parent's pid is : %d. And my pid is %d", getppid(), getpid());
        pmsg.msg_type = 1;
        if (msgsnd(qid, (void*)&pmsg, TXTLEN, 0) < 0)
        {
            perror("msgsnd\n");
            exit(1);
        }
        printf("\nSuccessfully send a message to the queue: %d\n\n", qid);
    }

    if (pid > 0)
    {
        pmsg.msg_type = 0;
        if (msgrcv(qid, (void*)&pmsg, TXTLEN, 0, 0) < 0)
        {
            perror("msgrcv\n");
            exit(1);
        }
        printf("Hello! I'm the parent. I revieved a message from my child that refers to \n\"%s\"\n", pmsg.msg_buf);
        if (msgctl(qid, IPC_RMID, NULL) < 0)
        {
            perror("msgctl\n");
            exit(1);
        }
        printf("\nThe queue was deleted by parent process.\n");
    }
    return 0;
}
