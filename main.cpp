#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstring>
#include <ctime>
#include <tuple>
#include <cstdlib>
#include "Vehicle.h"
#include "Motorcycle.h"
/*---------------------------------------------------------------------------------------------------*/
#include <cstdint>
#include <chrono>
#include <random>
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
namespace detail{
    static std::default_random_engine rnd(
            static_cast<uint32_t>(
                    std::chrono::system_clock::now().time_since_epoch().count()
            )
    );
}//namespace detail
inline uint32_t Random(uint32_t minvalue, uint32_t maxvalue)
{
    using std::swap;
    if(minvalue > maxvalue)
        swap(minvalue, maxvalue);

    return detail::rnd() % (maxvalue - minvalue + 1) + minvalue;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
/*-------------------------------------------------------------------------------------------------------------*/
const static string PATH_TO_VEHICLE = "E://Vehicle.txt";
const static string PATH_TO_MODEL_VEHICLE = "E://model.txt";
const static int COUNT_OF_PARAMETERS = 8;


void writeCars(vector<Cars> CarsFilling, int i);                   //Пеать результатов по автомобилям
void writeMotorcycle(vector<Motorcycle> MotorcycleFilling,int i);       //Печать результатов по мотоциклам
void writeTC();                                                        // Печать разделителя
void writeTCIn();                                                       // Печать данных о принятом заказе
int positionOfSeparator(string str);                        //определяет в каких местах необходимо делать разделения в строке
void separation(string str, int arr[],string arrStr);       //Делит строку на массив чисел согласно positionOfSeparator.
std::tuple<vector<Cars>,vector<Motorcycle>>CreateVehicle(); // tuple необходим для того чтобы полуить из функции 2 аргумента. Создаёт объекты Car, Motorcycle.
int MaxMilleageCars(vector<Cars>CarsFilling);                   //Определение автомобиля  с наибольшим проьбегом за месяц
int MaxMilleageMotorcycle(vector<Motorcycle>MotorcycleFilling);  //Определение мотоциклам  с наибольшим проьбегом за месяц
int AllCostOfMonthMotorcycle(vector<Motorcycle>MotorcycleFilling);//Итоговый доход по мотоциклам
int AllCostOfMonthCars(vector<Cars>CarsFilling);                   //Итоговый доход по автомобилям

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Hello, World!" << std::endl;
    auto [CarsFilling,MotorcycleFilling] = CreateVehicle();
    int flag = 0;
    int month = 1;
    int i = 0;
    int CountCustomer = 1;
    while (month < 2){
        int day = 1;
        while (day < 31){
            fstream fs;
            fs.open(PATH_TO_MODEL_VEHICLE, fstream::app);
            if(fs.is_open()) {
                fs <<"*****************************************************************************************************************" << "\n";
                fs <<"*                                     " << "New day : "<< " day "<< day << " month " << month << " hour " << 1  <<"                                           *" << "\n";
                fs <<"*****************************************************************************************************************" << "\n";
            }
            fs.close();
            i= 0;
            while (i < CarsFilling.size()) {
                if (CarsFilling[i].getStatus() == 1 and CarsFilling[i].getReturnDate() == day) {
                    srand(time(0));
                    int randnum = rand() % 10000;
                    if (randnum != 20) {//Вероятность того что клиет не вернёт ТС вовремя
                        CarsFilling[i].setStatus(0);
                        /*Вставить изменения и оправить на пеать*/
                        srand(time(0));
                        int MilleageCar = 20 + rand() % 500;//Сколько миль проехало ТС
                        CarsFilling[i].setMilleageRental(MilleageCar);//Установка сколько миль роехал клиент
                        CarsFilling[i].setMilleageMonth(CarsFilling[i].getMilleageMonth() + MilleageCar);// Заись в коилку 30 дневную
                        CarsFilling[i].setMilleage(CarsFilling[i].getMilleage() + MilleageCar);// Обновление миль автомобиля
                        CarsFilling[i].setReturnDate(0);
                        CarsFilling[i].setCostOfMonth(CarsFilling[i].getCostOf()+ CarsFilling[i].getCostOfMonth() + CarsFilling[i].getPenaltyRate());//Подсчёт доходов за месяц
                        writeTCIn();
                        writeCars(CarsFilling, i);
                        CarsFilling[i].setCustomer(0);
                        CarsFilling[i].setPenaltyRate(0); // обнуляем штраф
                    }
                    else {
                        srand(time(0));
                        int randnum = 1 + rand() % 3;//На сколько дней опоздает арендатор
                        CarsFilling[i].setReturnDate(CarsFilling[i].getReturnDate() + randnum);
                        CarsFilling[i].setPenaltyRate(CarsFilling[i].getRental_price() * 2 * randnum);
                    }
                }
                i++;
            }
            for (int hour = 1; hour < 25; hour++){
                if (flag == 0){ //При первом запуске устанавливает что все ТС доступны к сдачи в аренду
                    int i =0;
                    while (i<CarsFilling.size()){
                        CarsFilling[i].setStatus(0);
                        CarsFilling[i].setCount(0);
                        CarsFilling[i].setMilleageRental(0);
                        CarsFilling[i].setMilleageMonth(0);
                        CarsFilling[i].setCustomer(0);
                        i++;
                    }
                    i=0;
                    while (i< MotorcycleFilling.size()){
                        MotorcycleFilling[i].setStatus(0);
                        MotorcycleFilling[i].setCount(0);
                        MotorcycleFilling[i].setMilleageMonth(0);
                        MotorcycleFilling[i].setMilleageRental(0);
                        MotorcycleFilling[i].setCustomer(0);
                        i++;
                    }
                    flag++;
                }
                i=0;
                while (i<MotorcycleFilling.size()) {
                    if (MotorcycleFilling[i].getStatus() == 1 and MotorcycleFilling[i].getReturnDate() == day and MotorcycleFilling[i].getRentalHourReturn() == hour) {
                        int randnum = Random(1,10000);
                        if (randnum != 20) {//Вероятность того что клиет не вернёт ТС вовремя
                            MotorcycleFilling[i].setStatus(0);
                            srand(time(0));
                            int MilleageMotorcycle = 20 + rand() % 600;
                            MotorcycleFilling[i].setMilleageRental(MilleageMotorcycle);
                            MotorcycleFilling[i].setMilleageMonth(MotorcycleFilling[i].getMilleageMonth() + MilleageMotorcycle);
                            MotorcycleFilling[i].setMilleage(MotorcycleFilling[i].getMilleage() + MilleageMotorcycle);
                            MotorcycleFilling[i].setCostOfMonth(MotorcycleFilling[i].getCostOf() + MotorcycleFilling[i].getCostOfMonth() + MotorcycleFilling[i].getPenaltyRate());
                            writeTCIn();
                            writeMotorcycle(MotorcycleFilling, i);
                            MotorcycleFilling[i].setPenaltyRate(0);
                            MotorcycleFilling[i].setCustomer(0);
                        } else {
                            int randnum = Random(1,24);// На сколько клиент опоздает
                            MotorcycleFilling[i].setPenaltyRate(MotorcycleFilling[i].getRental_price() * 2 * randnum);
                            int clock = MotorcycleFilling[i].getRentalHourReturn() + randnum;
                            int clockday;
                            if (clock > 24) {
                                clockday = clock / 24;
                                clock = Random(1,24);
                                MotorcycleFilling[i].setReturnDate(clockday);
                                MotorcycleFilling[i].setRentalHourReturn(clock);
                            } else {
                                MotorcycleFilling[i].setRentalHourReturn(clock);
                            }
                        }
                    }
                    i++;
                }
                for (int minute = 0; minute< 60; minute++) {
                    int rrr = Random(0, 1000);
                    if (rrr == 25) {//Вероятность что клиент придёт
                        rrr = Random(0, 1);
                        if (rrr == 0) {
                            rrr = CarsFilling.size() - 1;
                            int ChoiceCar = Random(0, rrr);//Выбор автомобиля какой автомобиль взять
                            //cout << "\n" << "Choice avto" << ChoiceCar << "\n";
                            if (CarsFilling[ChoiceCar].getStatus() != 1) {
                                int LeaseTerm = Random(1, 7);// Выбор колиества дней аренды
                                CarsFilling[ChoiceCar].setCustomer(CountCustomer);
                                CountCustomer++;
                                CarsFilling[ChoiceCar].setLeaseTerm(LeaseTerm);
                                CarsFilling[ChoiceCar].setStatus(1);
                                CarsFilling[ChoiceCar].setRentalMinute(minute);
                                CarsFilling[ChoiceCar].setRentalHour(hour);
                                CarsFilling[ChoiceCar].setRentalDay(day);
                                CarsFilling[ChoiceCar].setRentalMonth(month);
                                CarsFilling[ChoiceCar].setReturnDate(
                                        LeaseTerm + day);// расчёт даты возврата, в данном слуае только день
                                CarsFilling[ChoiceCar].setCostOf(LeaseTerm *
                                                                 CarsFilling[ChoiceCar].getRental_price());// расчёт стоимости аренды, сумма которую клиент должен выложить
                                CarsFilling[ChoiceCar].setCount(CarsFilling[ChoiceCar].getCount() +
                                                                1);// счётччик, сколько раз автомобиль был в рокате
                                writeTC();
                                writeCars(CarsFilling, ChoiceCar);
                            }
                        } else {
                            rrr = MotorcycleFilling.size() - 1;
                            int ChoiceMotorcycle = Random(0, rrr);//Выбор мотоцикла
                            //cout << "\n" << "Choice moto" << ChoiceMotorcycle << "\n";
                            if (MotorcycleFilling[ChoiceMotorcycle].getStatus() != 1) {
                                int LeaseTerm = Random(1, 48);// На сколько часов оформлять аренду, не более 48 часов
                                MotorcycleFilling[ChoiceMotorcycle].setCustomer(CountCustomer);
                                CountCustomer++;
                                MotorcycleFilling[ChoiceMotorcycle].setLeaseTerm(LeaseTerm);
                                MotorcycleFilling[ChoiceMotorcycle].setStatus(1);
                                MotorcycleFilling[ChoiceMotorcycle].setRentalMinute(minute);
                                MotorcycleFilling[ChoiceMotorcycle].setRentalHour(hour);
                                MotorcycleFilling[ChoiceMotorcycle].setRentalDay(day);
                                MotorcycleFilling[ChoiceMotorcycle].setRentalMonth(month);

                                MotorcycleFilling[ChoiceMotorcycle].setCount(
                                        MotorcycleFilling[ChoiceMotorcycle].getCount() +
                                        1);//счётчик, сколько раз брали этот мотоцикл в прокат
                                MotorcycleFilling[ChoiceMotorcycle].setCostOf(
                                        LeaseTerm * MotorcycleFilling[ChoiceMotorcycle].getRental_price());
                                int clock = LeaseTerm + hour;
                                int clockday;
                                if (clock > 24) {
                                    clockday = clock / 24;
                                    clock = Random(1, 24);
                                    MotorcycleFilling[ChoiceMotorcycle].setReturnDate(clockday + day);
                                    MotorcycleFilling[ChoiceMotorcycle].setRentalHourReturn(clock);
                                } else {
                                    MotorcycleFilling[ChoiceMotorcycle].setReturnDate(day);
                                    MotorcycleFilling[ChoiceMotorcycle].setRentalHourReturn(clock);
                                }
                                writeTC();
                                writeMotorcycle(MotorcycleFilling, ChoiceMotorcycle);
                            }
                        }
                    }
                }
            }
        day++;
        }
        month++;
    }
    fstream fs;
    fs.open(PATH_TO_MODEL_VEHICLE, fstream::app);
    if(fs.is_open()) {
        fs <<"*****************************************************************************************************************" << "\n";
        fs <<"*                                     " <<"Итоговые показатели работы: (Автомобили)                                    *" << "\n";
        fs <<"*****************************************************************************************************************" << "\n";

            fs <<"Транспортное средство с наибольшим пробегом :" <<" Марка "<< CarsFilling[MaxMilleageCars(CarsFilling)].getBrand() <<" Модель "<< CarsFilling[MaxMilleageCars(CarsFilling)].getModel() <<" Гос Номер"<< CarsFilling[MaxMilleageCars(CarsFilling)].getNumber()<<" Пробег за месяц "<<CarsFilling[MaxMilleageCars(CarsFilling)].getMilleageMonth() <<"\n";
            fs <<"Выручка за месяц: " << AllCostOfMonthCars(CarsFilling) <<"\n";

        fs <<"*****************************************************************************************************************" << "\n";
        fs <<"*                                     " <<"Итоговые показатели работы: (Мотоциклы)                                    *" << "\n";
        fs <<"*****************************************************************************************************************" << "\n";
        i=0;

            fs <<"Транспортное средство с наибольшим пробегом :" << " Марка "<< MotorcycleFilling[MaxMilleageMotorcycle(MotorcycleFilling)].getBrand() <<" Модель "<< MotorcycleFilling[MaxMilleageMotorcycle(MotorcycleFilling)].getModel() <<" Гос номер "<< MotorcycleFilling[MaxMilleageMotorcycle(MotorcycleFilling)].getNumber() <<" Пробег за месяц" <<MotorcycleFilling[MaxMilleageMotorcycle(MotorcycleFilling)].getMilleageMonth()  <<"\n";
            fs <<"Выручка за месяц: " << AllCostOfMonthMotorcycle(MotorcycleFilling)<<"\n";

        fs <<"*****************************************************************************************************************" << "\n";
        fs <<"*                                     " <<"Итоговые показатели по ТС (Сколько раз брали в аренду каждое ТС)                                    *" << "\n";
        fs <<"*****************************************************************************************************************" << "\n";
        i=0;
        while (i<CarsFilling.size()) {
            fs << "Марка " <<CarsFilling[i].getBrand() <<" Модель "<< CarsFilling[i].getModel() << " Гос Номер " << CarsFilling[i].getNumber()<< " Раз в аренде " <<CarsFilling[i].getCount() <<"\n";
            i++;
        }
        while (i<MotorcycleFilling.size()) {
            fs << "Марка " <<MotorcycleFilling[i].getBrand() <<" Модель "<< MotorcycleFilling[i].getModel() << " Гос Номер " << MotorcycleFilling[i].getNumber()<< " Раз в аренде " <<MotorcycleFilling[i].getCount() <<"\n";
            i++;
        }
    }
    fs.close();
    return 0;
}
/*Считывание данных из файла и заись в вектор*/
int MaxMilleageCars(vector<Cars>CarsFilling){
    int i = 0;
    int max = 0;
    int test;
    while (i < CarsFilling.size()){
        if (CarsFilling[i].getMilleageMonth()>max) {
            max = CarsFilling[i].getMilleageMonth();
            test = i;
        }
        i++;
    }
    return test;
}
int AllCostOfMonthCars(vector<Cars>CarsFilling){
    int i =0;
    int Summ = 0;
    while (i<CarsFilling.size()){
        Summ = CarsFilling[i].getCostOfMonth()+ Summ;
        i++;
    }
    return Summ;
}
int AllCostOfMonthMotorcycle(vector<Motorcycle>MotorcycleFilling){
    int i =0;
    int Summ = 0;
    while (i<MotorcycleFilling.size()){
        Summ = MotorcycleFilling[i].getCostOfMonth()+ Summ;
        i++;
    }
    return Summ;
}
int MaxMilleageMotorcycle(vector<Motorcycle>MotorcycleFilling){
    int i = 0;
    int max = 0;
    int test;
    while (i < MotorcycleFilling.size()){
        if (MotorcycleFilling[i].getMilleageMonth()>max) {
            max = MotorcycleFilling[i].getMilleageMonth();
            test = i;
        }
        i++;
    }
    return test;
}

