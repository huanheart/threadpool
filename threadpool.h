//
// Created by 31897 on 2024/9/17.
//

#ifndef UNTITLED_THREADPOOL_H
#define UNTITLED_THREADPOOL_H

#include<thread>
#include<list>
#include<functional>
#include<condition_variable>
#include <mutex>
#include<atomic>
//自定义信号量
class Sem{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count=0;
public:
    Sem(int count_=0) :count(count_){}
    //消费者
    void wait(){

        std::unique_lock<std::mutex> lock(mtx);
        while(count==0){
            cv.wait(lock);
        }
        count--;
    }
    //生产者
    void signal(){
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_all();

    }

};

class threadpool{
private:
    int threadNum;
    Sem sem;
    std::mutex mtx;
//    std::list<std::function<void()> > workerList;
    std::list<std::function<void( std::thread::id) > > workerlist;

public:
    std::atomic<int>  num;
    void add(std::function<void(std::thread::id) >  e);
    std::function<void( std::thread::id) >   pop();
    threadpool(int num,int cnt);
    static void run(void * arg);
    void start();
};


#endif //UNTITLED_THREADPOOL_H
