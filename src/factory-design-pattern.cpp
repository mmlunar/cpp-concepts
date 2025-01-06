#include <iostream>
#include <string>
#include <stdexcept> 

using namespace std;

class IVehicle
{
  public:
    virtual void create() = 0;
};

class Car : public IVehicle
{
  public:
    void create()
    {
      cout<<"Creating a car";
    }
};

class Bike : public IVehicle
{
  public:
    void create()
    {
      cout<<"Creating a bike";
    }
};

class VehicleFactory
{
  public:
    static IVehicle* getVehicle(string vehicleType)
    {
      if(vehicleType == "Car")
      {
        return new Car();
      }
      else if(vehicleType == "Bike")
      {
        return new Bike();
      }
      else 
      {
        throw invalid_argument("Invalid input");
      }
    }
};



// To execute C++, please define "int main()"
int main() 
{
  string vehicleType = "Car";
  IVehicle *vehicle = VehicleFactory::getVehicle(vehicleType);
  vehicle->create();
  return 0;
}
