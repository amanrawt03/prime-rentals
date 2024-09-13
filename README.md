PrimeRentals - Car Rental System
Welcome to PrimeRentals, a modern and efficient car rental system built using C++! 🚗✨ This project demonstrates the use of design patterns, including Singleton and Factory, to manage a dynamic car rental service. It supports functionalities like renting cars, viewing available cars, generating receipts, and saving/loading data in JSON format.

📋 Features
Rent a Car: Easily rent a car by selecting from available options and specifying the rental duration.
See Available Cars: View the list of cars currently available for rent.
Generate Receipt: Automatically generate and display a detailed receipt for each rental.
Save and Load Data: Save car data to a JSON file and load it back for persistence across sessions.
🛠️ Technologies Used
C++: Programming language used for implementing the core functionality.
Singleton Pattern: Ensures a single instance of the inventory management system.
Factory Pattern: Used to create car objects with specific attributes.
JSONcpp: Library for handling JSON data, used for saving and loading car information.
🚀 Getting Started
To get started with PrimeRentals, follow these instructions:

Prerequisites
C++ Compiler: Ensure you have a C++ compiler installed (e.g., g++ or MSVC).
CMake: Required for building the project.
JSONcpp: Make sure the JSONcpp library is installed and configured.
Installation
Clone the Repository:

sh
Copy code
git clone https://github.com/yourusername/PrimeRentals.git
cd PrimeRentals
Build the Project:

sh
Copy code
mkdir build
cd build
cmake ..
cmake --build .
Usage
Run the Executable: Navigate to the build/Debug directory (or the appropriate build configuration directory) and run:

sh
Copy code
./PrimeRentals
Interact with the Application: Follow the prompts to:

Rent a car
View available cars
Generate a receipt
The application will also save the current car data to cars.json and load it when you restart the application.

🤝 Contributing
Contributions are welcome! If you have suggestions or improvements, feel free to open an issue or submit a pull request.

📧 Contact
For any questions or feedback, please contact amanrawat3021@example.com.
