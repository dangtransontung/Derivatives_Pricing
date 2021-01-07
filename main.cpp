#include "EuropeanOption.hpp"
#include "PutCallParity.hpp"
#include "Mesher.hpp"
#include "MatrixPricing.hpp"
#include <iostream>
#include <vector>
#include "PutCallParity.hpp"
#include "AmericanOption.hpp"

using namespace std;

int main() {
    // Initialize option
    EuropeanOption myOption;
    
    
    // PART A //////////////////////////////////
    
    // Part A - a.1 b.1
    cout << "Part A - A.1 B.1" << endl;
    // 4 Batch input
    vector<double> T = {0.25, 1.0, 1.0, 30.0};
    vector<double> K = {65, 100, 10, 100};
    vector<double> sig = {0.30, 0.2, 0.50, 0.30};
    vector<double> r = {0.08, 0.0, 0.12, 0.08};
    vector<double> S = {60, 100, 5, 100};
    vector<double> put_price_for_parity_checking = {5.84628, 7.96557, 4.07326, 1.24750};
    
    for (int i = 0; i < 4; i++) {
        
        // Assign option variable
        myOption.T = T[i];
        myOption.K = K[i];
        myOption.sig = sig[i];
        myOption.r = r[i];
        myOption.S = S[i];
        myOption.b = r[i];
        
        // Pricing & Parity check
        cout << "Batch" << i + 1 << endl;
        (myOption.optType == "C") ? cout << "Call Price\n" : cout << "Put PRice\n";
        cout << myOption.Price() << endl;
        cout << ParityCheck(myOption, put_price_for_parity_checking[i]) << endl; // 1 True ; 0 False
        // Compute price by parity function
        cout << Parity(myOption) << endl;
        cout << endl;
    }
    
    // Part A - c.1 d.1
    cout << "Part A - C.1 D.1" << endl;
    // One column for each parameter
    // S K T r sig
    // Input matrix parameter;
    cout << "MATRIX PRICING" << endl;
    
    vector<vector<double> > answer = MatrixPricing(myOption); // Run the matrix pricing function
    
    cout << "Option Pricing Matrix: " << endl;
    
    vector<string> par_names = {"S  ", "K  ", "T  ", "r  ", "sig"};
    for (int i = 0; i < par_names.size(); i++) {
        cout << par_names[i] << ": ";
        for (int j = 0; j < answer[i].size(); j++) {
            cout << answer[i][j] << " ";
        } cout << endl;
    } cout << endl;
    
    // PART A a.2
    cout << "Part A - A.2" << endl;
    myOption.K = 100;
    myOption.S = 105;
    myOption.T = 0.5;
    myOption.r = 0.1;
    myOption.b = 0;
    myOption.sig = 0.36;
    cout << "Gamma: " << myOption.Gamma() << endl;
    cout << "Delta " << myOption.optType << ": " << myOption.Delta() << endl;
    myOption.toggle();
    cout << "Delta " << myOption.optType << ": " << myOption.Delta() << endl;


    // PART A b.2 c.2
    cout << endl << "Part A - B.2 C.2" << endl;
    cout << "MATRIX SENSITIVITIES" << endl;
    
    
        // Delta Matrix
    vector<vector<double> > answer_delta = MatrixPricing(myOption, "Delta"); // Run the matrix pricing function
    
    cout << "Option Delta Matrix: " << endl;
    
    for (int i = 0; i < par_names.size(); i++) {
        cout << par_names[i] << ": ";
        for (int j = 0; j < answer_delta[i].size(); j++) {
            cout << answer_delta[i][j] << " ";
        } cout << endl;
    } cout << endl;
    
        // Gamma Matrix
    vector<vector<double> > answer_gamma = MatrixPricing(myOption, "Gamma"); // Run the matrix pricing function
    
    cout << "Option Gamma Matrix: " << endl;
    
    for (int i = 0; i < par_names.size(); i++) {
        cout << par_names[i] << ": ";
        for (int j = 0; j < answer_gamma[i].size(); j++) {
            cout << answer_gamma[i][j] << " ";
        } cout << endl;
    } cout << endl;
    
    // Part A - d.2
    cout << "Part A - D.2" << endl;
    
    cout << "Closed Formula: " << endl;
    cout << "Delta: " << myOption.Delta() << endl;
    cout << "Gamma: " << myOption.Gamma() << endl;
    
    cout << "Approximate: " << endl;
    cout << "Delta Approx: " << myOption.DeltaApprox() << endl;
    cout << "Gamma Approx: " << myOption.GammaApprox() << endl;
    cout << endl;
    
    // Part B - a b
    cout << "Part B - A B" << endl;
    AmericanOption myAopt;
    myAopt.K = 100;
    myAopt.sig = 0.1;
    myAopt.r = 0.1;
    myAopt.b = 0.02;
    myAopt.S = 110;
    
    cout << myAopt.optType << " price: " << myAopt.Price() << endl;
    myAopt.toggle();
    cout << myAopt.optType << " price: " << myAopt.Price() << endl;
    cout << endl;
    
    // Part B - c d
    cout << "Part B - C D" << endl;
    cout << "American Pricing Matrix" << endl;
    vector<vector<double> > AmeMat = MatrixPricing(myAopt);
    vector<string> A_par_names = {"S  ", "K  ", "b  ", "r  ", "sig"};
    // Print out result
    for (int i = 0; i < A_par_names.size(); i++) {
        cout << A_par_names[i] << ": ";
        for (int j = 0; j < AmeMat[i].size(); j++) {
            cout << AmeMat[i][j] << " ";
        } cout << endl;
    } cout << endl;
    
    return 0;
}
