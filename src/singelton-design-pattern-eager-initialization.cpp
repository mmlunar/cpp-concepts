#include <iostream>
#include <mutex>
#include <thread>
#include <string>

using namespace std;

class Logger
{
    private:
        static mutex logMutex;
        static Logger* instance;
        Logger()
        {
            cout << "Singleton created" << std::endl;
        }
    public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        static Logger* getLogger()
        {
            return instance;
        }

        void log(string message)
        {
            cout<<"Logging: "<<message<<endl;
        }

};

Logger* Logger::instance = new Logger();

void logMessages(int threadId)
{
    Logger* logger = Logger::getLogger();  // Get the singleton instance
    logger->log("Message from thread " + to_string(threadId) + "\n");
}

int main()
{
    cout<<"Starting the main"<<endl;
    // Create two threads to test the Logger
    thread t1(logMessages, 1);
    thread t2(logMessages, 2);

    // Wait for both threads to complete
    t1.join();
    t2.join();

    return 0;
}