//ASC29E
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

typedef pair<int, int> ii;

long long f[31][31][31][2][2], n;
bool vis[31][31][31][2][2];

void dbg(int b, int i, int T, int B, int U, int D) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n\n", b, i, T, B, U, D);
}

long long F(int i, int T, int B, int U, int D) {
    long long &res = f[i][T][B][U][D];
    bool &visit = vis[i][T][B][U][D];
    if(visit)
        return res;
    res = 0;
    visit = true;
    // Just close it
    if(i == n-2)
        return res = 1;
    else if(i == n-1 || T <= B)
        return res = 0;
    // TOP Move
    if(U)
        for(int j = 1; T + j < n; j++) {
            res += F(i+1, T + j, B, U, D);
            for(int k = 2; i + k < n-1; k++)
                for(int q = 0; q < n; q++)
                    if(vis[i+k][T][q][0][D])
                        res -= F(i+k, T, q, 0, D);
        }
    for(int j = 1; T - j > B; j++) {
        res += F(i+1, T - j, B, 0, D);
    }
    // Bottom Move
    if(D)
        for(int j = 1; B - j >= 0; j++) {
            res += F(i+1, T, B - j, U, D);
            for(int k = 2; i + k < n-1; k++)
                for(int q = 0; q < n; q++)
                    if(vis[i+k][q][B][U][0])
                        res -= F(i+k, q, B, U, 0);
        }


    for(int j = 1; B + j < T; j++) {
        res += F(i+1, T, B + j, U, 0);
    }
    dbg(res, i, T, B, U, D);
    return res;
}

int main() {
    cin >> n;
    printf("Res\ti\tT\tB\tU\tD\n");
    long long res = 0;
    for(int B = 0; B < n; B++)
        for(int T = B+1; T < n; T++)
            res += F(0, T, B, 1, 1);
    cout << res << endl;
    return 0;
}
