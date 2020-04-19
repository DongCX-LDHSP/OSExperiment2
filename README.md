# 实验二

## Ubuntu线程竞争范围

这个实验旨在查看Ubuntu的线程竞争范围，需要几个步骤完成

1. 调用`pthread_attr_getscope(&attr, &scope)`获取竞争范围并输出到控制台
2. 使用`pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM)`强制将线程竞争范围修改为系统间，即：SCS
3. 再次获取竞争范围并输出控制台
4. 运行程序，观察记录结果
5. 将2中的语句换为`pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS)`强制将竞争范围修改为进程间，即：PCS
6. 运行程序，观察记录结果，并与4中的结果进行比较

## Linux调度程序

这个实验旨在观察Ubuntu环境下`FIFO`和`RR`两种不同的调度策略的优先级设置

1. 先获取系统当前的调度策略
2. 然后输出当前调度策略以及`FIFO`和`RR`调度策略的优先级
3. 然后依次将调度策略设置为`FIFO`和`RR`
4. 最后`restore 重置`调度策略

## 利用消息队列实现进程间的通信

### 对fork的深入理解

- `fork()`被调用一次，返回两次，分别是父进程与子进程，而子进程的`pid = 0`，父进程的`pid`则是子进程的新产生的`pid`，因为父进程没有一个方法可以获得所有子进程的`pid`，但是子进程可以通过`getpid()`获取自己的`pid`，还可以通过`getppid()`获取父进程的`pid`，进而可以从某种程度上实现获取所有进程的`pid`的目的
- 子进程与父进程拥有相同的`PC(程序计数器)`值，也就是说子进程是从`fork()`返回处开始执行的

### 本次实验的要点

- 老师未将完整的代码给我们，需要我们自行上网查找资料，使用消息队列实现进程间的通信  
参考链接：
    - https://www.cnblogs.com/LUO77/p/5816326.html
    - https://www.codetd.com/article/10658143 较为详细
- 通过例子代码发现发送方和接收方的`qid`值是相同的。  
- 之前只能运行一次的就会遇到`msgsnd: Invalid arguement`异常的原因是：`if语句中的条件`是一个赋值语句，是C语言的使用问题，如下所示：  
`if ((qid = msgget((key_t)1234, IPC_CREAT | 0666)) < 0)`赋值语句外缺少一对括弧，添加之后便可解决那个异常

### 实现步骤

1. 创建一个消息队列，可以在`fork()`之前或之后均可，之前可能更好一点
2. `fork()`获得一个子进程
3. 如果`pid = 0`执行步骤4，否则执行步骤5、6.
4. 向消息结构体中的数据域写入消息，将消息消息结构体中的类型设置为`1`（原因暂时不太清楚），然后调用`msgsnd()`函数发送消息即可
5. 将消息结构体中的类型设置为`0`（原因暂时不太清楚），然后调用`msgrcv()`函数接收消息，最后输出消息即可
6. 删除消息队列

## Make Utility

这个实验使用了宏指令的形式，经过五步完成

1. make -f makefile
2. 修改 `b.h` 文件
3. make -f makefile
4. rm 2.o
5. make -f makefile
