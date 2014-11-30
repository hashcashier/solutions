#include <iostream>
#include <cstdio>

using namespace std;

int N, M, K;

int trans(int i, int j) {
    return i*M + j;
}

pair<int, int> rev(int i) {
    return pair<int, int> (i/M, i%M);
}

int F(int msk) {
//    cout << msk << endl;
    int cnt = 0, res = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++) {
            if(msk&trans(i,j))
                cnt++, res++;
            else {
                bool u = !i || ((1<<trans(i-1,j))&msk), d = (i==N-1) || ((1<<trans(i+1,j))&msk),
                     l = !j || ((1<<trans(i,j-1))&msk), r = (j==M-1) || ((1<<trans(i, j+1))&msk),
                     ok = u && d && l && r;
                cnt += u && d && l && r;
                msk |= (ok<<trans(i,j));
            }
        }

    if(cnt < K)
        return 1000;
    return res;
}

int main() {
    int T;
    cin >> T;
    for(int cse = 1; cse <= T; cse++) {
        cin >> N >> M >> K;
        int res = N*M;
        for(int i = 0; i < (1<<(N*M)); i++)
            res = min(res, F(i));
        cout << "Case #" << cse << ": " << res << endl;
    }
}
