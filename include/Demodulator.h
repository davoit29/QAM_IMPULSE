#pragma once
#include <vector>
#include <complex>

class Demodulator {
public:
    // из зашумленного вектора символов - вектор битов
    std::vector<int> demodulate(const std::vector<std::complex<double>>& symbol_to_bits, int M);

private:
    // одну зашумленную точку обратно в группу бит
    std::vector<int> symbol_to_bits(std::complex<double> symbol, int M);
};