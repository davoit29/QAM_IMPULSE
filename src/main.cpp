#include <iostream>
#include <vector>
#include <random>
#include <fstream> // запись результатов в файл
#include "../include/Modulator.h"
#include "../include/Channel.h"
#include "../include/Demodulator.h"

int main() {
    //обЪекты классов 
    Modulator modulator;
    Channel channel;
    Demodulator demodulator;

    int numBits = 120000; 
    int M = 16;           

    // генерация случайную последовательность бит 
    std::vector<int> tx_bits;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < numBits; i++) {
        tx_bits.push_back(dis(gen));
    }

    
    std::ofstream outFile("results.csv");
    outFile << "Variance,BER\n"; 

   

    
    for (double noise_var = 0.0; noise_var <= 5.0; noise_var += 0.1) {
        
        
        std::vector<std::complex<double>> symbols = modulator.modulate(tx_bits, M);

        
        std::vector<std::complex<double>> noisySymbols = channel.addNoise(symbols, noise_var);

        std::vector<int> rx_bits = demodulator.demodulate(noisySymbols, M);

        // считаем ошибки
        int errors = 0;
        for (int i = 0; i < tx_bits.size(); i++) {
            if (tx_bits[i] != rx_bits[i]) {
                errors++;
            }
        }

        
        double ber = (double)errors / numBits;

        outFile << noise_var << "," << ber << "\n";
        std::cout << "Noise Var: " << noise_var <<  " | BER: " << ber << std::endl;
    }

    outFile.close();
    std::cout << "\nГотово" << std::endl;

    return 0;
}