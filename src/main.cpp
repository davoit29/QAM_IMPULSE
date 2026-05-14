#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "../include/Modulator.h"
#include "../include/Channel.h"
#include "../include/Demodulator.h"

int main() {
    // экземпляры класса
    Modulator modulator;
    Channel channel;
    Demodulator demodulator;

    
    int numBits = 120000; 

    // Генерируем тестовые биты
    std::vector<int> txBits;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < numBits; i++) {
        txBits.push_back(dis(gen));
    }

   
    std::ofstream outFile("results.csv");
    outFile << "Variance,BER_QPSK,BER_QAM16,BER_QAM64\n";

    
    std::vector<int> modulations = {4, 16, 64};

    std::cout << "Начинаем симуляцию для QPSK, 16-QAM и 64-QAM..." << std::endl;

    
    for (double noise_var = 0.05; noise_var <= 5.0; noise_var += 0.05) {
        
        outFile << noise_var; 
        std::cout << "Noise Var: " << noise_var << " | ";

        
        for (int M : modulations) {
            
            auto symbols = modulator.modulate(txBits, M);
            auto noisySymbols = channel.addNoise(symbols, noise_var);
            auto rxBits = demodulator.demodulate(noisySymbols, M);

            // счет ошибки
            int errors = 0;
            for (int i = 0; i < txBits.size(); i++) {
                if (txBits[i] != rxBits[i]) errors++;
            }

            double ber = (double)errors / numBits;
            
            
            outFile << "," << ber;
            std::cout << "M=" << M << " BER=" << ber << "  ";
        }
        
        outFile << "\n"; 
        std::cout << std::endl;
    }

    outFile.close();
    std::cout << "\nУспешно" << std::endl;

    return 0;
}