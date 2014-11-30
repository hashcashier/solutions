//ASC30F
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    freopen("nim.in", "r", stdin);
    freopen("nim.out", "w", stdout);
    long long n, a = 0, b = 2;//, nums = 0;
    cin >> n;
    while(a < n) {
//        cout << a << endl;
//        nums++;
        a += b;
        if(a >= b*b) b++,a++;
    }
//    cout << nums << endl;
    if(a == n)
        cout << "LOSE" << endl;
    else
        cout << "WIN" << endl;
    return 0;
}
