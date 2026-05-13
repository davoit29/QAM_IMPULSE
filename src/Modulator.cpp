#include "Modulator.h"
#include <iostream>

std::complex<double> Modulator::BitsToSymbol(const std::vector<int>& bits, int M) {
    double in_phase_component = 0.0;
    double quadrature_component = 0.0;

    if (M == 4) {
        if (bits[0] == 0) in_phase_component = -1.0;
        else in_phase_component = 1.0;

        if (bits[1] == 0) quadrature_component = -1.0;
        else quadrature_component = 1.0;
    }
    else if (M == 16) {
        if (bits[0] == 0 && bits[1] == 0) in_phase_component = -3.0;
        else if (bits[0] == 0 && bits[1] == 1) in_phase_component = -1.0;
        else if (bits[0] == 1 && bits[1] == 1) in_phase_component = 1.0;
        else if (bits[0] == 1 && bits[1] == 0) in_phase_component = 3.0;

        if (bits[2] == 0 && bits[3] == 0) quadrature_component = -3.0;
        else if (bits[2] == 0 && bits[3] == 1) quadrature_component = -1.0;
        else if (bits[2] == 1 && bits[3] == 1) quadrature_component = 1.0;
        else if (bits[2] == 1 && bits[3] == 0) quadrature_component = 3.0;
    }
    else if (M == 64) {
        if (bits[0] == 0 && bits[1] == 0 && bits[2] == 0) in_phase_component = -7.0;
        else if (bits[0] == 0 && bits[1] == 0 && bits[2] == 1) in_phase_component = -5.0;
        else if (bits[0] == 0 && bits[1] == 1 && bits[2] == 1) in_phase_component = -3.0;
        else if (bits[0] == 0 && bits[1] == 1 && bits[2] == 0) in_phase_component = -1.0;
        else if (bits[0] == 1 && bits[1] == 1 && bits[2] == 0) in_phase_component = 1.0;
        else if (bits[0] == 1 && bits[1] == 1 && bits[2] == 1) in_phase_component = 3.0;
        else if (bits[0] == 1 && bits[1] == 0 && bits[2] == 1) in_phase_component = 5.0;
        else if (bits[0] == 1 && bits[1] == 0 && bits[2] == 0) in_phase_component = 7.0;

        if (bits[3] == 0 && bits[4] == 0 && bits[5] == 0) quadrature_component = -7.0;
        else if (bits[3] == 0 && bits[4] == 0 && bits[5] == 1) quadrature_component = -5.0;
        else if (bits[3] == 0 && bits[4] == 1 && bits[5] == 1) quadrature_component = -3.0;
        else if (bits[3] == 0 && bits[4] == 1 && bits[5] == 0) quadrature_component = -1.0;
        else if (bits[3] == 1 && bits[4] == 1 && bits[5] == 0) quadrature_component = 1.0;
        else if (bits[3] == 1 && bits[4] == 1 && bits[5] == 1) quadrature_component = 3.0;
        else if (bits[3] == 1 && bits[4] == 0 && bits[5] == 1) quadrature_component = 5.0;
        else if (bits[3] == 1 && bits[4] == 0 && bits[5] == 0) quadrature_component = 7.0;
    }

    return std::complex<double>(in_phase_component, quadrature_component);
}

std::vector<std::complex<double>> Modulator::modulate(const std::vector<int>& bits, int M) {
    std::vector<std::complex<double>> symbols;
    int bitsPerSymbol;

    if (M == 4) {
        bitsPerSymbol = 2; 
    } 
    else if (M == 16) {
        bitsPerSymbol = 4; 
    } 
    else if(M == 64) {
        bitsPerSymbol = 6; 
    }

    if (bits.size() % bitsPerSymbol != 0) {
        std::cout << "Число битов должно быть кратно числу модуляции" << std::endl;
    }

    for (int i = 0; i + bitsPerSymbol <= (int)bits.size(); i += bitsPerSymbol) {
        
        //отрезазние блоков битов
        std::vector<int> symbolBits; 

        for (int j = 0; j < bitsPerSymbol; j++) {
            
            symbolBits.push_back(bits[i + j]); 
        }
        
        symbols.push_back(BitsToSymbol(symbolBits, M));
    }

    return symbols;
}