#include "../include/Channel.h" 
#include <random>               
#include <cmath>                

//  добавления шума
std::vector<std::complex<double>> Channel::addNoise(const std::vector<std::complex<double>>& symbols, double noise_var) {
    
    
    std::vector<std::complex<double>> symbols_with_noise;
    
    
    double sigma = std::sqrt(noise_var / 2.0); //ско

    //  генератор  шума по гаусу(0,сигма^2)
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    
   
    std::normal_distribution<double> d(0.0, sigma);

    
    for (const auto& symbol : symbols) {
        
        
        double noiseI = d(gen);
        double noiseQ = d(gen);

        
        std::complex<double> point_with_noise(symbol.real() + noiseI, symbol.imag() + noiseQ);
        
        
        symbols_with_noise.push_back(point_with_noise);
    }

    
    return symbols_with_noise;
}