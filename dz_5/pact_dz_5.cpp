#include <iostream>
#include <cmath>

using namespace std; 

double m = 8.0 * 1000.0 / 3600.0;
double t1n = 169.0;
double t1k = 57.0;
double t2n = 23.0;
double t2k = 27.0;
double del_p = 0.07; // 7%

double del_ts = t1n - t2k;
double del_tu = t1k - t2n;
double del_tsr = (del_ts - del_tu) / (log(del_ts/del_tu));

double sig_t1 = t1n - t1k;
double sig_t2 = t2n - t2k;

double A = sqrt( pow(sig_t1, 2) + pow(sig_t2, 2));
double B = t1n + t1k - t2n - t2k;

double t2sr = (t2n + t2k) / 2.0;

double t1sr_ar = (t1n + t1k) / 2.0;
double t1sr = t2sr + del_tsr;

// !!!! ищем в методичке C1(в-во) и C2(вода). для воды 6-9, для в-ва 32-33 !!!!
double c1 = 1712.7;
double c2 = 4179.5;  

double Q1 = m * c1 * (t1n - t1k) / 1000.0;
double Q2 = Q1 * (1 - del_p);
double Qp = del_p * Q1;

double m2 = Q2 / (c2 * (t2k - t2n));

// Надо кароч смотреть как происходит охлаждение
// от пара к жидкости
// от жидкости к жидкости (там 2 варика есть, лучше искать в семинаре 11)
double Kop = 195.0;



int main()
{
    del_tsr = A / (log((B+A)/(B-A)));
    double t2sr_ar = (t2n + t2k) / 2.0;
    double Aop = Q2 / (Kop * del_tsr) * 1000.0;

    cout << "t1 ср ар " << t1sr_ar << endl;
    cout << "t2 ср ар " << t2sr_ar << endl;
    cout << "!!!ищем в методичке C1(в-во по t1ср) и C2(вода по t2ср). для воды 6-9, для в-ва 32-33!!!" << endl;

    cout << "Q1: " << Q1 << endl
    << "Q2: " << Q2 << endl
    << "Qп: " << Qp << endl
    << "del_tsr: " << del_tsr << endl
    << "t1sr: " << t1sr << endl
    << "t2sr: " << t2sr << endl
    << "Kop: " << Kop << endl
    << "Aop: " << Aop << endl;


    return 0;
}

