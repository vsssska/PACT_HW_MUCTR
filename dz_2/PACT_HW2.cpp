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
	double diametr1 = (57 - (2.5 * 2)) * pow(10, -3);	// mm диаметр трубы с жидкостью
	double mass_consumption = (27.9 * 1000) / 3600;		// массовый расход tonn/hour в kg/s
	double temperature_liquid = 20;						// Celsius температура жидкости
	double density_liquid = 1263.3;						// Плотность в-ва при 20 градусах
	double molyar_mass = 76.1;							// Молярная масса в-ва

	double atm = 760 * 0.000133;			// (атмосферное давление) мм рт. ст. в МПА

	double boiling_point = 46.2;			// Celsius температура кипения жидкости
	double boiling_min = 40;
	double density_min = 82.39;
	double boiling_max = 50;
	double density_max = 114.4;


	// 1 Задание
	double V_liquid = mass_consumption / density_liquid;
	double U_liquid = V_liquid / ((PI * pow((diametr1), 2)) / 4);
	cout << "1 Задание" << endl
		<< "pl = " << density_liquid << endl
		<< "Vl = " << U_liquid << endl;

	// 2 Задание
	cout << "2 Задание" << endl
		<< "atm= " << atm * pow(10, 6) << " ПА" << endl;

	double P_boiling = 103.51 * pow(10, -3);	// Давление при температуре кипения (интерполяция в ручную)
	cout << "Pgas= " << P_boiling << " МПА" << endl;
	
	double Vg_op = (25 + 15) / 2; // Подбор значений исходя от atm(ПА)
	cout << "Vg_op= " << Vg_op << endl;

	double density_gas = (P_boiling * molyar_mass) / (R * (boiling_point + 273.15)); // г/cм3
	density_gas = density_gas * pow(10, 3); // кг/м3
	cout << "pG= " << density_gas << " кг/м3" << endl;

	double V_gas = mass_consumption / density_gas;
	double S_gas = V_gas / Vg_op;
	double d_gas = sqrt((4 * S_gas) / PI);
	cout << "diam= " << d_gas << " " << endl;

	d_gas = (426 - (2 * 11)) * pow(10, -3); // Подбор диаметра в ручную
	double u_gas = V_gas / ((PI * pow(d_gas, 2)) / (4));
	cout << "Vg= " << u_gas << " м/с" << endl;

	// 3 Задание
	mass_consumption = mass_consumption * 3;
	V_liquid = mass_consumption / density_liquid;
	cout << "3 Задание" << endl << "V_liquid= " << V_liquid << endl;
	double Vl_op = (1.5 + 3) / 2; // Подбор ХЗ по какому признаку
	double S_liquid = (V_liquid) / (Vl_op);
	double d_liq = sqrt((4 * S_liquid) / PI);

	cout << "Vl_op= " << Vl_op << endl
		<< "d_liq= " << d_liq << endl;

	d_liq = (133 - (2 * 6)) * pow(10, -3); // Подбор диаметра в ручную
	double u_liq = V_liquid / ((PI * pow(d_liq, 2)) / (4));
	cout << "Vl= " << u_liq << "м/с" << endl;
	
}
