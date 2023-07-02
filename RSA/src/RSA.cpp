#include "carlMichaelTotient.h"
#include "RSA.h"
#include <algorithm>

using namespace std;
long long int extendedEuclidianGcd(long long int, long long int, long long int&, long long int&);

RSA::RSA(/* args */)
{
}

RSA::~RSA()
{
}
long long int RSA::generateRSAKey()
{
    //choose 2 prime numbers
    p = 17;
    q = 13;
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;

    //n = p * q
    n = p * q;
    cout << "n = " << n << endl;

    //calculate carmichaelTotient
    carlMichaelTotient* cmt = new carlMichaelTotient(13 * 17);
    carlmichaelTotientValue = cmt->getCarlMichaelTotient();
    cout << "carlmichaelTotientValue = " << carlmichaelTotientValue << endl;

    //choose e
    e = leastCoPrime(carlmichaelTotientValue);
    cout << "e = " << e << endl;

    //determine d
    d = modularMultiplicativeInverse(e, carlmichaelTotientValue);
    cout << "d = " << d << endl;
    return 0;
}

long long int RSA::leastCoPrime(long long int carlmichaelTotientValue){
    for(long long int i = 2; i < carlmichaelTotientValue; i++){
        if(__gcd(i, carlmichaelTotientValue) == 1)
            return i;
    }
    return -1;
}

long long int RSA::modularMultiplicativeInverse(long long int e, long long int carlmichaelTotientValue){
    //using extendend Euclidian algorithm
    long long int x, y;
    extendedEuclidianGcd(e, carlmichaelTotientValue, x, y);
    // cout << x << y << endl;
    return x;
}

long long int extendedEuclidianGcd(long long int a, long long int b, long long int& x, long long int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long int x1, y1;
    long long int d = extendedEuclidianGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}