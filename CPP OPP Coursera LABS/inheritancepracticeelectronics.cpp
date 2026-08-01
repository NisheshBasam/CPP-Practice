#include <iostream>
#include <string>
using namespace std;

class ElectronicDevice
{
private:
    string brand;
    string model;

protected:
    int powerConsumption;
    bool isOn;

public:
    ElectronicDevice(string b, string m, int power)
    {
        brand = b;
        model = m;
        powerConsumption = power;
        isOn = false;
    }

    virtual ~ElectronicDevice()
    {
        cout << brand << " " << model << " destroyed." << endl;
    }

    void turnOn()
    {
        isOn = true;
        cout << brand << " " << model << " is now on." << endl;
    }

    void turnOff()
    {
        isOn = false;
        cout << brand << " " << model << " is now off." << endl;
    }

    virtual void displaySpecs() const
    {
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Power Consumption: " << powerConsumption << " watts" << endl;
        cout << "Power Status: " << (isOn ? "On" : "Off") << endl;
    }

    string getBrand() const
    {
        return brand;
    }

    string getModel() const
    {
        return model;
    }
};

class Smartphone : public ElectronicDevice
{
private:
    double screenSize;
    int storageCapacity;
    int batteryLife;

public:
    Smartphone(string brand, string model, int power,
               double screen, int storage, int battery)
        : ElectronicDevice(brand, model, power)
    {
        screenSize = screen;
        storageCapacity = storage;
        batteryLife = battery;
    }

    ~Smartphone()
    {
        cout << "Smartphone " << getModel() << " destroyed." << endl;
    }

    void displaySpecs() const
    {
        ElectronicDevice::displaySpecs();

        cout << "Device Type: Smartphone" << endl;
        cout << "Screen Size: " << screenSize << " inches" << endl;
        cout << "Storage: " << storageCapacity << " GB" << endl;
        cout << "Battery Life: " << batteryLife << " hours" << endl;
    }

    void makeCall(string phoneNumber) const
    {
        if (isOn)
        {
            cout << "Calling " << phoneNumber << "..." << endl;
        }
        else
        {
            cout << "The phone must be turned on first." << endl;
        }
    }

    void sendText(string message) const
    {
        if (isOn)
        {
            cout << "Text sent: " << message << endl;
        }
        else
        {
            cout << "The phone must be turned on first." << endl;
        }
    }

    void takePicture() const
    {
        if (isOn)
        {
            cout << "Picture taken." << endl;
        }
        else
        {
            cout << "The phone must be turned on first." << endl;
        }
    }
};

class Laptop : public ElectronicDevice
{
private:
    int ramSize;
    string processorType;
    double screenSize;

public:
    Laptop(string brand, string model, int power,
           int ram, string processor, double screen)
        : ElectronicDevice(brand, model, power)
    {
        ramSize = ram;
        processorType = processor;
        screenSize = screen;
    }

    ~Laptop()
    {
        cout << "Laptop " << getModel() << " destroyed." << endl;
    }

    void displaySpecs() const
    {
        ElectronicDevice::displaySpecs();

        cout << "Device Type: Laptop" << endl;
        cout << "RAM: " << ramSize << " GB" << endl;
        cout << "Processor: " << processorType << endl;
        cout << "Screen Size: " << screenSize << " inches" << endl;
    }

    void runProgram(string programName) const
    {
        if (isOn)
        {
            cout << programName << " is now running." << endl;
        }
        else
        {
            cout << "The laptop must be turned on first." << endl;
        }
    }

    void connectToWifi(string networkName) const
    {
        if (isOn)
        {
            cout << "Connected to WiFi network: " << networkName << endl;
        }
        else
        {
            cout << "The laptop must be turned on first." << endl;
        }
    }

    void saveFile(string fileName) const
    {
        if (isOn)
        {
            cout << fileName << " was saved." << endl;
        }
        else
        {
            cout << "The laptop must be turned on first." << endl;
        }
    }
};

int main()
{
    Smartphone phone("Apple", "iPhone", 20, 6.1, 256, 22);
    Laptop laptop("Dell", "XPS 15", 65, 16, "Intel Core i7", 15.6);

    cout << "\n--- Smartphone Test ---" << endl;

    phone.displaySpecs();
    phone.makeCall("555-1234");

    phone.turnOn();
    phone.makeCall("555-1234");
    phone.sendText("Hello!");
    phone.takePicture();
    phone.turnOff();

    cout << "\n--- Laptop Test ---" << endl;

    laptop.displaySpecs();

    laptop.turnOn();
    laptop.runProgram("Visual Studio Code");
    laptop.connectToWifi("Home Network");
    laptop.saveFile("project.cpp");
    laptop.turnOff();

    cout << "\n--- Public Access Test ---" << endl;

    cout << "Phone brand: " << phone.getBrand() << endl;
    cout << "Laptop model: " << laptop.getModel() << endl;

    cout << "\n--- Polymorphism Test ---" << endl;

    ElectronicDevice* device1 = &phone;
    ElectronicDevice* device2 = &laptop;

    device1->displaySpecs();

    cout << endl;

    device2->displaySpecs();

    return 0;
}