#include "pch.h"
#include "Car.h"
#include "Vehicle.h"
#include "Motorcycle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
using namespace std;
int main()
{
	
	setlocale(LC_ALL, "Russian");
    cout << "Hello World!\n"; 
	vector<string> Cars;
	ifstream fin;
	fin.open("Cars.txt", fstream::in);
	vector<Vehicle> CreateVehicle
	{
		vector<Vehicle> VhicleOfFull;
		if(fin.is_open()) 
		{
		int arr[7];
		string str;
		while (!fin.eof()) 
		{
			getline(fin,str);
			separation(str,arr);
			StationOfFuel.push_back(GasStation(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]));
		}
	}

	}









	/*
	//Чтение из файла в вектор автомобмль
	while (fin.get(ch))
	{
		Cars.push_back(ch);
	}
	fin.close();
	ifstream Zin("Motorcycle1.txt");
	//Чтение из файла в вектор мотоцикл
	while (Zin.get(ch1))
	{
		Motorcycle.push_back(ch1);
	}
	Zin.close();
	//Запись результатов в файл автомобиль
	ofstream fout("Result_Cars.txt");
	for (unsigned int i=0 ; i< Cars.size(); i++)
	{
		fout << Cars[i];
	}
	fout.close();
	//Запись результатов в файл мотоцикл
	ofstream Zout("Result_Motorcycle.txt");
	for (unsigned int i=0; i < Motorcycle.size(); i++)
	{
		Zout << Motorcycle[i];
	}
	Zout.close();
	for (vector<char>::iterator iter = Cars.begin(); iter != Cars.end(); ++iter)
	{

	};
	auto iter = Cars.begin();//Получаем итератор
	while (iter != Cars.end())
	{
		cout << *iter << endl;// получаем элементы через итератор
		++iter;// перемещаемся вперед на один элемент
	};*/
	system("pause");
	return 0;
}