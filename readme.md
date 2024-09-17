# 轻量级线程池
写了一个简单的线程池，主要是为了练手，因为太久没写线程池了



## 线程池的意义
多线程并发执行的时候，我们要考虑加锁问题，在任务队列的push操作和pop操作都需要考虑线程安全问题。
所以需要加锁，但是每个线程拿取的任务由于是独立的，此时就不需要考虑加锁，从而提高了并发的效率
## 测试线程池

根据图片可以发现,放入10个函数执行，输出也只进行10次.

所以线程是安全的，


![image ](https://github.com/huanheart/threadpool/blob/master/image/testphoto.png)

## 待扩展

- [X] 写完一个初步线程池
- [ ] 扩展当前线程池，实现更高性能
