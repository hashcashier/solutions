//CF255C
#include <iostream>
#include <vector>

#define MOD 1000000009

using namespace std;

vector<long long> ft;

int lastOne(int i) {
    return i & (-i);
}

long long ft_rsq(int b) { // Sum until index b
    long long sum = 0;
    for(; b; b -= lastOne(b))
        sum = (sum+ft[b])%MOD;
    return sum%MOD;
}

long long ft_adjust(int k, long long v) { // adjust k'th element by v
    for(; k <= ft.size(); k+= lastOne(k))
        ft[k] += (ft[k]+v)%MOD;
}

void setRange(int k, int w, long long v) {
    ft_adjust(k, v);
    ft_adjust(k+w, -v);
}

int arr[300100], n, m;

int main() {
    int x;
    cin >> n >> m;

    long long fib[n+10];
    fib[1] = fib[2] = 1;
    for(int i = 3; i < n+10; i++)
        fib[i] = (fib[i-1] + fib[i-2])%MOD;
    ft.assign(n+10, 0);
    for(int i = 1; i <= n; i++)
        ft_adjust(i, fib[i]);

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    for(int i = 0; i < m; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if(t == 1) {
//            int f =
        } else {
            long long res = ft_rsq(r) - ft_rsq(l-1);
            cout << res << endl;
        }
    }

    return 0;
}
