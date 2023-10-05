#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141;
const double R = 8.314;
const double ALPHA = 1.1;
const double g = 9.81;

const double t = 45; // Температура в °C
const double velocity = 1.5; // Скорость
const double D = 1.1; // Диаметр витка
const double n = 24; // Число витков
const double h = 0.12; // Шаг витка
const double d_outer = 56 * pow(10, -3); // Диаметр внутренний в метрах
const double delta = 3.5 * pow(10, -3); // Диаметр внешний в метрах
const double delta_P1 = 1.5 * 98066.5; // Избыточное давление

// Вода, незначительная коррозия
const double e = 0.2 * pow(10, -3); // Абсолютная шероховатость
const double p = 990.21; // Плотность
const double mu =  0.5963 * pow(10, -3); // Вязкость

const double E_enter = 0.2;

// Высота змеевика
double get_H() {
    return n * h;
}

// Длина змеевика
double get_L() {
    return n * sqrt(pow((PI * D), 2) + pow(h, 2));
}

// Эквивалентный диаметр трубы круглого сечения
double get_d_eq() {
    return d_outer - 2 * delta;
}

// Критерий Рейнольдса
double get_Re() {
    return velocity * get_d_eq() * p / mu;
}

// Относительная шероховатость
double get_E() {
    return e / get_d_eq();
}

// Коэффициент гидравлического трения (коэффициент Дарси) для прямой трубы
double get_Darcy_factor() {
    return pow(2 * log10((get_E() / 3.7) + pow(6.81 / get_Re(), 0.9)), -2);
}

//Коэффициент гидравлического трения (коэффициент Дарси) для змеевика
double get_Darcy_factor_coil() {
    return get_Darcy_factor() * (1 + 3.54 * get_d_eq() / D);
}

double get_delta_P_general() {
    return (ALPHA + get_Darcy_factor_coil() * get_L() / get_d_eq() + E_enter) * p * pow(velocity, 2) / 2;
}

double get_delta_P_H() {
    return p * g * get_H();
}

double get_delta_P2() {
    return delta_P1 - get_delta_P_H() - get_delta_P_general();
}

int main() {
    cout << get_delta_P2()* 0.00001019716212978 << endl;
    //* 0.00001019716212978;

    return 0;
}