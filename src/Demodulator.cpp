#include "../include/Demodulator.h"


std::vector<int> Demodulator::demodulate(const std::vector<std::complex<double>>& noisy_symbols, int M) {
    std::vector<int> recovered_bits;
    
    // по всем зашумленным точкам
    for (int i = 0; i < noisy_symbols.size(); i++) {
        
        //одну точку
        std::complex<double> symbol = noisy_symbols[i];
        
        // возвращаем биты
        std::vector<int> bits = symbol_to_bits(symbol, M);
        
        
        for (int j = 0; j < bits.size(); j++) {
            recovered_bits.push_back(bits[j]);
        }
    }
    
    return recovered_bits;
}


std::vector<int> Demodulator::symbol_to_bits(std::complex<double> symbol, int M) {
    std::vector<int> bits;
    double I = symbol.real(); 
    double Q = symbol.imag(); 

    if (M == 4) { 
        
        if (I > 0) { bits.push_back(1); } 
        else       { bits.push_back(0); }
        
        if (Q > 0) { bits.push_back(1); } 
        else       { bits.push_back(0); }
    } 
    else if (M == 16) { 
       
        if (I <= -2)      { bits.push_back(0); bits.push_back(0); }
        else if (I <= 0)  { bits.push_back(0); bits.push_back(1); }
        else if (I <= 2)  { bits.push_back(1); bits.push_back(1); }
        else              { bits.push_back(1); bits.push_back(0); }

        
        if (Q <= -2)      { bits.push_back(0); bits.push_back(0); }
        else if (Q <= 0)  { bits.push_back(0); bits.push_back(1); }
        else if (Q <= 2)  { bits.push_back(1); bits.push_back(1); }
        else              { bits.push_back(1); bits.push_back(0); }
    }
    else if (M == 64) { // 64-QAM
        
        if (I <= -6)      { bits.push_back(0); bits.push_back(0); bits.push_back(0); }
        else if (I <= -4) { bits.push_back(0); bits.push_back(0); bits.push_back(1); }
        else if (I <= -2) { bits.push_back(0); bits.push_back(1); bits.push_back(1); }
        else if (I <= 0)  { bits.push_back(0); bits.push_back(1); bits.push_back(0); }
        else if (I <= 2)  { bits.push_back(1); bits.push_back(1); bits.push_back(0); }
        else if (I <= 4)  { bits.push_back(1); bits.push_back(1); bits.push_back(1); }
        else if (I <= 6)  { bits.push_back(1); bits.push_back(0); bits.push_back(1); }
        else              { bits.push_back(1); bits.push_back(0); bits.push_back(0); }

        
        if (Q <= -6)      { bits.push_back(0); bits.push_back(0); bits.push_back(0); }
        else if (Q <= -4) { bits.push_back(0); bits.push_back(0); bits.push_back(1); }
        else if (Q <= -2) { bits.push_back(0); bits.push_back(1); bits.push_back(1); }
        else if (Q <= 0)  { bits.push_back(0); bits.push_back(1); bits.push_back(0); }
        else if (Q <= 2)  { bits.push_back(1); bits.push_back(1); bits.push_back(0); }
        else if (Q <= 4)  { bits.push_back(1); bits.push_back(1); bits.push_back(1); }
        else if (Q <= 6)  { bits.push_back(1); bits.push_back(0); bits.push_back(1); }
        else              { bits.push_back(1); bits.push_back(0); bits.push_back(0); }
    }

    return bits;
}