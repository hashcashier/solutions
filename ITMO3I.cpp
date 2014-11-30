#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    freopen("sums.in", "r", stdin);
    freopen("sums.out", "w", stdout);

    int N, K;
    cin >> N >> K;
    int nums[N], number[N], numberCount[N];
    for(int i = 0; i < N; i++)
        cin >> nums[i];
    sort(nums, nums+N);

    int idx = 0;
    number[0] = nums[0];
    numberCount[0] = 0;
    for(int i= 0 ; i < N; i++)
        if(nums[i] == number[idx])
            numberCount[idx]++;
        else {
            idx++;
            number[idx] = nums[i];
            numberCount[idx] = 1;
        }

    long long msof = 0, num = 0;
    for(int i = 1; i <= idx && num < K; i++) {
        int previdx = i - 1;

        while(number[i] > msof + 1 && num < K && previdx >= 0) {
//            cout << "lop" << previdx << ';' << numberCount[previdx] << ':';
            if(!numberCount[previdx]) {
                previdx--;
                continue;
            }

            if(num) cout << ' ';
            cout << number[previdx];
            msof += number[previdx];
            numberCount[previdx]--;
            num++;
        }

        if(number[i] == msof + 1 && num < K) {
            if(num) cout << ' ';
            cout << number[i];
            msof += number[i];
            numberCount[i]--;
            num++;
        } else if(num < K && number[i] == msof && ((i < idx && number[i+1] != msof + 1) || i == idx)) {
            if(num) cout << ' ';
            cout << number[i];
            msof += number[i];
            numberCount[i]--;
            num++;
        }
    }

    for(int i = idx; i >= 0 && num < K; i--)
//    for(int i = 0; i <= idx && num < K; i++)
        while(numberCount[i] && num < K) {
            if(num) cout << ' ';
            cout << number[i];
            numberCount[i]--;
            num++;
        }

    cout << endl;
}
