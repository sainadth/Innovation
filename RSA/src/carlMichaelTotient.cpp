#include<carlMichaelTotient.h>
#include <bits/stdc++.h>
#include <numeric>
using namespace std;

carlMichaelTotient::carlMichaelTotient(long long int n){
    //considering n is product of 2 primes
    pair<long long int, long long int> primeFactors = findPrimeFactors(n);
    long long int p, q;
    p = primeFactors.first;
    q = primeFactors.second;

    val = lcm((p - 1), (q - 1));
}

carlMichaelTotient::~carlMichaelTotient(){
}

long long int carlMichaelTotient::lcm(long long int p, long long int q){
    return p * q / __gcd(p, q);
}

pair<long long int, long long int> carlMichaelTotient::findPrimeFactors(long long int n){
    for(long long int i = 2; i * i <= n; i++){
        if(n%i == 0)
            return {i, (int)n/i};
    }
    return {1, n};
}

long long int carlMichaelTotient::getCarlMichaelTotient(){
    return val;
}
