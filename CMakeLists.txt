cmake_minimum_required(VERSION 3.10)
project(PrimeRentals)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define vcpkg root and toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Aman Rawat/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Add the executable
add_executable(PrimeRentals main.cpp)

# Link JSONcpp library
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(PrimeRentals PRIVATE jsoncpp_lib)
