//1860. Fiborial
#include <iostream>
#include <cstdio>
#include <vector>

#define MOD 1000000007

using namespace std;

typedef pair<int, int> ii;


const int MXPRIMES = 1000010;
bool notprime[MXPRIMES]; // primes upto 1M
long long prime[700000], facs[1000000][3];
int numprimes, NUMBER;

// Generate Primes
void sieve() {
    notprime[0] = notprime[1] = true;
    numprimes = 0;
    long long i, j;
    for(i = 2; i < MXPRIMES; i++)
        if(!notprime[i])
            for(j = i*i, prime[numprimes++] = i; j < MXPRIMES; j += i)
                notprime[j] = true;
}

int idx(int i) {
    return i < 0 ? i + 3 : i%3;
}

void alloc(int N, int a, int b, int c) {
    long long PF_idx = 0, PF = prime[PF_idx], NN = N;
    while(PF <= NN) {
        int power = 0;
        while(N%PF == 0)
            N /= PF, power++;

        facs[PF_idx][c] = power + facs[PF_idx][a] + facs[PF_idx][b];

        PF = prime[++PF_idx];
    }
}


int main() {
//    freopen("1860. Fiborial.in", "r", stdin);
    sieve();
//    cout << numDiv(48) << endl;
    int n;
    cin >> n;

    for(int i = 2; i <= n; i++) {
        int a = idx(i-2), b = idx(i-1), c = idx(i);
//        cout << i << ' ' << a << ' ' << b << ' ' << c << endl;
        alloc(i, a, b, c);
    }

    int ix = idx(n);
    cout << ix << endl;
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 10; i++)
            cout << facs[i][j] << ' ';
        cout << endl;
    }

    long long res = 1;
    for(int i = 0; i < numprimes; i++) {
        if(facs[i][ix])
            res = (res*(facs[i][ix] + 1))%MOD;
    }

    cout << res << endl;
}
