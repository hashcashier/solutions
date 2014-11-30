//6177 - The King's Ups and Downs
#include <algorithm>
#include <iostream>

using namespace std;

long long solve(int n) {
    int arr[n];
    long long res = 0;
    for(int i = 0; i < n; i++)
        arr[i] = i;

    do {
        bool ok = true;
        for(int i = 0; i < n; i++) {
            if(i%2) {
                if(i)
                    ok &= arr[i] < arr[i-1];
                if(i < n-1)
                    ok &= arr[i] < arr[i+1];
            } else {
                if(i)
                    ok &= arr[i] > arr[i-1];
                if(i < n-1)
                    ok &= arr[i] > arr[i+1];
            }
        }
        if(ok)
            res++;
    } while(next_permutation(arr, arr+n));

    return res;
}

int main() {
    for(int i = 1; i <= 10; i++)
        cout << i << ' ' << solve(i) << endl;
}
