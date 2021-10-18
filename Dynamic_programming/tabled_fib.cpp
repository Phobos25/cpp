// FIB TABULATION
// Write a function that takes in a number as an argument.
// the Functiion should return the n-th number of the Fibonacci sequence

// algorithm
// the 0th number of the sequence is 0.
// the 1st number of the sequence is 1.

// To generate the next number of the sequence, we sum the previous two.

// it is so called tabular solution. we create a table that represents the sequence
// this way our time complexity will be linear O(n)
#include <iostream>
#include <vector>

using namespace std;

int fibonacci(int n){
    vector<int> fib_tabled(n+1, 0);
    fib_tabled[1] = 1;
    for (int i=0; i <= n; ++i){
        if (i == n){
            fib_tabled[i+1] += fib_tabled[i];            
        } else {
            fib_tabled[i+1] += fib_tabled[i];
            fib_tabled[i+2] += fib_tabled[i]; 
        }         
    }
    return fib_tabled[n];
}

int main(){
    cout << fibonacci(6) << endl;
    cout << fibonacci(7) << endl;    
    cout << fibonacci(8) << endl;    
    cout << fibonacci(20) << endl;    

    return 0;
}