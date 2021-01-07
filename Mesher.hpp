//
//  Mesher.hpp
//  GroupA_B
//
//  Created by TungDang on 1/3/21.
//

#ifndef Mesher_hpp
#define Mesher_hpp

#include <stdio.h>
#include <vector>

class Mesher
{
public:
        double a, b;    // In space

        Mesher()
        {
            a = 0.0; b = 1.0;
        }

        Mesher (double A, double B)
        { // Describe the domain of integration

            a = A;
            b = B;
        }

        std::vector<double> xarr(int J)
        {
            // NB Full array (includes end points)

            double h = (b - a) / double (J);
            
            int size = J+1;
            int start = 1;

            std::vector<double> result(size, start);
            result[0] = a;

            for (unsigned int j = 1; j < result.size(); j++)
            {
                result[j] = result[j-1] + h;
            }

            return result;
        }

        std::vector<double> Xarr(int J)
        { // Return as an STL vector

            // NB Full array (includes end points)

            double h = (b - a) / double (J);
            
            int size = J+1;
            int start = 1;

            std::vector<double> result(size, start);
            result[0] = a;

            for (unsigned int j = 1; j < result.size(); j++)
            {
                result[j] = result[j-1] + h;
            }

            return result;
        }
    
        std::vector<double> mesh(double h) {
        // return a mesh array of doubles separated by a mesh size h
            std::vector<double> result;
            if (a == b) {
                result.push_back(a);
                return result;
            }
            
            double temp = a;
            while (temp <= b + 1e-5) {
                result.push_back(temp);
                temp += h;
            }
            
            return result;
        }

};


#endif /* Mesher_hpp */
