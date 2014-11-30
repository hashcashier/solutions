#include <iostream>
#include <cstdio>
#include <map>

#define INF 1000000000100

using namespace std;

long long sums[4*1000100], costsums[4*1000100];
bool zero[4*1000100];

void add(int i, int L, int R, int pos, long long num) {
//    cout << i << ' ' << L << ' ' << R << ' ' << pos << ' ' << num << endl;
    if(zero[i]) {
        zero[i] = sums[i] = costsums[i] = 0;
        if(L != R)
            zero[2*i] = zero[2*i + 1] = true,
            sums[2*i] = costsums[2*i] = 0,
            sums[2*i + 1] = costsums[2*i + 1] = 0;
    }

    if(L == R && L == pos) {
        sums[i] += num;
        costsums[i] = sums[i]*pos;
    } else if(pos > R || pos < L)
        return;
    else {
        int mid = (L+R)/2, LL = L, LR = mid, RL = mid + 1, RR = R;

        add(2*i, LL, LR, pos, num);
        add(2*i + 1, RL, RR, pos, num);

        sums[i] = sums[2*i] + sums[2*i + 1];
        costsums[i] = costsums[2*i] + costsums[2*i + 1];
    }
//    cout << i << ' ' << L << ' ' << R << ' ' << pos << ' ' << num << ':' << sums[i] << endl;
}

void add(int pos, int num) {
    add(1, 0, 1000000, pos, num);
}

long long mincost(int i, int L, int R, long long N) {
//    cout << i << ' ' << L << ' ' << R << ' ' << N << endl;
    if(zero[i]) {
        zero[i] = sums[i] = costsums[i] = 0;
        if(L != R)
            zero[2*i] = zero[2*i + 1] = true,
            sums[2*i] = costsums[2*i] = 0,
            sums[2*i + 1] = costsums[2*i + 1] = 0;
    }

    if(N == 0)
        return 0;
    else if(N == sums[i])
        return costsums[i];
    else if(N > sums[i])
        return INF;
    else if(L == R) {
        return N*L;
    } else {
        int mid = (L+R)/2, LL = L, LR = mid, RL = mid + 1, RR = R;
        if(sums[2*i] >= N)
            return mincost(2*i, LL, LR, N);
        else {
            int rem = N - sums[2*i];
            return mincost(2*i, LL, LR, sums[2*i]) + mincost(2*i + 1, RL, RR, rem);
        }
    }
}

long long mincost(long long N) {
    return mincost(1, 0, 1000000, N);
}

void rem(int i, int L, int R, long long N) {
//    cout << i << ' ' <<  L << ' ' << R << ' ' << N << endl;
    if(N == sums[i])
        zero[i] = true, sums[i] = costsums[i] = 0;
    else if(N == 0)
        return;
    else if(L == R) {
        sums[i] -= N;
        costsums[i] = sums[i]*L;
    } else {
        int mid = (L+R)/2, LL = L, LR = mid, RL = mid + 1, RR = R;
        if(sums[2*i] >= N) {
            rem(2*i, LL, LR, N);
        } else {
            long long remain = N - sums[2*i];

            rem(2*i, LL, LR, sums[2*i]);
            rem(2*i + 1, RL, RR, remain);
        }

        sums[i] = sums[2*i] + sums[2*i + 1];
        costsums[i] = costsums[2*i] + costsums[2*i + 1];
    }

}

void rem(long long N) {
    rem(1, 0, 1000000, N);
}

int main() {
    freopen("icecream.in", "r", stdin);
    freopen("icecream.out", "w", stdout);
    string cmd;
    long long c, n;
    while(cin >> cmd >> n >> c) {
        if(cmd[0] == 'A') {
            add(c, n);
        } else {
            long long tmp = mincost(n);
//            cout << tmp << endl;
            if(tmp > c) {
                cout << "UNHAPPY" << endl;
            } else {
                rem(n);
                cout << "HAPPY" << endl;
            }
        }
    }
}
