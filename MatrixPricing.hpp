#ifndef MatrixPricing_hpp
#define MatrixPricing_hpp

#include <stdio.h>
#include <vector>
#include "EuropeanOption.hpp"
#include "AmericanOption.hpp"
#include <boost/algorithm/string.hpp>

vector<vector<double> > MatrixPricing(const EuropeanOption& inOpt, string metric = "Price") {
    
    // User input for each parameter
    
    vector<vector<double> > parameters;
    vector<string> par_names = {"S  ", "K  ", "T  ", "r  ", "sig"};
    
    for (int i = 0; i < par_names.size(); i++) {
        cout << "Enter a range of " << par_names[i] << ": ";
        double a, b; cin >> a >> b;
        double interval = 0;
        if (a != b) {
        cout << "Enter number of interval to split: ";
        cin >> interval;
        }
        Mesher temp(a, b);
        vector<double> par_vector = temp.mesh(interval); // Split interval a, b into a vector (a, a + h, a + 2h, ..., a + n * h); n = (int) (b-a)/h
        for (int j = 0; j < par_vector.size(); j++) {
            cout << par_vector[j] << " ";
        } cout << endl;
        parameters.push_back(par_vector);
    }
    
    vector<vector<double>> answer; // Matrix answers with row is option price for 1 parameter interval
    
    EuropeanOption myOption = inOpt; // Copy input option
 
    // Calculate option price for each parameters
    for (int i = 0; i < par_names.size(); i++) {
        vector<double> temp;
        for (int j = 0; j < parameters[i].size(); j++) {
            if (i == 0) {
                myOption.S = parameters[i][j];
            } else if (i == 1) {
                myOption.K = parameters[i][j];
            } else if (i == 2) {
                myOption.T = parameters[i][j];
            } else if (i == 3) {
                myOption.r = parameters[i][j];
                myOption.b = parameters[i][j];
            } else if (i == 4) {
                myOption.sig = parameters[i][j];
            }
            
            // Adding result to result matrix
            metric = boost::algorithm::to_lower_copy(metric); // Transform input metric into lowercase word
            if (metric == "price") {
                temp.push_back(myOption.Price());
            } else if (metric == "delta") {
                temp.push_back(myOption.Delta());
            } else if (metric == "gamma") {
                temp.push_back(myOption.Gamma());
            } else if (metric == "vega") {
                temp.push_back(myOption.Vega());
            } else if (metric == "theta") {
                temp.push_back(myOption.Theta());
            }
        }
        // Reset to default values after changes in 1 parameter
        myOption = inOpt;
        
        answer.push_back(temp);
    }
    
    return answer;
}

// Overload function with American Option
vector<vector<double> > MatrixPricing(const AmericanOption& inOpt) {
    
    // User input for each parameter
    
    vector<vector<double> > parameters;
    vector<string> par_names = {"S  ", "K  ", "b  ", "r  ", "sig"};
    
    for (int i = 0; i < par_names.size(); i++) {
        cout << "Enter a range of " << par_names[i] << ": ";
        double a, b; cin >> a >> b;
        double interval = 0;
        if (a != b) {
        cout << "Enter number of interval to split: ";
        cin >> interval;
        }
        Mesher temp(a, b);
        vector<double> par_vector = temp.mesh(interval); // Split interval a, b into a vector (a, a + h, a + 2h, ..., a + n * h); n = (int) (b-a)/h
        for (int j = 0; j < par_vector.size(); j++) {
            cout << par_vector[j] << " ";
        } cout << endl;
        parameters.push_back(par_vector);
    }
    
    vector<vector<double>> answer; // Matrix answers with row is option price for 1 parameter interval
    
    AmericanOption myOption = inOpt; // Copy input option
 
    // Calculate option price for each parameters
    for (int i = 0; i < par_names.size(); i++) {
        vector<double> temp;
        for (int j = 0; j < parameters[i].size(); j++) {
            if (i == 0) {
                myOption.S = parameters[i][j];
            } else if (i == 1) {
                myOption.K = parameters[i][j];
            } else if (i == 2) {
                myOption.b = parameters[i][j];
            } else if (i == 3) {
                myOption.r = parameters[i][j];
            } else if (i == 4) {
                myOption.sig = parameters[i][j];
            }
            
            // Adding result to result matrix
            temp.push_back(myOption.Price());
        }
        // Reset to default values after changes in 1 parameter
        myOption = inOpt;
        
        answer.push_back(temp);
    }
    
    return answer;
}


#endif /* MatrixPricing_hpp */
