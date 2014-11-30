#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef pair<long double, int> retype;

int N, M, A[11];
long long q[17];
int r[1<<17];
int cardin[1<<17];


long long Q(int n, int m) {
    if(m == 0) return A[0];
    return A[m] + n*(Q(n, m-1));
}

long long Q(int n) {
    if(q[n] != -1)
        return q[n];
    return q[n] = Q(n, M);
}

int res[1<<17], reslen;
string bmpstr(int m) {
    string result(N, '0');//0', N);
    for(int i = 0; i < N; i++)
        if((1<<i) & m)
            result[i] = '1';
    return result;
}

bool vis[1<<17];
long long T(int msk) {
    if(vis[msk])
        return 0;
    vis[msk] = true;
//    cout << "T " << bmpstr(msk) << endl;

    long long remaining = 0;
    for(int i = 0; i < N; i++)
        if((1<<i)&msk)
            remaining += T(msk^(1<<i));

    res[reslen++] = msk;
    return q[ cardin[msk] ] + remaining;
}

long long ft[17];
long long FT(int R) {
    if(R == 0) return 0;
    if(ft[R] != -1) return ft[R];

    int msk = (1<<N)-1;
    ft[R] = FT(R-1) + T(msk - (1<<(R-1)));

//    cout << "FT " << R << ' ' << ft[R] << endl;
    return ft[R];
}

pair<long double, int> F(int R) {
    if(R == 0) return retype(0, 0);
    int msk = (1<<N)-1;

    long long total = FT(R), sum = 0;
    for(int i = 0; i < R; i++)
        sum += i*(FT(i+1) - FT(i));

    long double top = sum;
    top = top/total;
    top = top/N;
//    cout << R << ": " << sum << '/' << total << '=' << top << ' ' << reslen << endl;
    return retype(top, reslen);
}

void precomp() {
    memset(q, -1, sizeof q);
    for(int i = 0; i <= N; i++)
        Q(i);

    for(int i = 0; i < (1<<N); i++)
        for(int j = 1; j <= i; j <<= 1)
            if(i&j)
                cardin[i]++;

    memset(vis, 0, sizeof vis);
    memset(ft, -1, sizeof ft);
    vis[0] = true;
}

int main() {
    freopen("raccoons.in", "r", stdin);
    freopen("raccoons.out", "w", stdout);
    cin >> N >> M;
    for(int i = 0; i <= M; i++)
        cin >> A[M-i];
    precomp();

    retype best = retype(0, -1);
    for(int i = 1; i <= N; i++)
        best = max(best, F(i));

    for(int i = 0; i < best.second; i++)
        cout << bmpstr(res[i]) << endl;
}
