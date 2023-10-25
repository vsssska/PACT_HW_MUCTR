#include <iostream>
#include <cmath>

using namespace std;

const double Pi = 3.142;
const double g = 9.81;
const double alph = 1.1;

const double t = 50.0; // Temperatura
const double m = 58.7 * (1000.0/3600.0); // massoviy rashod
const double pressure_tank = 4.2 * 98066.5; // Давление в напорном баке кгс/см2 в ПА
const double atm_pressure = 747.0 * 133.3; // Атмосферное давление
const double n = 2900.0; // Кол-во оборотов
const double p_zvezdochka = 1.0 * 133.3; // Давление насыщеного пара

// Стальной трубопровод с незначительной коррозией
const double e = 0.2; // Абсолютная шероховатость

const double dVs = (133 - (4 * 2)) / 1000.0; // Внутренний Всасывающий трубопровод m
const double lVs = 27.0; // Длина всасывающего трубопровода

const double dNg = (108 - (4 * 2)) / 1000.0; // Внутренний Нагнетательный трубопровод m
const double lNg = 75.0; // Длина нагнетательного трубопровода

const double sumVs = 6.0; // Сумма местных сопротивлений Всасывающего трубопровода
const double sumNg = 41.5; // Сумма местных сопротивлений Нагнетательного трубопровода

const double H = 42; // Высота напорного бака

// Нитробензол
const double p = 1174.0; // Плотность
const double u = 1.251; // Вязкость

// Объемный расход жидкости
double V(){
    return m/p;
}

// Площадь сечения
double S(double d){
    return Pi * (pow(d, 2) / 4);
}

// Скорость жидкости
double velocity(double s){
    return V() / s;
}

// Критерий Рейнольдса
double get_Re(double vel, double dvn) {
    return (vel * dvn * p) / (u * pow(10, -3.0));
}

// Относительная шероховатость
double relative_e(double dvn){
    return e / (dvn * 1000);
}

// Коэффициент гидравлического трения (коэффициент Дарси)
double get_Darcy_factor(double rel_e, double re_cef) {
    return pow(2 * log10((rel_e / 3.7) + pow(6.81 / re_cef, 0.9)), -2);
}

// Потери давления по длине трубопровода
double hn(double darcy, double l, double v, double d, double sum){
    return (alph + (darcy * (l / d)) + sum) * ( (pow(v, 2)) / (2 * g) );
}

// Гослинг
double Ngs(double hh){
    return V() * p * g * hh;
}


int main(){

    cout << "====================== 1 ====================" << endl;

    double sVs = S(dVs); // Площадь сечения всасывающего насоса
    double sNg = S(dNg); // Площадь сечения нагнетающего насоса

    double vVs = velocity(sVs); // Скорость жидкости всасывающего насоса
    double vNg = velocity(sNg); // Скорость жидкости нагнетающего насоса

    double realtive_eVs = relative_e(dVs); // Относительная шероховатость всасывающего насоса
    double realtive_eNg = relative_e(dNg); // Относительная шероховатость нагнетающего насоса

    double ReVs = get_Re(vVs, dVs); // Критерий Рейнольдса всасывающего насоса
    double ReNg = get_Re(vNg, dNg); // Критерий Рейнольдса нагнетающего насоса

    double cef_darVs = get_Darcy_factor(realtive_eVs, ReVs); // Коэф дарси всасывающего насоса
    double cef_darNg = get_Darcy_factor(realtive_eNg, ReNg); // Коэф дарси нагнетающего насоса

    double hVs = hn(cef_darVs, lVs, vVs, dVs, sumVs); // Потери напора всасывающего насоса
    double hNg = hn(cef_darNg, lNg, vNg, dNg, sumNg); // Потери напора нагнетающего насоса
    double hall = hVs + hNg; // Потери напора на трение общие
    
    cout << "Скорость жидкости всасывающего насоса: " << vVs << endl
    << "Скорость жидкости нагнетающего насоса: " << vNg << endl
    << "Коэф дарси всасывающего насоса: " << cef_darVs << endl
    << "Коэф дарси нагнетающего насоса: " << cef_darNg << endl
    << "Потери напора на трение всасывающего насоса: " << hVs << endl
    << "Потери напора на трение нагнетающего насоса: " << hNg << endl
    << "Потери напора на трение общие: " << hall << endl;

    cout << "====================== 2 ====================" << endl;

    double p1 = atm_pressure;
    double p2 = pressure_tank;
    // Необходимый напор насоса 
    double Hs = ((p2 - p1) / (p * g)) + H + hall + (alph * ( (pow(vNg, 2) - pow(vVs, 2)) / (2 * g)));
    cout << "Общий расход: " << V() * 1000 << "л/с " << V() * 1000 * 3.6 << "м3/ч" << endl
    << "Необходимый напор насоса: " << Hs << endl;

    cout << "====================== 3 ====================" << endl;

    double hkav = 0.00125 * pow((V() * pow(n, 2)), 2.0/3.0); // Запас напора на кавитацию
    double Hmax = ((p1 - p_zvezdochka)/(p * g)) - (pow(vVs, 2)/(2 * g)) - hVs - hkav; // Максимальная высота всасывающей линии
    cout << "Запас напора на кавитацию: " << hkav << endl
    << "Максимальная высота всасывающей линии: " << Hmax << endl;

    cout << "====================== 4 ====================" << endl;
    double Hh = 82.5;
    cout << "Марка насоса: K80-50-250" << endl 
    << "Высота Hh: " << Hh << endl;

    cout << "====================== 5 ====================" << endl;

    double ngs = Ngs(Hh); // Гослинг
    double efficiency = 64.9; // КПД
    double Nvn = ngs / (efficiency / 100.0); // Расч. Мощность насоса по мощности гидравлической сети
    double NvnRef = 17.99 * 1000; // Справ. Мощность насоса по мощности гидравлической сети

    cout << "Nгс: " << ngs << endl
    << "КПД: " << efficiency << endl
    << "Расч. Мощность насоса по мощности гидравлической сети: " << Nvn << endl
    << "Справ. Мощность насоса по мощности гидравлической сети: " << NvnRef << endl;



    return 0;
}