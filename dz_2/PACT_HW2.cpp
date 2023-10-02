#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

const double PI = 3.1416;
const double R = 8.314;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	//Сероуглерод
	double diametr1 = (57 - (3.5 * 2)) * pow(10, -3);	// mm диаметр трубы с жидкостью
	double mass_consumption = (13.4 * 1000) / 3600;		// массовый расход tonn/hour в kg/s
	double temperature_liquid = 40;						// Celsius температура жидкости
	double density_liquid = 783.7;						// Плотность в-ва при 20 градусах
	double molyar_mass = 60.096;						// Молярная масса в-ва

	double atm = 760 * 0.000133;			// (атмосферное давление) мм рт. ст. в МПА

	double boiling_point = 97.2;			// Celsius температура кипения жидкости
	double boiling_min = 90;				
	double density_min = 76.37;				// Давление насыщ. пара над орг. жидкостью
	double boiling_max = 100;
	double density_max = 112.5;


	// 1 Задание
	double V_liquid = mass_consumption / density_liquid;
	double U_liquid = V_liquid / ((PI * pow((diametr1), 2)) / 4);
	cout << "1 Задание" << endl
		<< "pl = " << density_liquid << endl
		<< "Vl = " << U_liquid << endl;

	// 2 Задание
	cout << "2 Задание" << endl
		<< "atm= " << atm * pow(10, 6) << " ПА" << endl;

	double P_boiling = 102.3836 * pow(10, -3);	// Давление при температуре кипения (интерполяция в ручную)
	//cout << "Pgas= " << P_boiling << " МПА" << endl;
	
	double Vg_op = (25 + 15) / 2; // Подбор значений исходя от atm(ПА)
	cout << "Vg_op= " << Vg_op << endl;

	double density_gas = (P_boiling * molyar_mass) / (R * (boiling_point + 273.15)); // г/cм3
	density_gas = density_gas * pow(10, 3); // кг/м3
	cout << "pG= " << density_gas << " кг/м3" << endl;

	double V_gas = mass_consumption / density_gas;
	double S_gas = V_gas / Vg_op;
	double d_gas = sqrt((4 * S_gas) / PI);
	cout << "diam= " << d_gas << " " << endl;

	d_gas = (377 - (2 * 10)) * pow(10, -3); // Подбор диаметра в ручную
	double u_gas = V_gas / ((PI * pow(d_gas, 2)) / (4));
	cout << "Vg= " << u_gas << " м/с" << endl;

	// 3 Задание
	mass_consumption = mass_consumption * 3;
	V_liquid = mass_consumption / density_liquid;
	cout << "3 Задание" << endl;
	double Vl_op = (1.5 + 3) / 2; // Подбор ХЗ по какому признаку
	double S_liquid = (V_liquid) / (Vl_op);
	double d_liq = sqrt((4 * S_liquid) / PI);

	cout << "Vl_op= " << Vl_op << endl
		<< "d_liq= " << d_liq << endl;

	d_liq = (108 - (2 * 4)) * pow(10, -3); // Подбор диаметра в ручную
	double u_liq = V_liquid / ((PI * pow(d_liq, 2)) / (4));
	cout << "Vl= " << u_liq << "м/с" << endl;
	
}
