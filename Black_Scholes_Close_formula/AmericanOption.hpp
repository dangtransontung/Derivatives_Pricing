//
//  AmericanOption.hpp
//  GroupA_B
//
//  Created by TungDang on 1/4/21.
//

#ifndef AmericanOption_hpp
#define AmericanOption_hpp

#include <stdio.h>
#include <string>
using namespace std;
class AmericanOption {
private:
    void init();
    void copy(const AmericanOption& source);
    double CallPrice() const;
    double PutPrice() const;
public:
    double K;
    double sig;
    double r;
    double b;
    double S;
    
    string optType;
    string underlying;
    
public:
    // Constructors & Destructor
    AmericanOption();
    AmericanOption(const AmericanOption& source);
    AmericanOption(const string& OptionType);
    virtual ~AmericanOption();
    
    // Operator
    AmericanOption& operator = (const AmericanOption& source);
    
    // Pricing function
    double Price() const;
    
    // Modifier function
    void toggle();
};

#endif /* AmericanOption_hpp */
