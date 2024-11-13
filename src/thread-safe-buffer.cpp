#define CAPACITY 256

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;

class SafeBuffer
{
    private:
        int data[CAPACITY];
        int head;
        int tail;
        int count;
        mutex mutexDataAccess;
        condition_variable cvDataAccess;
    public:
        SafeBuffer()
        {
            head = 0;
            tail = 0;
            count = 0;
        }

        void push(int x)
        {
            unique_lock<mutex> lock(mutexDataAccess);
            cvDataAccess.wait(lock, [this]{ return count < CAPACITY; });
            data[tail] = x;
            tail = (tail+1)%CAPACITY;
            count++;
            cout<<"Producing: "<<x<<endl;
            cvDataAccess.notify_one();
        }

        void pop()
        {
            unique_lock<mutex> lock(mutexDataAccess);
            cvDataAccess.wait(lock, [this]{return count>0;});
            int x = data[head];
            head = (head+1)%CAPACITY;
            count--;
            cout<<"Consuming: "<<x<<endl;
            cvDataAccess.notify_one();
        }
};

void producer(int x, SafeBuffer& sb)
{
    sb.push(x);
}

void consumer(SafeBuffer& sb)
{
    sb.pop();
}


int main() 
{
    thread prod[CAPACITY], cons[CAPACITY];
    SafeBuffer sb;

    for(int i=0; i<CAPACITY; i++)
    {
        prod[i] = thread(producer, i, ref(sb));
        cons[i] = thread(consumer, ref(sb));
    }

    for(int i=0; i<CAPACITY; i++)
    {
        prod[i].join();
        cons[i].join();
    }

    return 0;
}
