#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141;
const double R = 8.314;
const double ALPHA = 1.1;
const double g = 9.81;

const double t = 50; // Температура в °C
const double m = 47 * 1000 / 3600; // Массовый расход жидкости кг/с
const double d_outer = 25 * pow(10, -3); // Диаметр внутренний в метрах
const double delta = 2 * pow(10, -3); // Диаметр внешний в метрах
const double L = 6; // Длинна труб в метрах
const double N = 404; // Число труб
const double k = 4; // Число ходов теплообменника по трубному пространству

// Циклогексан, незначительная коррозия
const double e = 0.2 * pow(10, -3); // Абсолютная шероховатость
const double p = 749.9; // Плотность
const double mu =  0.608 * pow(10, -3); // Вязкость

// Кожухотрубный комментарий к-ф сопротивления
const double E_enter = 1.5;
const double E_enter_tube = 1.0;
const double E_exit_tube = 1.0;
const double E_turn = 2.5;
const double E_exit = 1.5;

// Объёмный расход жидкости
double get_v() {
    return m / p;
}

// Эквивалентный диаметр трубы круглого сечения
double get_d_eq() {
    return d_outer - 2 * delta;
}

// Площадь сечения трубного пространства теплообменника
double get_section() {
    return (N / k) * PI * pow(get_d_eq(), 2) / 4;
}

// Скорость жидкости
double get_velocity() {
    return get_v() / get_section();
}

// Критерий Рейнольдса
double get_Re() {
    return get_velocity() * get_d_eq() * p / mu;
}

// Относительная шероховатость
double get_E() {
    return e / get_d_eq();
}

// Коэффициент гидравлического трения (коэффициент Дарси)
double get_Darcy_factor() {
    return pow(2 * log10((get_E() / 3.7) + pow(6.81 / get_Re(), 0.9)), -2);
}

// Потери давления на трение
double get_delta_P_lose() {
    return get_Darcy_factor() * L * k * p * pow(get_velocity(), 2) / (get_d_eq() * 2);
}

// Местные сопротивления кожухотрубчатого теплообменника
double get_E_sum() {
    return E_enter + E_enter_tube * k + E_exit_tube * k + E_turn * (k - 1) + E_exit;
}

// Потери давления на местные сопротивления
double get_delta_P_velocity() {
    return get_E_sum() * (p * pow(get_velocity(), 2) / 2);
}

// Общие потери давления
double get_delta_P_general() {
    return get_delta_P_lose() + get_delta_P_velocity();
}

double get_h_lose() {
    return get_delta_P_general() / (p * g);
}

int main() {
    cout << get_h_lose() << endl;

    return 0;
}