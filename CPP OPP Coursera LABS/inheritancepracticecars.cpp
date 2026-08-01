#include <iostream>
#include <string>
using namespace std;

// Base class
class Vehicle
{
private:
    string brand;
    int year;

protected:
    int maxSpeed;
    bool engineRunning;

public:
    Vehicle(const string& b, int y, int speed)
        : brand(b), year(y), maxSpeed(speed), engineRunning(false)
    {
        cout << year << " " << brand << " vehicle created." << endl;
    }

    virtual ~Vehicle()
    {
        cout << year << " " << brand << " vehicle destroyed." << endl;
    }

    virtual void displayInfo() const
    {
        cout << year << " " << brand
             << " - Max Speed: " << maxSpeed
             << " mph, Engine: "
             << (engineRunning ? "Running" : "Off") << endl;
    }

    void startEngine()
    {
        if (!engineRunning)
        {
            engineRunning = true;
            cout << brand << " engine started." << endl;
        }
    }

    void stopEngine()
    {
        if (engineRunning)
        {
            engineRunning = false;
            cout << brand << " engine stopped." << endl;
        }
    }

    string getBrand() const
    {
        return brand;
    }

    int getYear() const
    {
        return year;
    }
};

// Car class
class Car : public Vehicle
{
private:
    int numDoors;
    bool trunkOpen;

public:
    Car(const string& brand, int year, int maxSpeed, int doors)
        : Vehicle(brand, year, maxSpeed),
          numDoors(doors),
          trunkOpen(false)
    {
        cout << "Car with " << numDoors << " doors created." << endl;
    }

    ~Car()
    {
        cout << "Car " << getBrand() << " destroyed." << endl;
    }

    void displayInfo() const override
    {
        Vehicle::displayInfo();

        cout << "Type: Car, Doors: " << numDoors
             << ", Trunk: "
             << (trunkOpen ? "Open" : "Closed") << endl;
    }

    void openTrunk()
    {
        trunkOpen = true;
        cout << getBrand() << " trunk opened." << endl;
    }

    // Protected members can be used inside derived classes
    void showStatus()
    {
        cout << getBrand() << " max speed: "
             << maxSpeed << " mph" << endl;
    }
};

// Truck class
class Truck : public Vehicle
{
private:
    double payloadCapacity;
    double currentLoad;

public:
    Truck(const string& brand, int year, int maxSpeed, double capacity)
        : Vehicle(brand, year, maxSpeed),
          payloadCapacity(capacity),
          currentLoad(0.0)
    {
        cout << "Truck with " << payloadCapacity
             << " ton capacity created." << endl;
    }

    ~Truck()
    {
        cout << "Truck " << getBrand() << " destroyed." << endl;
    }

    void displayInfo() const override
    {
        Vehicle::displayInfo();

        cout << "Type: Truck, Capacity: "
             << payloadCapacity
             << " tons, Current Load: "
             << currentLoad
             << " tons" << endl;
    }

    bool loadCargo(double weight)
    {
        if (currentLoad + weight <= payloadCapacity)
        {
            currentLoad += weight;
            cout << "Loaded " << weight << " tons." << endl;
            return true;
        }

        cout << "Cannot load - would exceed capacity!" << endl;
        return false;
    }

    void showStatus()
    {
        cout << getBrand() << " max speed: "
             << maxSpeed << " mph" << endl;
    }
};

int main()
{
    // Create objects
    Car myCar("Toyota", 2024, 130, 4);
    Truck myTruck("Ford", 2023, 90, 10.0);

    cout << "\n--- Car Test ---" << endl;
    myCar.displayInfo();
    myCar.startEngine();
    myCar.openTrunk();
    myCar.showStatus();
    myCar.displayInfo();
    myCar.stopEngine();

    cout << "\n--- Truck Test ---" << endl;
    myTruck.displayInfo();
    myTruck.startEngine();
    myTruck.loadCargo(5.0);
    myTruck.loadCargo(4.0);
    myTruck.loadCargo(3.0);   // Exceeds capacity
    myTruck.showStatus();
    myTruck.displayInfo();
    myTruck.stopEngine();

    cout << "\n--- Public Access ---" << endl;
    cout << "Car Brand: " << myCar.getBrand() << endl;
    cout << "Car Year: " << myCar.getYear() << endl;

    /*
    These would NOT compile because they are private:
    myCar.brand;
    myCar.year;

    These would also NOT compile because they are protected:
    myCar.maxSpeed;
    myCar.engineRunning;
    */

    return 0;
}