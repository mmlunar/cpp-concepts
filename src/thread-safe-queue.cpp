#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <shared_mutex>

using namespace std;

template <typename T>
class SafeQueue
{
    private:
        queue<T> data;
        mutex dataMutex;
        condition_variable dataCV;
    public:
        SafeQueue() = default;
        ~SafeQueue() = default;
        
        void push(T x)
        {
            lock_guard<mutex> guardMutex(dataMutex);
            data.push(x);
            cout<<"Pushing: "<<x<<endl;
            dataCV.notify_one();
        }

        void pop()
        {
            unique_lock<mutex> uniqueMutex(dataMutex);
            dataCV.wait(uniqueMutex, [this]{return !data.empty();});
            T x = data.front();
            data.pop();
            cout<<"Popping: "<<x<<endl;
        }
};

class PusherTask
{
    public:
        void operator()(int x, SafeQueue<int>& sq)
        {
            sq.push(x);
        }
};

class PoperTask
{
    public:
        void operator()(SafeQueue<int>& sq)
        {
            sq.pop();
        }
};

int main()
{
    const int totalAgents = 5;
    SafeQueue<int> sq;

    thread pusher[totalAgents], poper[totalAgents];

    PusherTask pusherTask;
    PoperTask poperTask;

    for(int i=0; i<totalAgents; i++)
    {
        pusher[i] = thread(pusherTask, i, ref(sq));
        poper[i] = thread(poperTask, ref(sq));
    }

    for(int i=0; i<totalAgents; i++)
    {
        pusher[i].join();
        poper[i].join();
    }

    return 0;
}

/*
Problem: Design a queue that is thread safe. That means multiple threads can access i.e. push and pop into it without any problem.
Make sure that, pop operation waits until queue has something for popping.

Approach:
For ensuring concurrency we have used a custom class with queue as a member variable. Then we leverage mutex lock to 
let only one thread access the queue. 

Instead of directly locking anf unlocking the mutex, lock_guard is used for push and unique_lock is used for pop.

A condition variable ensures the access of queue for pop operation only when the queue is not empty.
*/


