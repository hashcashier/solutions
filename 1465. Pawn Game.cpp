//1465. Pawn Game
#include <iostream>
#include <cstdio>
#include <set>

#define MAXN 42

using namespace std;

int grundyValue[MAXN];

bool solve(int n) {
    return grundyValue[n] > 0;
}

bool solve2(int n) {
    n -= 42;
    n %= 34;
    int adds[] = {12,4,4,10}, num = 0;
    for(int i = 0; i < 5; i++) {
        if(n == num) return false;
        num += adds[i];
    }
    return true;
}

int main() {
    grundyValue[1] = grundyValue[2] = 1;
    for(int i = 3; i < MAXN; i++) {
        set<int> children;
        children.insert(grundyValue[i-2]);

        for(int j = 1; j < i-1; j++)
            children.insert(grundyValue[j-1]^grundyValue[i-j-2]);

        while(children.count(grundyValue[i])) grundyValue[i]++;
    }

//    int l = 0;
//    for(int i = 0; i < MAXN; i++) {
//        if(!solve(i))
//            cout << i << ' ' << (i-l) << ' ' << solve(i) << ' ' << solve2(i) << endl, l=i;
//    }

    int n;
    cin >> n;
    bool res = n < MAXN ? solve(n) : solve2(n);
    cout << (res ? "White" : "Black") << endl;
}
