//ASC20D
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

typedef unsigned long long LL;

bool vf[30][30], vg[30][30][30][30];
LL f[30][30], g[30][30][30][30];

LL F(int i, int j) {
    if(!i || !j)
        return 0;
    else if(vf[i][j])
        return f[i][j];
    vf[i][j] = true;

    f[i][j] = 0;

    if(i >= j && j > 1)
        f[i][j] += 1 + F(i-j, j);

    if(i && j > 2)
        f[i][j] += F(i, j-1);

    return f[i][j];
}

LL G(int i, int j, int k, int m) {
    if(!i && !j)
        return 1;
    else if(!i || !j || !k)
        return 0;
    else if(vg[i][j][k][m])
        return g[i][j][k][m];
    else if(!m)
        return g[i][j][k][m] = G(i, j, k-1, j);
    vg[i][j][k][m] = true;

    g[i][j][k][m] = 0;

    if(i >= k && j >= m)
        g[i][j][k][m] = G(i-k, j-m, k, m);

    g[i][j][k][m] += G(i, j, k, m-1);

//    prt(i, j, k, m);
    return g[i][j][k][m];
}

//int BF(vector<int> nums) {
//    int n = nums.size();
//    set< vector<int> > res;
//    do {
//        for(int msk = 0; msk < pow(3, n); msk++) {
//            stack<int> op;
//            bool ok = true;
//            vector<int> subres;
//            for(int i = 0; ok && i < n; i++) {
//                int st = int(msk/pow(3, i))%3;
//                if(op.empty() && st == 1)
//                    ok = false;
//                else if(!op.empty() && !st)
//                    ok = false;
//                else if(!st)
//                    op.push(nums[i]);
//                else if(st == 1)
//                    subres.push_back(op.top() * nums[i]), op.pop();
//                else if(st == 2)
//                    if(op.empty())
//                        subres.push_back(nums[i]);
//                    else {
//                        int num = op.top(); op.pop();
//                        op.push(num*nums[i]);
//                    }
//            }
//
//            if(ok && op.empty()) {
//                sort(subres.begin(), subres.end());
//                res.insert(subres);
//            }
//        }
//    } while(next_permutation(nums.begin(), nums.end()));
//    return res.size() - 1;
//}

LL Q(int i) {
    LL res = 0;
    for(int a = 0; a <= i; a++) {
        int resa = a > 1 ? F(a, a) + 1 : 1;
        for(int b = 0; b <= i; b++) {
            int resb = b > 1 ? F(b, b) + 1 : 1;
            res += resa*resb*G(i-a, i-b, i-a, i-b);
//            printf("%d %d %d %d \t %d %d %d\n", a, b, resa, resb, i-a, i-b, G(i-a, i-b, i-a, i-b));
        }
    }
    return res - 1;
}



int main() {
    freopen("false.in", "r", stdin);
    freopen("false.out", "w", stdout);
//    vector<int> test4(8, 0);
//    test4[0] = test4[1] = test4[2] = test4[3] = 2;
//    test4[4] = test4[5] = test4[6] = test4[7] = 5;
//    cout << 4 << ' ' << BF(test4) << endl;
//    vector<int> test(6, 0);
//    test[0] = test[1] = test[2] = 2;
//    test[3] = test[4] = test[5] = 5;
//    cout << 3 << ' ' << BF(test) << endl;
//    vector<int> test2(4, 0);
//    test2[0] = test2[1] = 2;
//    test2[2] = test2[3] = 5;
//    cout << 2 << ' ' << BF(test2) << endl;
//    cout << "------" << endl;

    LL n, INF = 0;
    for(int i = 0; i < 64; i++)
        INF |= 1ULL<<i;


//    int x = 11, y = 7;
//    LL a = pow(x, 9), b = pow(y, 9), c = pow(x*y, 9);
//    cout << a*b << ' ' << c << endl;
//    return 0;

    while(cin >> n) {

        bool found = false;
//        LL bestd = n, best = 0;
//        for(LL i = 26; !found && i > 0; i--) {
////            LL val = (LL) pow(n, 1.0/i);
////            for(LL j = val-min(1000ULL, val); !found && j <= val+1000; j++) {
////                if(j < 1 || ((LL) pow(j, i)) != n)
////                    continue;
////
////                found = true;
////            }
//            LL lo = 1, hi = ceil(pow(2*n, 1.0/i)), mid, pmid;
//            while(!found && lo <= hi) {
//
//                mid = lo+(hi-lo)/2, pmid = pow(mid, i);
//
////                cout << i << ' ' << lo << ' ' << hi << ' ' << mid << ' ' << pmid << endl;
//                if(pmid > n) {
//                    if(pmid - n < bestd)
//                        bestd = pmid-n, best = i;
//                    hi = mid-1;
//                } else if(pmid < n) {
//                    if(n - pmid < bestd)
//                        bestd = n-pmid, best = i;
//                    lo = mid+1;
//                } else {
//                    found = true;
//                }
//            }
//
//            if(found)
//                cout << Q(i) << endl;
//        }
//        if(!found)
//            cout << Q(best) << endl;
        int k = 0;
        for(LL i = 2; i < 32000; i++) {
            if(n%i == 0) {
                while(n && n%i == 0) {
                    k++;
                    n /= i;
//                    cout << "YOLO" << endl;
                }
                break;
            }
        }
        cout << Q(max(1, k)) << endl;
//        assert(found);
    }
    return 0;
}
