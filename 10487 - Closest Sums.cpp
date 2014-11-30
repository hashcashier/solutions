//10487 - Closest Sums
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n, cse = 1;
    while(cin >> n && n) {
        cout << "Case " << cse++ << ':' << endl;
        int nums[n];
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        int m;
        cin >> m;
        for(int i = 0; i < m; i++) {
            int num, best;
            cin >> num;
            bool found = false;
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++)
                    if(nums[j] != nums[k])
                        if(!found || abs(num-best) > abs(num-nums[j]-nums[k]))
                            found = true, best = nums[j] + nums[k];
            cout << "Closest sum to " << num << " is " << best << '.' << endl;
        }
    }
    return 0;
}
