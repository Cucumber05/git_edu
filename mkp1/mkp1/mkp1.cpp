#include <iostream>
#include <cmath>
#include <fstream>

#define ra 12739.0 //радиус-вектор апоцентра
#define rp 2639.0 //радиус-вектор перицентра
#define GP 4880.0 //гравитационный параметр
#define T 43200.0 //период обращения ка (в секундах)
#define Mpl 0.33 //масса центрального тела(планеты)
#define PI 3.14159265359 
#define EPS 0.00001
double Iter(double M, double e);
double Gold(double M, double e);
double Half(double M, double e);
double IsaacNewton(double M, double e);

int main()
{
    //ищем а и е:
    double a = (ra + rp) / 2; //большая полуось орбиты
    double e = (ra - rp) / (2 * a); //эксцентриситет орбиты
    double t = 0; //время прохождения ?перицентра
    double aa = 0, bb = 2 * PI; //интервал рассмотрения по оси ординат(аномалии)
    double siderealPeriod = sqrt(GP / pow(a, 3)); 
    double n = ((2 * PI) / T); //средняя угловая скорость 
    // найти:
    double M, E, V; //средняя, эксцентрическая, истинная аномалии, соответсвенно

    std::ofstream file;
    file.open("Data_Itr.txt");
    if (file) {
        file << "t, c\t";
        file << "M(t), рад\t";
        file << "E(t), рад\t";
        file << "Theta(t), рад\t" << std::endl;
    }
    else {
        std::cout << "Error: unabled to open file" << std::endl;
    }
    for (; t <= T; t++) {
        M = n * t;
        E = Iter(M, e); //один из 4 методов
        V = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2;
        if (V < 0) { V += 2 * PI; }           
        file << t << "\t" << M << "\t" << E << "\t" << V << std::endl;
    }
    file.close();
    std::cout << "U can find output files in directory" << std::endl;
}

double Iter(double M, double e) {
    double Ek = M, Ek1 = e * sin(Ek) + M;; //Нулевая итерация: 𝐸(0)=𝑀- Ek
    while ((abs(Ek1 - Ek) > EPS)) {
        Ek = Ek1;
        Ek1 = e * sin(Ek) + M;
    }
    return Ek1;
 
}

double Gold(double M, double e) {
    double hi = ((sqrt(5) + 1) / 2), a = M-5.0, b = M+5.0, c, d, fc, fd;
    do {
        c = a + (b - a) / hi;
        fc = (c - e * sin(c) - M);
        if ((a - e * sin(a) - M) * (fc) < 0)
            b = c;
        else
            a = c;
    } while (fabs(b - a) > 2 * EPS || fabs(c - e * sin(c) - M > EPS));
    return c;
}

double Half(double M, double e) {
    double a = M-2.0, b = M+1.0, c =(a + b) / 2.0;
        do { //точность вычислений
            if ((a - e * sin(a) - M) * (c - e * sin(c) - M) < 0) {
                b = c;
            }
            else {
                a = c;
            }

            c = (a + b) / 2.0;
        } while (fabs(b - a) > 2 * EPS || fabs(c - e * sin(c) - M > EPS));
        return c;
    
}

double IsaacNewton(double M, double e) {
    double Ek = M, Ek1= Ek- (Ek- e*sin(Ek)-M)/ (1- e* cos(Ek));
    while (abs(Ek1 - Ek) > EPS){
        Ek = Ek1;
        Ek1 = Ek - ((Ek - e * sin(Ek) - M) / (1 - e * cos(Ek)));
    }
    return Ek1;
}