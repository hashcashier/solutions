//5092 - Permutation Counting
#include <cstdio>

#define MOD 1000000007

using namespace std;

int f[1010][1010];
bool vis[1010][1010];

int F(int n, int k) {
    if(vis[n][k])
        return f[n][k];
    vis[n][k] = true;

    if(k == 0)
        return f[n][k] = 1;
    else if(n <= k)
        return f[n][k] = 0;

    return f[n][k] = ((k+1LL)*F(n-1, k) + (n-k+0LL)*F(n-1, k-1))%MOD;;
}

int main() {
    int n,k;
//    freopen("5092 - Permutation Counting.in", "r", stdin);
    while(scanf("%d %d", &n, &k) != EOF) {
        printf("%d\n", F(n, k));

//        long long test = 0;
//        int arr[n];
//        for(int i = 0; i < n; i++)
//            arr[i] = i+1;
//        do {
//            int num = 0;
//            for(int i = 0; i < n; i++)
//                if(arr[i] > i+1)
//                    num++;
//            if(num == k) test++;
//        } while(next_permutation(arr, arr+n));
//        cout << test << endl;
    }
}
