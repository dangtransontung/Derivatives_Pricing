//
//  EuropeanOption.hpp
//  GroupA_B
//
//  Created by TungDang on 12/31/20.
//

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

class EuropeanOption {
private:
    
    void init();        // Initialize default values
    void copy(const EuropeanOption& source);
    
    // 'Kernel' functions for option calculations
    double CallPrice() const;
    double PutPrice() const;
    
    
    double CallDelta() const;
    double PutDelta() const;
    
    // Gaussian functions
    double n(double x) const;
    double N(double x) const;
    
public:
    
    double r;           // Interest rate
    double sig;         // Volatility
    double K;           // Strike Price
    double T;           // Expiration Date
    double b;           // Cost of carry - depend on input type models
    double S;           // Underlying current price S0
    
    string optType;
    string underlying;
    
public:
    EuropeanOption();                                   // Default Constructor
    EuropeanOption(const EuropeanOption& source);       // Copy Constructor
    EuropeanOption(const string& optionType);
    virtual ~EuropeanOption();                          // Destructor
    
    // Operator
    EuropeanOption& operator = (const EuropeanOption& source);
    
    // Functions to calculate option price and sensitivities
    double Price() const;
    
    double Delta() const;
    double Gamma() const;
    double Vega() const;
    double Theta() const;
    
    // Sensitivities by approximate
    double DeltaApprox() const;
    double GammaApprox() const;
    
    // Modifier functions
    void toggle();
};

#endif /* EuropeanOption_hpp */
