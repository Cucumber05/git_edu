#include <iostream>
#include <cmath>
#include <fstream>
const double G = 6.67430e-11;   // гравитационная постоянная
const double M = 5.972e24;      // масса Земли в кг
const double R = 6371e3;        // радиус Земли в м
const double i = 15;

double calculate_Vc(double H) {
    H *= 1000; 
    double vc = sqrt(G * M / (R + H));

    return vc;
}

double calculate_Vi(double H, double i) {
    H *= 1000;
    double vi = sqrt(G / R) * sqrt((2 / R) - (1 / (H + R))) * sin(i); // Скорость конца геоцентрического радиус-вектора 
    return vi;
}

int main() {
    double maxH = 600;
    double step = 10;
    
    std::ofstream file("Data.txt");
    if (!file) {
        std::cout << "Unsuccessful try" << std::endl;
        return 1;
    }
    else {
        file << "H (km)\t Vs (m/s)\t Vi " << std::endl;
        for (double H = 0; H <= maxH; H += step) {
            double vc = calculate_Vc(H);
            double vi = calculate_Vi(H, i);
            file << H << "\t" << vc << "\t" << vi << std::endl;
   
        }
        std::cout << "Chek file 'Data.txt' in directory" << std::endl;
    }
    

    return 0;
}

