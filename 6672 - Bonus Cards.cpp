//6672 - Bonus Cards
#include <cstdio>
#include <cstring>

using namespace std;

double f[3010][3010][2];
int n, a, b;

//bool v[3010][3010];
//
//void F(int A, int B) {
//    if(A+B == n || A > a || B > b) {
//        f[A][B][0] = f[A][B][1] = 0;
//        return;
//    } else if(v[A][B])
//        return;
//    v[A][B] = true;
//
//    double total = (2.0*(a-A) + (b-B) + 1);
//    double total2 = total + 1;
//
//    double alpha = 1/total;
//    double alpha2 = 2/total2;
//
//    double beta = (2*(a-A))/total;
//    double beta2 = (2*(a-A))/total2;
//
//    double gamma = (b-B)/total;
//    double gamma2 = (b-B)/total2;
//    F(A+1, B);
//    F(A, B+1);
//    f[A][B][0] = alpha + f[A+1][B][0]*beta + f[A][B+1][0]*gamma;
//    f[A][B][1] = alpha2 + f[A+1][B][1]*beta2 + f[A][B+1][1]*gamma2;
//}

int main() {
//    freopen("6672 - Bonus Cards.in", "r", stdin);
    while(scanf("%d %d %d", &n, &a, &b) != EOF) {
        for(int A = n; A >= 0; A--)
            for(int B = n - A; B >= 0; B--) {
                if(A + B == n) {
                    f[A][B][0] = f[A][B][1] = 0;
                    continue;
                }

                long long total = (2LL*(a-A) + (b-B) + 1);
                long long total2 = total + 1;

                int beta = (2*(a-A));
                int gamma = (b-B);

                f[A][B][0] = (1 + f[A+1][B][0]*beta + f[A][B+1][0]*gamma) / total;
                f[A][B][1] = (2 + f[A+1][B][1]*beta + f[A][B+1][1]*gamma) / total2;
            }
        printf("%.10lf\n", f[0][0][1]);
        printf("%.10lf\n", f[0][0][0]);
//        continue;
//
//        for(int i = 0; i <= n; i++)
//            for(int j = 0; i + j <= n; j++)
//                v[i][j] = false;
//        F(0,0);
//        printf("%.10lf\n", f[0][0][1]);
//        printf("%.10lf\n", f[0][0][0]);
    }
}
