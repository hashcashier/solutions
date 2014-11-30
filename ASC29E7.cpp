//ASC29E
#include <iostream>
#include <cstdio>

using namespace std;

typedef long long LL;

LL ncr[50][50], n;

LL NCR(int a, int b) {
    if(a < 0 || b < 0 || b > a) return 0;
    else if(ncr[a][b]) return ncr[a][b];
    else if(b == 1) return ncr[a][b] = a;
    return ncr[a][b] = NCR(a-1, b-1) + NCR(a-1, b);
}

LL F(int LT, int LB, int RT, int RB, int A, int B) {
    if(LT < RT && LB > RB && LT-RB > 1) return 0;
    if(RT < LT && RB > LB && RT-RB > 1) return 0;
    if(LT < RT && LT > RB && LT-RB > 1) return 0;
    if(LB < RT && LB > RB && RT-LB > 1) return 0;
    // magic
    LL topMoves = n-min(LT, RT), botMoves = max(LB, RB), left = min(A, B) - 1, right = n - min(A, B) - 2;

}

int main() {
    cin >> n;
    for(int n = 2; n <= 30; n++) {
        LL res = 0;
        for(int LB = 0; LB < n; LB++)
            for(int LT = LB + 1; LT < n; LT++)
                for(int RB = 0; RB < n; RB++)
                    if((!LB && !RB) || (LB != RB && LT != RB))
                        for(int RT = RB+1; RB < n; RB++)
                            if((LT == n-1 && RT == n-1 && (LB || RB)) || (LB != RT && LT != RT)) {
                                if(LT == n-1 && RT == n-1) {
                                    for(int B = 2; B < n-1; B++)
                                        res += 4LL*F(LT, LB, RT, RB, n-1, B);
                                } else if(LB == 0 && RB == 0) {
                                    for(int A = 2; A < n-1; A++)
                                        res += 4LL*F(LT, LB, RT, RB, A, n-1);
                                } else {
                                    for(int A = 2; A < n-1; A++)
                                        for(int B = 2; B < n-1; B++)
                                            res += 4LL*F(LT, LB, RT, RB, A, B);
                                }
                            }
        cout << res << endl;
    }
}
