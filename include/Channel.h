#pragma once
#include <vector>
#include <complex>

class Channel {
public:
    // принимает исимволы и дисперсию (мощность) шума возвращает зашумленные символы
    
    std::vector<std::complex<double>> addNoise(const std::vector<std::complex<double>>& symbols, double noiseVariance);
};