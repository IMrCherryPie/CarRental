//
// Created by 79526 on 15.01.2019.
//

#ifndef CARRENTAL_MOTORCYCLE_H
#define CARRENTAL_MOTORCYCLE_H

#include <string>
#include "Vehicle.h"

class Motorcycle : public Vehicle{
public:
    Motorcycle (string Type,string Brand, string Model, int YearOfManufacture, string Color, string Number, int Milleage, int Rental_price)
    {
        this->Type = Type;
        this->Brand = Brand;
        this->Model= Model;
        this->YearOfManufacture = YearOfManufacture;
        this->Color = Color;
        this->Number = Number;
        this->Milleage = Milleage;
        this->Rental_price = Rental_price;
    };
};
class Cars : public Vehicle{
public:
    Cars (string Type,string Brand, string Model, int YearOfManufacture, string Color, string Number, int Milleage, int Rental_price)
    {
        this->Type = Type;
        this->Brand = Brand;
        this->Model= Model;
        this->YearOfManufacture = YearOfManufacture;
        this->Color = Color;
        this->Number = Number;
        this->Milleage = Milleage;
        this->Rental_price = Rental_price;
    };
};
#endif //CARRENTAL_MOTORCYCLE_H
