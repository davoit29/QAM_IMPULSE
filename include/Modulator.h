#pragma once //один раз читать

#include <vector>
#include <complex>

class Modulator
{
public:
    std::vector<std::complex<double>>
    modulate(const std::vector<int>& bits, int M);

private:
    std::complex<double>
    BitsToSymbol(const std::vector<int>& bits, int M);
};