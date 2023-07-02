#include <bits/stdc++.h>
using namespace std;
class carlMichaelTotient
{
private:
    /* data */
    long long int val = -1;
public:
    carlMichaelTotient(long long int n);
    ~carlMichaelTotient();
    long long int lcm(long long int p, long long int q);
    pair<long long int, long long int> findPrimeFactors(long long int n);
    long long int getCarlMichaelTotient();
};