#include <iostream>
#include<thread>
#include<atomic>
#include <unistd.h>
#include "threadpool.h"

using namespace std;

const int N=10;

void test(std::thread::id id){
    cout<<"thread id   "<<id<<endl;
}


int main() {
    cout<<"test start "<<endl;

    threadpool pool(5,N);
    for(int i=0;i<N;i++){
        pool.add(test);
    }
    //这里等待所有任务被完成
    while(pool.num!=0){

    }
    cout<<"test end and current atomic num :  "<<pool.num<<endl;
    return 0;
}


//线程池的demo
