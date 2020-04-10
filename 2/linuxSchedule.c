#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <stdio.h>

static int get_thread_policy(pthread_attr_t attr);
static void set_thread_policy(pthread_attr_t attr, int policy);
static void show_thread_priority(pthread_attr_t attr, int policy);
static int get_thread_priority(pthread_attr_t attr);

int main()
{
    printf("作者：181110305董成相\n");
    pthread_attr_t attr;
    struct sched_param sched;
    int rs = pthread_attr_init(&attr);
    int policy = get_thread_policy(attr);
    printf("- show current configuration of prioroty\n");
    show_thread_priority(attr, policy);
    printf("- show SCHED_FIFO of priority\n");
    show_thread_priority(attr, SCHED_FIFO);
    printf("- show SCHED_RR of priority\n");
    show_thread_priority(attr, SCHED_RR);
    printf("- show priority of current thread\n");
    int priority = get_thread_priority(attr);
    printf("SET THREAD POLICY\n");
    printf("set SCHED_FIFO policy\n");
    set_thread_policy(attr, SCHED_FIFO);
    printf("set SCHED_RR policy\n");
    set_thread_policy(attr, SCHED_RR);
    printf("restore current policy\n");
    set_thread_policy(attr, policy);
    pthread_attr_destroy(&attr);
    return 0;
}

static int get_thread_policy(pthread_attr_t attr)
{
    int policy;
    pthread_attr_getschedpolicy(&attr, &policy);
    switch (policy)
    {
    case SCHED_FIFO:
        printf("policy = SCHED_FIFO\n");
        break;
    case SCHED_RR:
        printf("policy = SCHED_RR\n");
        break;
    case SCHED_OTHER:
        printf("policy = SCHED_OTHER\n");
        break;
    default:
        printf("policy = UNKNOWN\n");
        break;
    }
    return policy;
}

static void set_thread_policy(pthread_attr_t attr, int policy)
{
    pthread_attr_setschedpolicy(&attr, policy);
    get_thread_policy(attr);
}

static void show_thread_priority(pthread_attr_t attr, int policy)
{
    int priority = sched_get_priority_max(policy);
    printf("max_priority = %d\n", priority);
    priority = sched_get_priority_min(policy);
    printf("min_priority = %d\n", priority);
}

static int get_thread_priority(pthread_attr_t attr)
{
    struct sched_param param;
    pthread_attr_getschedparam(&attr, &param);
    printf("priority = %d\n", param.sched_priority);
    return param.sched_priority;
}
