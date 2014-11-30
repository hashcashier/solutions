//6029 - Fibonacci Words
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

#define PRECOMP 25

using namespace std;


long long f[110], n, fib[110];
bool g[110][100010][2], v[110][100010][2], m[100010][PRECOMP];
string p, fibs[PRECOMP];
int failure[PRECOMP][76000];
//vector< vector<int> > failure(PRECOMP, vector<int>());

void kmpPreprocess() {
    for(int k = 0; k < PRECOMP; k++) {
        int i = 0, j = -1;
        failure[k][0] = -1;
        while(i < fib[k]) {
            while(j >= 0 && fibs[k][i] != fibs[k][j])
                j = failure[k][j];
            i++; j++;
            failure[k][i] = j;
        }
    }
}

void precomp() {
    fib[0] = fib[1] = 1, fibs[0] = "0", fibs[1] = "1";
    for(int i = 2; i < PRECOMP; i++)
        fibs[i] = fibs[i-1] + fibs[i-2];
    for(int i = 2; i <= 100; i++)
        fib[i] = fib[i-1] + fib[i-2];

    kmpPreprocess();
}

void recomputeKMP() {
//    cout << p << " matches:" << endl;
    for(int k = 0; k < PRECOMP; k++) {
//        cout << k << ' ' << fibs[k].substr(0, 10) << endl;
        int i = 0, j = 0;
        while(i < p.length()) {
            while( j >= 0 && p[i] != fibs[k][j] )
                j = failure[k][j];
            i++; j++;
            if(j == fib[k]) {
//                cout << " Match: " << fibs[k] << " in " << p << " at " << i-j << endl;
                m[i - j][k] = true, j = failure[k][j];
            }
        }
    }
}

bool match(int N, int idx) {
//    cout << fibs[N] << ',' << idx  << " ? " << m[idx][N] << endl;
    return m[idx][N];
}

bool G(int N, int idx, int dir) {
    if(v[N][idx][dir])
        return g[N][idx][dir];
    v[N][idx][dir] = true;

    bool validEdgepos = (!idx && !dir) || (idx == p.length()-1 && dir);
    if(N <= 1)
        return g[N][idx][dir] = validEdgepos && (p[idx] == fibs[N][0]);

    if(dir == 0) {//left
        if(N >= PRECOMP || fib[N-2] >= idx+1)
            return g[N][idx][dir] = G(N-2, idx, dir);
//        cout << (idx-fib[N-2]) << endl;
        return g[N][idx][dir] = match(N-2, idx - fib[N-2] + 1) && G(N-1, idx-fib[N-2], dir);
    } else {//right
        if(N >= PRECOMP || fib[N-1] >= p.length() - idx)
            return g[N][idx][dir] = G(N-1, idx, dir);

//        cout << (idx+fib[N-1]) << endl;
        return g[N][idx][dir] = match(N-1, idx) && G(N-2, idx+fib[N-1], dir);
    }
}

long long F(int N) {
    if(f[N] != -1)
        return f[N];

    if(N <= 1)
        return f[N] = (p == fibs[N]);
    else if(p.length() > fib[N])
        return f[N] = 0;

    long long crossover = 0;
    for(int i = 0; i < p.length() - 1; i++)
        crossover += G(N-1, i, 0) && G(N-2, i+1, 1);

    return f[N] = F(N-1) + F(N-2) + crossover;
}


int main() {
//    freopen("6029 - Fibonacci Words.in", "r", stdin);
    precomp();

    int cse = 1;
    while(cin >> n >> p) {
        memset(f, -1, sizeof f);
        memset(v, false, sizeof v);
        memset(m, false, sizeof m);
        recomputeKMP();
        cout << "Case " << cse++ << ": " << F(n) << endl;
    }
}
