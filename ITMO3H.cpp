#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

#define MAX_N 6*(2<<17)+1
string T;

int n;
int RA[MAX_N], tRA[MAX_N];
int SA[MAX_N], tSA[MAX_N];
int Phi[MAX_N], PLCP[MAX_N], LCP[MAX_N];
int c[MAX_N];
void countingSort(int k) {
    int i, sum, maxi = max(300, n), t;
    memset(c, 0, sizeof c);
    for(i = 0; i < n; i++)
        c[i + k < n ? RA[i+k] : 0]++;
    for(i = sum = 0; i < maxi; i++)
        t = c[i], c[i] = sum, sum += t;
    for(i = 0; i < n; i++)
        tSA[ c[ SA[i]+k < n ? RA[ SA[i]+k ] : 0 ]++ ] = SA[i];
    for(i = 0; i < n; i++)
        SA[i] = tSA[i];
}

void constructSA() {
    int i, k, r;
    for(i = 0; i < n; i++) RA[i] = T[i];
    for(i = 0; i < n; i++) SA[i] = i;
    for(k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tRA[ SA[0] ] = r = 0;
        for(i = 1; i < n; i++)
            tRA[ SA[i] ] = (RA[ SA[i] ] == RA[ SA[i-1] ] && RA[ SA[i]+k ] == RA[ SA[i-1]+k ]) ? r : ++r;
        for(i = 0; i < n; i++)
            RA[i] = tRA[i];
        if(RA[ SA[n-1] ] == n-1) break;
    }
}

void computeLCP() {
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++)
        Phi[SA[i]] = SA[i-1];
    for (i = L = 0; i < n; i++) {
        if (Phi[i] == -1) {
            PLCP[i] = 0;
            continue;
        }
        while (T[i + L] == T[Phi[i] + L]) L++;
        PLCP[i] = L;
        L = max(L-1, 0);
    }
    for (i = 1; i < n; i++)
        LCP[i] = PLCP[SA[i]];
}

int main() {
    freopen("robots.in", "r", stdin);
//    freopen("robots.out", "w", stdout);
    int x;
    string A, B;
    cin >> x >> A >> B;
    T = A + A + A + "." + B + B + B;
    n = T.length();
    constructSA();
    computeLCP();
    for(int i = 0; i < n; i++)
        printf("%2d\t%2d\t%s\n", SA[i], LCP[i], T.substr(SA[i]).c_str() );
    int m = 3*A.length(), res = 0, sh = 0;
    for(int i = 1; i < n; i++)
        if(SA[i]/m != (SA[i-1]/m)) {
            if(LCP[i] > res) {
                res = LCP[i];
                sh = abs(SA[i]%A.length()-SA[i-1]%A.length());
            }

        }
    cout << res << ' '  << sh << endl;

	return 0;
}
