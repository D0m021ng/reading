#include <iostream>
#include <fstream>

using namespace std;

double Power(double base, int exponent) {
    	if(base <= 0.0 && base >= 0.0 && exponent < 0)
            return 0;
        
        bool positive = true;
        if(exponent < 0){
            exponent = -exponent;
            positive = false;
        }
        
        double res = 1.0;
        while(exponent){
            if(exponent & 1)
                res *= base;
            base *= base;
            exponent /= 2;
        }
        
        if(positive){
            return res;
        }else{
            return 1/res;
        }
		
}

int main(){
    double base;
    int n;

    fstream fin("./input/input12");
    
    while(fin >> base >> n){
        cout << Power(base, n) << endl;
    }
    return 0;
}