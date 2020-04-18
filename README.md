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

### 本次实验的重点

老师未将完整的代码给我们，需要我们自行上网查找资料，使用消息队列实现进程间的通信  
参考链接：https://www.cnblogs.com/LUO77/p/5816326.html


## Make Utility

这个实验使用了宏指令的形式，经过五步完成

1. make -f makefile
2. 修改 `b.h` 文件
3. make -f makefile
4. rm 2.o
5. make -f makefile
