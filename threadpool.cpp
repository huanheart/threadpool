//
// Created by 31897 on 2024/9/17.
//

#include "threadpool.h"
#include<iostream>

void threadpool::add(std::function<void( std::thread::id) >  e) {
    mtx.lock();
    workerlist.push_back(e);
    mtx.unlock();
    sem.signal();
}


std::function<void( std::thread::id) >  threadpool::pop() {
    mtx.lock();
    std::function<void(std::thread::id) > temp=workerlist.front();
    workerlist.pop_front();
    mtx.unlock();
    return temp;
}

threadpool::threadpool(int num,int cnt):threadNum(num),num(cnt) {

    for(int i=0;i<threadNum;i++){
        std::thread t(run,this);
        t.detach();
    }

}

void threadpool::run(void * arg) {
    threadpool * pool=(threadpool*) arg;
    pool->start();
}

void threadpool::start() {
    while(true){
        //等待当前的锁,防止让线程在没有任务的时候一直抢占时间片，使性能下降
        sem.wait();
        std::function<void( std::thread::id)> temp=pop();
        //开始执行对应的temp函数
        temp(std::this_thread::get_id() );
        num--;
    }
}

