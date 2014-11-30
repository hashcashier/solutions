//920 - Sunny Mountains
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        pair<int, int> pts[N];
        for(int i = 0; i < N; i++)
            cin >> pts[i].first >> pts[i].second;
        sort(pts, pts + N);

        int y = pts[N-1].second;
        double res = 0;
        for(int i = N-2; i >= 0; i--) {
            if(pts[i].second <= y) continue;

            int a = pts[i].second - pts[i+1].second, b = pts[i+1].first - pts[i].first, c = a*pts[i].first + b*pts[i].second;

            double x = (c-b*y)/(a*1.0), dx = x-pts[i].first;

            int dy = y - pts[i].second;

            res += sqrt(dx*dx + dy*dy);
            y = max(y, pts[i].second);
        }

        cout << setprecision(2) << fixed << res << endl;
    }
}

