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

## 利用消息队列实现进程间的通信

## Make Utility

这个实验使用了宏指令的形式，经过五步完成

1. make -f makefile
2. 修改 `b.h` 文件
3. make -f makefile
4. rm 2.o
5. make -f makefile
