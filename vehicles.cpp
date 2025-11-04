#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
protected:
    string brand;

public:
    Vehicle(string b) : brand(b) {};

    virtual void startEngine() const = 0;

    string getBrand() const
    {
        return brand;
    };

    virtual ~Vehicle() {};
};

class Car : public Vehicle
{
public:
    int horsepower;

public:
    Car(string b, int hp) : Vehicle(b), horsepower(hp) {};

    void startEngine() const override
    {
        cout << "Car " << brand << " with " << horsepower << " HP engine started" << endl;
    };

    ~Car() {};
};

class Bike : public Vehicle
{
public:
    string type;

public:
    Bike(string b, string t) : Vehicle(b), type(t) {};

    void startEngine() const override
    {
        cout << "Bike " << brand << " of type " << type << endl;
    };

    ~Bike() {};
};

int main()
{
    Vehicle *myCar = new Car("Toyota Yarris", 60);
    Vehicle *myBike = new Bike("Yamaha", "Sport");

    myCar->startEngine();
    myBike->startEngine();

    delete myBike;
    delete myCar;

    return 0;
}