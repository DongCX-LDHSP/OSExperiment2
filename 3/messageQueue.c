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

struct msg
{
    long msg_types;
    char msg_buf[511];
};

int main()
{
    int qid;
    int pid;
    int len;
    struct msg pmsg;
    sprintf(pmsg.msg_buf, "hello! this is: %d\n", getpid());
    len = strlen(pmsg.msg_buf);
    if ((qid = msgget(IPC_PRIVATE, IPC_CREAT | 0666) < 0))
    {
        perror("msgget\n");
        exit(1);
    }
    if ((msgsnd(qid, &pmsg, len, 0) < 0))
    {
        perror("msgsnd\n");
        exit(1);
    }
    printf("successfully send a message to the queue: %d\n", qid);
    return 0;
    
}
