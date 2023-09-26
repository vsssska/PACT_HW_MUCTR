#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

const int Subst_count = 3; // Колличество в-в
const double R = 8.314 * 1000; // Газовая постоянная

int main()
{
    setlocale(LC_ALL, "Russian");
    double* massa = new double [Subst_count];
    //Заполняем массив
    massa[0] = 21.0;
    massa[1] = 17.0;
    massa[2] = 9.0;

    // Общая масса
    double total_weight = 0; 
    for (int i = 0; i < Subst_count; i++)
        total_weight += massa[i];
    //
    double* molyar_massX = new double[Subst_count]; //Молярная масса
    //Заполняем массив
    molyar_massX[0] = 58.08;
    molyar_massX[1] = 60.05; 
    molyar_massX[2] = 88.11; 
    //
    double* p30 = new double[Subst_count]; //Плотность при первой температуре
    //Заполняем массив
    p30[0] = 778.8;
    p30[1] = 1039.2;
    p30[2] = 888.5;
    //
    double* v30 = new double[Subst_count]; //Вязкость при первой температуре
    //Заполняем массив
    v30[0] = 0.296;
    v30[1] = 1.04;
    v30[2] = 0.403;
    //

    double* mass_frX = new double[Subst_count]; //Массовые доли
    double* mol_frX = new double[Subst_count]; //Мольные доли

    //Расчет массовых долей
    for (int i = 0; i < Subst_count; i++)
        mass_frX[i] = massa[i] / total_weight;

    //Знаменатель для пересчета массовых долей в мольные
    double denominator_mass_frX = 0;
    for (int i = 0; i < Subst_count; i++)
        denominator_mass_frX += mass_frX[i] / molyar_massX[i];

    //Пересчет массовых долей в мольные
    for (int i = 0; i < Subst_count; i++)
        mol_frX[i] = (mass_frX[i] / molyar_massX[i]) / (denominator_mass_frX);

    

    //
    // 1 Задание
    // 
    //Расчет плотности жидкой смеси
    double density_liquid = 0;
    double denominator_density_liquid = 0;
    for (int i = 0; i < Subst_count; i++)
        denominator_density_liquid += mass_frX[i] / p30[i];
    density_liquid = 1 / denominator_density_liquid;
    cout << "Плотность жидкой смеси: " << density_liquid << endl;

    //Расчет вязкости жидкой смеси
    double viscosity_liquid = 0;
    double degree_viscosity_liquid = 0;
    for (int i = 0; i < Subst_count; i++)
        degree_viscosity_liquid += mol_frX[i] * log10(v30[i]);
    viscosity_liquid = pow(10, degree_viscosity_liquid);
    cout << "Вязкость жидкой смеси: " << viscosity_liquid << endl;

    //
    // 2 Задание
    //
    
    //Расчет молярной массы
    double total_molyar_mass = 0;
    for (int i = 0; i < Subst_count; i++)
        total_molyar_mass += mol_frX[i] * molyar_massX[i];

    // Расчет плотности газовой(паровой) смеси

    double pressure = 745.0 * 133.3; // Давление мм рт. ст. в ПА
    pressure = (0.25 * 98066.52) + pressure; // кгс/см^2 в ПА + атмосферное давление
    double T = 120;
    T += 273.15; // Температура в Кельвинах

    double density_gas = (total_molyar_mass * pressure) / (R * T);
    cout << "Давление: " << pressure << " ПА" << endl;
    cout << "Плотность газовой(паровой) смеси: " << density_gas << endl;
    
    // Расчет вязкости газовой(паровой) смеси

    double* v120 = new double[Subst_count]; // Вязкость при 120 градусах
    //
    v120[0] = 0.149;
    v120[1] = 0.388;
    v120[2] = 0.178;
    //
    
    double viscosity_gas = 0;
    double denominator_viscosity_gas = 0;
    for (int i = 0; i < Subst_count; i++)
        denominator_viscosity_gas += (mol_frX[i] * molyar_massX[i]) / v120[i];
    viscosity_gas = total_molyar_mass / denominator_viscosity_gas;
    cout << "Вязкость газовой(паровой) смеси: " << viscosity_gas << endl;

}

