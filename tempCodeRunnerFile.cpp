#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "include/json/json.h"

using namespace std;

// Car Class
class Car
{
public:
  Car(string brand, string model, double price)
      : brand(brand), model(model), price(price), available(true) {}

  string getBrand() const { return brand; }
  string getModel() const { return model; }
  double getPrice() const { return price; }
  bool isAvailable() const { return available; }

  void setAvailable(bool status) { available = status; }

private:
  string brand;
  string model;
  double price;
  bool available;
};

// Rental Class
class Rental
{
public:
  Rental(string customerName, Car *rentedCar, int duration)
      : customerName(customerName), rentedCar(rentedCar), duration(duration) {}

  void generateReceipt() const
  {
    cout << "Receipt:\n";
    cout << "Customer: " << customerName << "\n";
    cout << "Car Rented: " << rentedCar->getBrand() << " " << rentedCar->getModel() << "\n";
    cout << "Total Price: " << rentedCar->getPrice() * duration << "\n";
    cout << "Duration: " << duration << " days\n";
  }

private:
  string customerName;
  Car *rentedCar;
  int duration;
};

// Inventory Singleton Class
class Inventory
{
public:
  static Inventory &getInstance()
  {
    static Inventory instance;
    return instance;
  }

  void addCar(const Car &car)
  {
    cars.push_back(car);
  }

  void removeCar(int index)
  {
    if (index >= 0 && index < cars.size())
    {
      cars.erase(cars.begin() + index);
    }
  }

  Car *getCar(int index)
  {
    if (index >= 0 && index < cars.size())
    {
      return &cars[index];
    }
    return nullptr;
  }

  vector<Car> &getCars()
  {
    return cars;
  }

private:
  Inventory() {}
  vector<Car> cars;
};

// RentalManager Class
class RentalManager
{
public:
  void rentCar(string customerName, int carIndex, int duration)
  {
    Car *car = Inventory::getInstance().getCar(carIndex);
    if (car && car->isAvailable())
    {
      car->setAvailable(false); // Mark car as rented
      Rental rental(customerName, car, duration);
      rental.generateReceipt();
    }
    else
    {
      cout << "Car not available.\n";
    }
  }

  void returnCar(int carIndex)
  {
    Car *car = Inventory::getInstance().getCar(carIndex);
    if (car)
    {
      car->setAvailable(true); // Mark car as available
      cout << "Car returned.\n";
    }
  }
};

// JSONData Class using JSONcpp
class JSONData
{
public:
  void saveData(const vector<Car> &cars, const string &filename)
  {
    Json::Value root;
    for (size_t i = 0; i < cars.size(); ++i)
    {
      Json::Value carData;
      carData["brand"] = cars[i].getBrand();
      carData["model"] = cars[i].getModel();
      carData["price"] = cars[i].getPrice();
      carData["available"] = cars[i].isAvailable();
      root["cars"].append(carData);
    }
    ofstream file(filename);
    file << root;
    file.close();
  }

  void loadData(vector<Car> &cars, const string &filename)
  {
    Json::Value root;
    ifstream file(filename);
    file >> root;
    for (const auto &carData : root["cars"])
    {
      cars.push_back(Car(carData["brand"].asString(),
                         carData["model"].asString(),
                         carData["price"].asDouble()));
    }
  }
};

// Main Program
int main()
{
  Inventory &inventory = Inventory::getInstance();

  // Adding cars
  inventory.addCar(Car("Toyota", "Corolla", 50.0));
  inventory.addCar(Car("Honda", "Civic", 60.0));

  // Saving to JSON
  JSONData jsonData;
  jsonData.saveData(inventory.getCars(), "cars.json");

  // Rental process
  RentalManager rentalManager;
  rentalManager.rentCar("John Doe", 0, 5); // Rent car at index 0 for 5 days
  rentalManager.returnCar(0);              // Return car at index 0

  // Loading from JSON
  vector<Car> loadedCars;
  jsonData.loadData(loadedCars, "cars.json");

  return 0;
}
