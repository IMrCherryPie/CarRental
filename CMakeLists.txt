cmake_minimum_required(VERSION 3.13)
project(CarRental)

set(CMAKE_CXX_STANDARD 14)

add_executable(CarRental main.cpp Vehicle.h Car.h Motorcycle.h)