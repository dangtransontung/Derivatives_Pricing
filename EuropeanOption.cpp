//
//  EuropeanOption.cpp
//  GroupA_B
//
//  Created by TungDang on 12/31/20.
//

#include "EuropeanOption.hpp"
#include <cmath>
#include <iostream>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>

using namespace boost::math;

// Gaussian functions

double EuropeanOption::n(double x) const {
    normal_distribution<> myNormal(0.0, 1.0);
    return pdf(myNormal, x);
}

double EuropeanOption::N(double x) const {
    normal_distribution<> myNormal(0.0, 1.0);
    return cdf(myNormal, x);
}

// Kernal Functions
    // Option Price
double EuropeanOption::CallPrice() const {
    double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T)/ (sig * sqrt(T));
    double d2 = d1 - sig * sqrt(T);
    return (S * exp((b-r)*T) * N(d1)) - K * exp(-r * T)* N(d2);
}

double EuropeanOption::PutPrice() const {
    double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T)/ (sig * sqrt(T));
    double d2 = d1 - sig * sqrt(T);
    return K * exp(-r * T)* N(-d2) - S * exp((b-r)*T) * N(-d1);
}
    // Call sensitivities
double EuropeanOption::CallDelta() const{
    double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T)/ (sig * sqrt(T));
    return exp((b-r)*T) * N(d1);
}

    // Put Sensitivities
double EuropeanOption::PutDelta() const{
    double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T)/ (sig * sqrt(T));
    return -exp((b-r) * T) * N(-d1);
}

////////////////
void EuropeanOption::init()
{   // Initialise all default values
    
    // Default values
    r = 0.05;
    sig = 0.2;
    
    K = 110.0;
    T = 0.5;
    
    b = r;  // Black & Scholes stock option model
    S = 100;
    
    optType = "C"; // European Call Option
}

void EuropeanOption::copy( const EuropeanOption& source){
    r    = source.r;
    sig  = source.sig;
    K    = source.K;
    T    = source.T;
    b    = source.b;
    S    = source.S;
       
    optType = source.optType;
    underlying = source.underlying;

}

EuropeanOption::EuropeanOption() { // Default call option
    init();
}

EuropeanOption::EuropeanOption(const EuropeanOption& source) { // Copy constructor
    copy(source);
}

EuropeanOption::EuropeanOption(const string& optionType) {    // Create option type
    init();
    optType = optionType;

    if (optType == "c")
        optType = "C";
}

EuropeanOption::~EuropeanOption() {
}


EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source)
{

    if (this == &source) return *this;

    copy (source);

    return *this;
}

// Functions that calculate option price and sensitivities
double EuropeanOption::Price() const
{
    if (optType == "C")
    {
        return CallPrice();
    }
    else
    {
        return PutPrice();
    }
}

double EuropeanOption::Delta() const
{
    if (optType == "C")
        return CallDelta();
    else
        return PutDelta();

}

double EuropeanOption::Gamma() const {
    double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T)/ (sig * sqrt(T));
    return n(d1) * exp((b-r) * T)/ (S * sig * sqrt(T));
}

double EuropeanOption::Vega() const {
    double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T)/ (sig * sqrt(T));
    return S * sqrt(T) * exp((b-r) * T) * n(d1);
}

double EuropeanOption::Theta() const {
    double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T)/ (sig * sqrt(T));
    double d2 = d1 - sig * sqrt(T);
    return - (S * sig * exp((b-r) * T) * n(d1))/(2 * sqrt(T)) - (b-r) * S * exp((b-r) * T) * N(d1) - r * K * exp(-r * T) * N(d2);
}

// Approximate Sensitivities
    // Delta Approximate
double EuropeanOption::DeltaApprox() const {
    double h = 0.0001; // "Small" constant to approximate sensitivity
    EuropeanOption increaseOption(*this);
    increaseOption.S += h;
    EuropeanOption decreaseOption(*this);
    decreaseOption.S -= h;
    
    return (increaseOption.Price() - decreaseOption.Price())/ (2 * h);
}
    // Gamma Approximate
double EuropeanOption::GammaApprox() const {
    double h = 0.0001; // "Small" constant to approximate sensitivity
    EuropeanOption increaseOption(*this);
    increaseOption.S += h;
    EuropeanOption decreaseOption(*this);
    decreaseOption.S -= h;
    
    return (increaseOption.Price() - 2 * Price() + decreaseOption.Price())/(pow(h, 2));
}



// Modifier functions
void EuropeanOption::toggle()
{ // Change option type (C/P, P/C)

    if (optType == "C")
        optType = "P";
    else
        optType = "C";
}
