//6185 Find the Outlier
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
double poly[10], res[10];
int n;

double calc(int x, int i) {
    if(i == 0) return poly[0];
    return poly[i] + x*calc(x, i-1);
}

int main() {
    while(cin >> n && n) {
        for(int i = 0; i <= n; i++)
            cin >> poly[i];
        for(int i = 0; i < n+3; i++)
            cin >> res[i];

    }
}
