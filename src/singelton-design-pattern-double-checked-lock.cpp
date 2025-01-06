#include <iostream>
#include <mutex>
#include <thread>
#include <string>

using namespace std;

class Logger
{
    private:
        static Logger* instance;
        static mutex logMutex;
        Logger()
        {
        }
    public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        static Logger* getLogger()
        {
            if(instance == nullptr)
            {
                lock_guard<mutex> lock(logMutex);
                if(instance == nullptr)
                {
                    instance = new Logger();
                }
            }

            return instance;
        }

        void log(string message)
        {
            cout<<"Logging: "<<message<<endl;
        }

};

Logger* Logger::instance = nullptr;
mutex Logger::logMutex;

void logMessages(int threadId)
{
    Logger* logger = Logger::getLogger();  // Get the singleton instance
    logger->log("Message from thread " + to_string(threadId) + "\n");
}

int main()
{
    // Create two threads to test the Logger
    thread t1(logMessages, 1);
    thread t2(logMessages, 2);

    // Wait for both threads to complete
    t1.join();
    t2.join();

    return 0;
}