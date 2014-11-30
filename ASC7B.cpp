//ASC7B
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
int r, n, m, logn;

class matrix {
    public:
        int a, b, c, d;
        matrix() {a = b = c = d = 0;}
        matrix(int A, int B, int C, int D) {a = A, b = B, c = C, d = D;}
        matrix mult(matrix &o) {
//            return matrix((a*o.a+b*o.c), (a*o.b+b*o.d), (c*o.a+d*o.c),(c*o.b+d*o.d));
            return matrix((a*o.a+b*o.c)%r, (a*o.b+b*o.d)%r, (c*o.a+d*o.c)%r,(c*o.b+d*o.d)%r);
        }
};

int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);

    cin >> r >> n >> m;
    while((1<<logn) < n) logn++;
    logn += 2;
    matrix mats[n][logn];
    for(int i = 0; i < n; i++) {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        mats[i][0] = matrix(a,b,c,d);
    }

    for(int j = 1; j <= logn; j++) {
        int expon = (1<<j);
        for(int i = 0; i + expon - 1 < n; i++) {
            mats[i][j] = mats[i][j-1].mult(mats[i+expon/2][j-1]);
        }
    }


    for(int i = 0; i < m; i++) {
        int a,b;
        cin >> a >> b;
        if(b < a)
            swap(a, b);
        a--, b--;

        matrix res = mats[a++][0];
        while(a <= b) {
            int jump = logn;
            while(a+(1<<jump)-1 > b)
                jump--;

            res = res.mult(mats[a][jump]);
            a += (1<<jump);
        }
        if(i) cout << endl;
        cout << res.a << ' ' << res.b << endl;
        cout << res.c << ' ' << res.d << endl;
    }
    return 0;
}
