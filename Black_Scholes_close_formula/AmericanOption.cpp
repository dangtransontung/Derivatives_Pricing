//
//  AmericanOption.cpp
//  GroupA_B
//
//  Created by TungDang on 1/4/21.
//

#include "AmericanOption.hpp"
#include <iostream>
#include <cmath>
using namespace std;
double AmericanOption::CallPrice() const {
    double y1 = 0.5 - b/pow(sig, 2) + sqrt(pow(b/pow(sig,2) - 0.5,2) + 2*r/pow(sig, 2));
    return K/(y1 - 1) * pow((y1 - 1)/y1 * S/K, y1);
}

double AmericanOption::PutPrice() const {
    double y2 = 0.5 - b/pow(sig,2) - sqrt(pow(b/pow(sig,2) - 0.5,2) + 2*r/pow(sig,2));
    return K/(1-y2) * pow((y2-1)/y2 * S/K,y2);
}


/////
void AmericanOption::init() {
    // Default values
    r = 0.05;
    sig = 0.2;
    
    K = 110.0;
    
    b = r;  // Black & Scholes stock option model
    S = 100;
    
    optType = "C"; // European Call Option
}

void AmericanOption::copy(const AmericanOption& source) {
    r    = source.r;
    sig  = source.sig;
    K    = source.K;
    b    = source.b;
    S    = source.S;
       
    optType = source.optType;
    underlying = source.underlying;
}

// Constructors &  Destructor
AmericanOption::AmericanOption() {
    init();
}

AmericanOption::AmericanOption(const AmericanOption& source){
    copy(source);
}

AmericanOption::AmericanOption(const string& OptionType) {
    init();
    optType = OptionType;

    if (optType == "c")
        optType = "C";
}

AmericanOption::~AmericanOption(){
}

// Operator
AmericanOption& AmericanOption::operator = (const AmericanOption& source) {
    if (this == &source) return *this;

    copy (source);

    return *this;
}

// Pricing function
double AmericanOption::Price() const {
    if (optType == "C") return CallPrice();
    return PutPrice();
}

// Toggle Function
void AmericanOption::toggle() {
    if (optType == "C")
        optType = "P";
    else
        optType = "C";
}
