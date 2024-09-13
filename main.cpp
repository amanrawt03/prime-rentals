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

// CarFactory Class for creating Car objects
class CarFactory
{
public:
  static Car createCar(const string &brand, const string &model, double price)
  {
    return Car(brand, model, price);
  }
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

  void displayAvailableCars() const
  {
    vector<Car> &cars = Inventory::getInstance().getCars();
    if (cars.empty())
    {
      cout << "No cars available.\n";
      return;
    }

    cout << "Available Cars:\n";
    for (size_t i = 0; i < cars.size(); ++i)
    {
      if (cars[i].isAvailable())
      {
        cout << i << ": " << cars[i].getBrand() << " " << cars[i].getModel() << " - $" << cars[i].getPrice() << " per day\n";
      }
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

  // Create and add cars using CarFactory
  Car toyota = CarFactory::createCar("Toyota", "Corolla", 50.0);
  Car honda = CarFactory::createCar("Honda", "Civic", 60.0);
  Car ford = CarFactory::createCar("Ford", "Focus", 55.0);
  Car bmw = CarFactory::createCar("BMW", "X5", 80.0);
  inventory.addCar(toyota);
  inventory.addCar(honda);
  inventory.addCar(ford);
  inventory.addCar(bmw);

  // Saving to JSON
  JSONData jsonData;
  jsonData.saveData(inventory.getCars(), "cars.json");

  // Main Menu
  RentalManager rentalManager;
  int choice, carIndex, duration;
  string customerName;

  while (true)
  {
    cout << "1. Rent a Car\n";
    cout << "2. See Available Cars\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // to ignore the newline character after the integer input

    switch (choice)
    {
    case 1:
      rentalManager.displayAvailableCars();
      cout << "Enter car index to rent: ";
      cin >> carIndex;
      cout << "Enter rental duration (in days): ";
      cin >> duration;
      cin.ignore(); // to ignore the newline character after the integer input
      cout << "Enter customer name: ";
      getline(cin, customerName);
      rentalManager.rentCar(customerName, carIndex, duration);
      break;

    case 2:
      rentalManager.displayAvailableCars();
      break;

    case 3:
      cout << "Exiting...\n";
      return 0;

    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}
