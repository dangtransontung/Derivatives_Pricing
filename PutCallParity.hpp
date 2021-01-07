#ifndef PutCallParity_hpp
#define PutCallParity_hpp

#include "EuropeanOption.hpp"
#include <iostream>
using namespace std;

// Put - Call parity: C + Kexp(-rt) = P + S
// Method 1: Calculating corresponding option price
double Parity(const EuropeanOption& input_call) {
    if (input_call.optType == "C") {
        // Return parity put option price
        cout << "Parity Put Price: ";
        return input_call.Price() + input_call.K * exp(-input_call.r * input_call.T) - input_call.S;
    }
    // Return corresponding Call Option price
    cout << "Parity Call Price: ";
    return input_call.Price() + input_call.S - input_call.K * exp(-input_call.r * input_call.T);
}

//Method 2: Check if a given set of put/call price satisfy parity
bool ParityCheck(const EuropeanOption& input_option, double parity_price) {
    // Input option is a Call option & Parity price is price of a parity PUT
    if (input_option.optType == "C") {
        return input_option.Price() + input_option.K * exp(-input_option.r * input_option.T) - parity_price - input_option.S < 1e-5;
    }
    // Input option is a Put option & Parity price is price of a parity CALL
    return parity_price + input_option.K * exp(-input_option.r * input_option.T) - input_option.Price() - input_option.S < 1e-5;
}
#endif /* PutCallParity_hpp */

