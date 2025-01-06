#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

class ThreadPool
{
  private:
    int numThreads;
    bool stop;
    queue<function<void()>> tasks;
    mutex threadAccessMutex;
    condition_variable cv;
    vector<thread> threads;

    // Member function to run in the threads
    void processTask()
    {
        function<void()> task;
        while (1)
        {
            unique_lock<mutex> uniqueMutex(threadAccessMutex);
            cv.wait(uniqueMutex, [this]{ return !tasks.empty() || stop; });
            if (stop && tasks.empty())
            {
                cout << "Stopping thread: " << this_thread::get_id() << endl;
                return;
            }
            task = move(tasks.front());
            tasks.pop();
            cout << "Queue size: " << tasks.size() << endl;
            uniqueMutex.unlock();
            task();
        }
    }

    void startPool()
    {
      for(int i=0; i<numThreads; i++)
      {
        threads.emplace_back(bind(&ThreadPool::processTask, this));
      }
    }

  public:
    ThreadPool(int m_Threads) : numThreads(m_Threads), stop(false)
    {
      startPool();
    }

    void execute(function<void()> task)
    {
      unique_lock<mutex> uniqueLock(threadAccessMutex);
      tasks.push(task);
      uniqueLock.unlock();
      cv.notify_one();
    }

    ~ThreadPool()
    {
      {
        lock_guard<mutex> guardLock(threadAccessMutex);
        stop = true;
      }
      cv.notify_all();
      
      for (thread& th : threads) 
      {
        th.join();
      }
    }
};

void runTask()
{
  this_thread::sleep_for(chrono::seconds(2));
}

// To execute C++, please define "int main()"
int main() 
{
  int tasks = 64;
  int m = 8;

  ThreadPool threadPool(m);

  for(int i=0; i<tasks; i++)
  {
    threadPool.execute(runTask);
  }

  return 0;
}
