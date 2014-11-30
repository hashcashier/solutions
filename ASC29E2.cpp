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

//set<ii> f[31][31][31][31][2][2];
map<int, int> f[31][31][31][31][2][2];
int n, EXP;
bool vis[31][31][31][31][2][2];

void dbg(int b, int i, int T, int B, int U, int D) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n\n", b, i, T, B, U, D);
}

void F(int n, int i, int T, int B, int U, int D) {
    map<int, int> &res = f[n][i][T][B][U][D];
    bool &visit = vis[n][i][T][B][U][D];
    if(visit) return;

    visit = true;
    res.clear();
    int TT = (1<<T), BB = (1<<B);
    if(i == n-2) {
        res.insert(ii(TT|BB,1));
        return;
    }
    else if(i && T && B && !D) {
        F(n-1, i-1, T-1, B-1, U, 0);
        map<int, int> &subres = f[n-1][i-1][T-1][B-1][U][0];
        for(m_it it = subres.begin(); it != subres.end(); it++)
            res[it->first<<1] = it->second;
        return;
    }
    // TOP Move
    if(U)
        for(int j = 1; T + j < n; j++) {
            F(n, i+1, T + j, B, U, D);
            map<int, int> &subres = f[n][i+1][T + j][B][U][D];
            for(m_it it = subres.begin(); it != subres.end(); it++) {
                ii subSol = *it;
                if((subSol.first&TT) == 0)
                    res[subSol.first|TT] += subSol.second;
            }
        }

    for(int j = 1; T - j > B; j++) {
        F(n, i+1, T - j, B, 0, D);
        map<int, int> &subres = f[n][i+1][T - j][B][0][D];
        for(m_it it = subres.begin(); it != subres.end(); it++) {
            ii subSol = *it;
            if((subSol.first&TT) == 0)
                res[subSol.first|TT] += subSol.second;
        }
    }
    // Bottom Move
    if(D)
        for(int j = 1; B - j >= 0; j++) {
            F(n, i+1, T, B - j, U, D);
            map<int, int> &subres = f[n][i+1][T][B-j][U][D];
            for(m_it it = subres.begin(); it != subres.end(); it++) {
                ii subSol = *it;
                if((subSol.first&BB) == 0)
                    res[subSol.first|BB] += subSol.second;
            }
        }

    for(int j = 1; B + j < T; j++) {
        F(n, i+1, T, B + j, U, 0);
        map<int, int> &subres = f[n][i+1][T][B+j][U][0];
        for(m_it it = subres.begin(); it != subres.end(); it++) {
            ii subSol = *it;
            if((subSol.first&BB) == 0)
                res[subSol.first|BB] += subSol.second;
        }
    }
//    EXP = max(EXP, (int)res.size());
    // Just close it
//    dbg(res, i, T, B, U, D);
}

int main() {
//    freopen("permutominoes.in", "r", stdin);
//    freopen("permutominoes.out", "w", stdout);
    for(n = 2; n <= 16; n++) {
//        memset(vis, 0, sizeof vis);
        EXP = 0;
        long long res = 0;
        for(int B = 0; B < n; B++)
            for(int T = B+1; T < n; T++) {
                F(n, 0, T, B, 1, 1);
                res += f[n][0][T][B][1][1].begin()->second;
            }
        cout << n << ' ' << res << ' ' << EXP << endl;
    }
//    cin >> n;
//    printf("Res\ti\tT\tB\tU\tD\n");
//    long long res = 0;
//    for(int B = 0; B < n; B++)
//        for(int T = B+1; T < n; T++) {
//            F(0, T, B, 1, 1);
//            res += f[0][T][B][1][1].begin()->second;
//        }
//    cout << res << endl;
    return 0;
}