int positionOfSeparator(string str){
    int i = 0;
    while (i < str.length() && str[i] != ' ') i++;
    return i;
}
void separation(string str, int arr[], string arrStr[]){
    char typecastBuffer[20];
    string  parameterOfGasStation;
    for (int j = 0; j < COUNT_OF_PARAMETERS; j++) {
        int position = positionOfSeparator(str);
        if (position != str.length()){
            parameterOfGasStation = str.substr(0, position);
            str = str.substr(position + 1, str.length());
        }
        else
            parameterOfGasStation = str.substr(0, position);
        strcpy( typecastBuffer, parameterOfGasStation.c_str() );
        if (j!= 0 and j!= 1 and j!= 2 and j!= 4 and j!= 5) {/*Проверка нужно ли приводить k int*/
            arr[j] = atoi(typecastBuffer);
        }
        else arrStr[j]= parameterOfGasStation.c_str();
    }
}
std::tuple<vector<Cars>,vector<Motorcycle>>CreateVehicle(){
    vector<Cars> CarsFilling;
    vector<Motorcycle> MotorcycleFilling;
    fstream fin;
    fin.open(PATH_TO_VEHICLE,fstream::in);
    if(fin.is_open()){
        int arr[8];
        string arrStr[8];
        string str;
        while(!fin.eof()){
            getline(fin,str);
            separation(str,arr,arrStr);
            if (arrStr[0] == "Car")
                CarsFilling.push_back(Cars(arrStr[0],arrStr[1], arrStr[2], arr[3], arrStr[4], arrStr[5], arr[6], arr[7]));
            else
                MotorcycleFilling.push_back(Motorcycle(arrStr[0],arrStr[1], arrStr[2], arr[3], arrStr[4], arrStr[5], arr[6], arr[7]));
        }
    }
    fin.close();
    return {CarsFilling,MotorcycleFilling};
}
/*Считывание данных из файла и заись в вектор*/
/*Печать результатов моделирования*/
void writeCars(vector<Cars> CarsFilling,int i){
    fstream fs;
    fs.open(PATH_TO_MODEL_VEHICLE, fstream::app);
    if(fs.is_open())
        fs << CarsFilling[i];
    fs.close();
}
void writeMotorcycle(vector<Motorcycle> MotorcycleFilling, int i){
    fstream fs;
    fs.open(PATH_TO_MODEL_VEHICLE, fstream::app);
    if(fs.is_open()) {
        fs << MotorcycleFilling[i];
    }
    fs.close();
}
void writeTC(){
    fstream fs;
    fs.open(PATH_TO_MODEL_VEHICLE, fstream::app);
    if(fs.is_open()) {
        fs << "\nVehicle was leased: "<<"\n" ;
    }
    fs.close();
}
void writeTCIn(){
    fstream fs;
    fs.open(PATH_TO_MODEL_VEHICLE, fstream::app);
    if(fs.is_open()) {
        fs << "\nThe arrival of the vehicle: "<< "\n";
    }
    fs.close();
}
/*Печать результатов моделирования**/