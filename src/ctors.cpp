#include <iostream>
#include <cstring>

using namespace std;

class Person
{
    private:
        char *name;
        int size;
    public:
        Person(char *m_name)
        {
            size = strlen(m_name);
            name = new char[size + 1];
            strcpy(name, m_name);
            cout << "Constructor called: " << this->name << endl;
        }

        Person(const Person& other)
        {
            size = other.size;
            name = new char[size + 1];
            strcpy(name, other.name);
            cout << "Copy constructor called: " << this->name << endl;
        }

        Person(Person&& other) noexcept
        {
            size = other.size;
            name = other.name;
            other.name = nullptr;
            other.size = 0;
            cout << "Move constructor called: " << this->name << endl;
        }

        Person& operator=(const Person& other)
        {
            if(this == &other)
            {
                return *this;
            }

            delete []name;
            size = other.size;
            name = new char[size + 1];
            strcpy(name, other.name);
            cout << "Copy Assignment Operator called: " << this->name << endl;

            return *this;           
        }

        Person& operator=(Person&& other) noexcept
        {
            if(this == &other)
            {
                return *this;
            }

            delete []name;
            size = other.size;
            name = other.name;
            other.name = nullptr;
            other.size = 0;
            cout << "Move Assignment Operator called: " << this->name << endl;

            return *this;
        }

        // Method to print the name
        void print() const 
        {
            cout << "Name: " << (name ? name : "No name") << endl;
        }

        // Destructor
        ~Person() 
        {
            delete[] name;
            cout << "Destructor called: " << (name ? name : "No name") << endl;
        }

};

int main()
{
    // Create a Person object using constructor
    Person person1("Alice");

    // Copy Constructor
    Person person2 = person1;  // Copy constructor is called

    // Move Constructor
    Person person3 = move(person1);  // Move constructor is called

    // Copy Assignment
    Person person4("Bob");
    person4 = person2;  // Copy assignment operator is called

    // Move Assignment
    person4 = move(person2);  // Move assignment operator is called

    // Print the names
    person1.print();
    person2.print();
    person3.print();
    person4.print();

    return 0;
}