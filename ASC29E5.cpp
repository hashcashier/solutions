//ASC29E
#include <iostream>
#include <cstdio>
#include <set>
#include <map>
#include <cstring>

using namespace std;

typedef pair<int, int> ii;
typedef set<ii>::iterator s_it;
typedef map<int, int>::iterator m_it;
typedef map<int, long long>::iterator ml_it;

map<int, long long> f[31][31][31][31][2][2];
int n, EXP;

void dbg(int b, int i, int T, int B, int U, int D) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n\n", b, i, T, B, U, D);
}

long long F(int n, int i, int T, int B, int U, int D, int msk) {
    map<int, long long> &resMap = f[n][i][T][B][U][D];
    if(resMap.count(msk)) return resMap[msk];
    EXP++;
    long long subres = 0;
    int TT = (1<<T), BB = (1<<B);
    if(i == n-2) {
        subres = 1;
    }
//    else if(i && T && B && ((!D && !U) || msk&1)) {
    else if(i && T && B && ((!D && !U))) {
        EXP--;
        subres = F(n-1, i-1, T-1, B-1, D, U, msk>>1);
    }
    else {
        // TOP Move
        if(U)
            for(int j = 1; T + j < n; j++) {
                if(msk&(1<<(T+j))) continue;
                subres += F(n, i+1, T + j, B, U, D, msk|TT);
            }

        for(int j = 1; T - j > B; j++) {
            if(msk&(1<<(T-j))) continue;
            subres += F(n, i+1, T - j, B, 0, D, msk|TT);
        }
        // Bottom Move
        if(D)
            for(int j = 1; B - j >= 0; j++) {
                if(msk&(1<<(B-j))) continue;
                subres += F(n, i+1, T, B - j, U, D,msk|BB);
            }

        for(int j = 1; B + j < T; j++) {
            if(msk&(1<<(B+j))) continue;
            subres += F(n, i+1, T, B + j, U, 0, msk|BB);
        }
    }

    resMap[msk] = subres;
    return subres;
}

int main() {
//    freopen("permutominoes.in", "r", stdin);
//    freopen("permutominoes.out", "w", stdout);
    for(n = 2; n <= 18; n++) {
        EXP = 0;
        long long res = 0;
        for(int B = 0; B < n; B++)
            for(int T = B+1; T < n; T++) {
                res += F(n, 0, T, B, 1, 1, 0);
            }
        cout << n << ' ' << res << ' ' << EXP << endl;
    }
    return 0;
}
