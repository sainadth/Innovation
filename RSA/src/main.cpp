#include <bits/stdc++.h>
#include "RSA.h"
using namespace std;

int main(){
    RSA* rsaHandler = new RSA();
    rsaHandler->generateRSAKey();
    return 0;
}