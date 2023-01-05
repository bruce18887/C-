//
// Created by zlq on 2023/1/5.
//
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace  std;

int main()
{
//    lambda 1
//    int a[] = {3,7,2,9,0,5};
//    sort(a,a+(sizeof(a)/ sizeof(int)),[=](int num1,int num2)->bool{return num1<num2;} );
//    for (auto i:a) {
//            cout<<i<<" ";
//    }
    auto PrintSomething1 = []()->void{
        cout<<"Now Im Here!!!"<<endl;
    };
    auto PrintSomething2 = []()->void{
        cout<<"Now Im not Here!!!"<<endl;
    };
    struct Pos{
        double x;
        double y;
    };
    thread threadson1(
        [&]()->void {
            PrintSomething1();
            this_thread::sleep_for(chrono::seconds(3));
            this_thread::yield();
            PrintSomething2();
            cout<<"thread "<<threadson1.get_id()<< " finished"<<endl;
        }
    );
    thread threadson3(
        [&]()->void {
            unique_ptr<Pos> pospointer(new Pos{3.14,3.3});
            cout<<"Pos x is "<<pospointer->x<<" Pos y is "<<pospointer->y<<endl;
            this_thread::sleep_for(chrono::seconds(1));
            this_thread::yield();
            cout<<"thread "<<threadson3.get_id()<< " finished"<<endl;
        }
    );
    thread threadson2([]{cout<<"Hello world1"<<endl;});
    threadson1.join();
    threadson2.join();
    threadson3.join();
    cout<<"Main thread will  print after threadson finish"<<endl;
}