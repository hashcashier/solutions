//ASC29E
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <map>
#include <set>

using namespace std;


typedef map<int, long long> llmap;
typedef map<int, long long>::iterator m_it;

int func[160000000], sz;
llmap f[16][30][30][2][2], g[30][30][2][2], revFunc;
set<int> visG[30][30][2][2];
bool visF[16][30][30][2][2];
long long n, div, res, div2;

void F(int i, int B, int T, int U, int D) {
    bool &visit = visF[i][B][T][U][D];
    if(visit) return;
    visit = true;
    llmap &res = f[i][B][T][U][D];
    int BB = (1<<B), TT = (1<<T);

    if(i == div-1) {
        res[0] = 1;
    } else if(i == div - 2) {
        res[TT|BB] = 1;
    } else {
        if(U)
            for(int j = 1; T + j < n; j++) {
                F(i+1, T + j, B, U, D);
                llmap &subres = f[i+1][T + j][B][U][D];
                for(m_it it = subres.begin(); it != subres.end(); it++) {
                    if((it->first&TT) == 0)
                        res[it->first|TT] += it->second;
                }
            }

        for(int j = 1; T - j > B; j++) {
            F(i+1, T - j, B, 0, D);
            llmap &subres = f[i+1][T - j][B][0][D];
            for(m_it it = subres.begin(); it != subres.end(); it++) {
                if((it->first&TT) == 0)
                    res[it->first|TT] += it->second;
            }
        }
        // Bottom Move
        if(D)
            for(int j = 1; B - j >= 0; j++) {
                F(i+1, T, B - j, U, D);
                llmap &subres = f[i+1][T][B-j][U][D];
                for(m_it it = subres.begin(); it != subres.end(); it++) {
                    if((it->first&BB) == 0)
                        res[it->first|BB] += it->second;
                }
            }

        for(int j = 1; B + j < T; j++) {
            F(i+1, T, B + j, U, 0);
            llmap &subres = f[i+1][T][B+j][U][0];
            for(m_it it = subres.begin(); it != subres.end(); it++) {
                if((it->first&BB) == 0)
                    res[it->first|BB] += it->second;
            }
        }
    }
}

long long G(int B, int T, int U, int D, int M) {
    set<int> &visContainer = visG[B][T][U][D];
    llmap &resContainer = g[B][T][U][D];
    if(visContainer.count(M))
        return resContainer[M];
    visContainer.insert(M);

    int BB = 1<<B, TT = 1<<T, i = __builtin_popcount(M);
    long long res = 0;

    if(i == div2) {
        int opposite = (~M)&((1<<n)-1);
        res = f[0][B][T][U][D][opposite];
    } else {
        if(U)
            for(int j = 1; T + j < n; j++) {
                int NT = TT<<j;
                if(M&NT) continue;
                res += G(B, T+j, U, D, M|TT);
            }

        for(int j = 1; T - j > B; j++) {
            int NT = TT>>j;
            if(M&NT) continue;
                res += G(B, T - j, 0, D, M|TT);
        }
        // Bottom Move
        if(D)
            for(int j = 1; B - j >= 0; j++) {
                int NB = BB>>j;
                if(M&NB) continue;
                    res += G(B - j, T , U, D, M|BB);
            }

        for(int j = 1; B + j < T; j++) {
            int NB = BB<<j;
            if(M&NB) continue;
                res += G(B + j, T , U, 0, M|BB);
        }

    }

    resContainer[M] = res;
    return res;
}

void clr(int i, int B, int T, int U, int D) {
    if(!visF[i][B][T][U][D])
        f[i][B][T][U][D].clear();
    visF[i][B][T][U][D] = true;
}

//void Q() {
//    int idx = (n-1)%2, idx2 = (n-2)%2;
//        for(int B = 0; B < n; B++)
//            for(int T = B+1; T < n; T++)
//                for(int U = 0; U < 2; U++)
//                    for(int D = 0; D < 2; D++)
//                        visF[idx][B][T][U][D] = true, f[idx][B][T][U][D][0] = 1;
//
//    for(int i = n-1; i >= div2; i++) {
//        int idx = i%2, idx2 = (idx+1)%2;
//        memset(visF[idx2], 0, sizeof visF[idx2]);
//        for(int B = 0; B < n; B++)
//            for(int T = B+1; T < n; T++)
//                for(int U = 0; U < 2; U++)
//                    for(int D = 0; D < 2; D++)
//                        if(!visF[idx][B][T][U][D])
//                            continue;
//                        else {
//
//                        }
//    }
//}

int main() {
    cin >> n;
    if(n == 2)
        res = 1;
    else {
        div = (n/2)+(n%2), div2 = n/2;
//        Q();
//        for(int B = 0; B < n; B++)
//            for(int T = B+1; T < n; T++) {
//                F(0, B, T, 0, 0);
//                F(0, B, T, 0, 1);
//                F(0, B, T, 1, 0);
//                F(0, B, T, 1, 1);
//            }

        res = 0;
        for(int B = 0; B < n; B++)
            for(int T = B+1; T < n; T++)
                res += G(B, T, 1, 1, 0);
    }
    cout << res << endl;
}

