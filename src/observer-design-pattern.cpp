#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class ISubscriber
{
    public:
        virtual void update(string msg) = 0;
};

class User : public ISubscriber
{
    private:
        string name;
    public:
        User(string m_name)
        {
            this->name = m_name;
        }

        void update(string msg) override
        {
            cout<<"Updating: "<<name<<", Message: "<<msg<<endl;
        }

            // Define equality operator to compare users by name (or any other criteria you prefer)
        bool operator==(const User& other) const
        {
            return name == other.name;
        }
};

class Group
{
    private:
        list<User> userGroup;
    public:
        void addUser(User user)
        {
            userGroup.push_back(user);
        }

        void removeUser(User user)
        {
            userGroup.remove(user);
        }

        void notify(string msg)
        {
            for(User& user : userGroup)
            {
                user.update(msg);
            }
        }
};

int main()
{
    string userNames[] = {"User 0", "User 1", "User 2", "User 3"};
    User users[] = {User(userNames[0]), User(userNames[1]), User(userNames[2]), User(userNames[3])};
    Group g;
    
    for (int i = 0; i < 4; ++i) 
    {
        g.addUser(users[i]);
    }

    g.notify("New message");
    g.removeUser(users[2]);
    g.notify("Latest message");
    
    return 0;
}