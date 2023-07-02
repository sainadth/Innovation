class RSA
{
private:
    /* data */
    long long int p;
    long long int q;
    long long int n;
    long long int carlmichaelTotientValue;
    long long int e;
    long long int d;
public:
    RSA(/* args */);
    ~RSA();
    long long int generateRSAKey();
    long long int leastCoPrime(long long int carlmichaelTotientValue);
    long long int modularMultiplicativeInverse(long long int e, long long int carlmichaelTotientValue);
};