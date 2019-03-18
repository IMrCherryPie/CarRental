//
// Created by 79526 on 25.12.2018.
//

#ifndef CARRENTAL_CAR_H

#define CARRENTAL_CAR_H
#include <cstring>
using namespace std;
class Vehicle
{
    protected:
    string Type;                //Тип ТС
    string Brand;               //Брэнд
    string Model;               // Модель ТС
    int YearOfManufacture;      // Год производства ТС
    string Color;               // Цвет ТС
    string Number;              // Гос номер ТС
    int Milleage;                // Пробег ТС
    int Rental_price;           // Стоимость Аренды ТС

    int MilleageRental;           //Пробег за время аренды
    int MilleageMonth;           //Пробез за месяц
    int RentalDay;                //День Аренды ТС

    int second;                  //Секунда, не будет учитываться при создании отчёта
    int RentalMinute;            //Минута аренды
    int RentalHour;              //Час аренды
    int RentalMonth;             //Месяц аренды
    int LeaseTerm;               //Срок аренды
    int Status;                 //Статус аренды
    int ReturnDate;             //Дата возврата день
    int RentalHourReturn;       //Час возврата ТС
    int Customer;               //Клиент

    int PenaltyRate;            //Размер штрафа
    int CostOf;                 //Расчётная стоимость аренды без учёта штрафа
    int CostOfMonth;            //Итоговый доход за 30 дней
    int Count;                  //Итоговое колиество сдачи в аренду

    public:
    void setCustomer(int value){
        Customer = value;
    }
    int getCustomer(){
        return Customer;
    }
    void setPenaltyRate(int value){
        PenaltyRate = value;
    }
    int getPenaltyRate(){
        return PenaltyRate;
    }
    int getMilleageMonth(){
        return MilleageMonth;
    }
    void setCount(int value){
        Count= value;
    }
    int getCount(){
        return Count;
    }
    int getReturnDate(){
        return  ReturnDate;
    }
    void setRentalHourReturn(int value){
        RentalHourReturn = value;
    }
    int getRentalHourReturn(){
        return RentalHourReturn;
    }
    int getCostOfMonth(){
        return CostOfMonth;
    }
    int getCostOf(){
        return CostOf;
    }
    void setReturnDate(int value){
        ReturnDate = value;
    }
    void setLeaseTerm (int value){
         LeaseTerm = value;
    }
    int getStatus(){
        return Status;
    }
    void setMilleageRental(int value){
        MilleageRental = value;
    }
    int getMilleageRental(){
        return MilleageRental;
    }
    void setMilleageMonth (int value){
        MilleageMonth = value;
    }
    void setRentalHour (int value){
        RentalHour = value;
    }
    void setRentalMonth (int value){
        RentalMonth = value;
    }
    void setStatus (int value){
        Status = value;
    }
    void setCostOf (int value){
        CostOf  = value;
    }
    void setCostOfMonth (int value){
        CostOfMonth = value;
    }
    void setsecond (int value){
        second  = value;
    }
    void setRentalMinute (int value){
        RentalMinute = value;
    }
    void setRentalDay (int value){
        RentalDay = value;
    }
    string getBrand(){
        return Brand;
    }
    string getType(){
        return Type;
    }
    string getModel(){
        return Model;
    }
    int getYearOfManufacture(){
        return YearOfManufacture;
    }
    string getColor(){
        return Color;
    }
    string getNumber(){
        return Number;
    }
    int getMilleage(){
        return Milleage;
    }
    void setMilleage(int value){
        Milleage = value;
    }
    int getRental_price(){
        return Rental_price;
    }

    friend ostream& operator<<(ostream& os,  Vehicle& dt){
        os
                <<"Клиет " <<dt.getCustomer()
                <<" Тип ТС: "<<dt.getType()
                <<" Модель: "<<dt.getModel()
                <<" Брэнд: "<<dt.getBrand()
                <<" Год выуска: "<<dt.getYearOfManufacture()
                <<" Гос номер: "<<dt.getNumber()
                <<" Пробег ТС: "<<dt.getMilleage()
                <<" Стоимость Аренды: "<<dt.getCostOf()
                <<" Цвет: "<<dt.getColor()
                <<" Дата возврата (день): "<<dt.getReturnDate()
                <<" Пробег за время аренды: "<<dt.getMilleageRental()
                <<" Штраф: "<<dt.getPenaltyRate()
                <<"\n";
        return os;
    }
};
#endif //CARRENTAL_CAR_H
