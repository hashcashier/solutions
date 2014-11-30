#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    string inp;
    int cse = 1;
    freopen("containers.in", "r", stdin);
    while(cin >> inp && inp != "end") {
        int n = inp.size(), res = n;
        int low = 1, high = n;
        while(low <= high) {
            bool possible = true;
            int mid = (high+low)/2;
            char stks[mid];
            memset(stks, (char)('Z'+1), sizeof stks);
            for(int i = 0; i < n && possible; i++) {
                int best = -1;
                for(int j = 0; j < mid && best == -1; j++)
                    if(stks[j] == inp[i])
                        best = j;
                for(int j = 0; j < mid && best == -1; j++)
                    if(stks[j] > inp[i])
                        best = j;
                if(best == -1)
                    possible = false;
                else
                    stks[best] = inp[i];
            }


            if(possible) {
                res = min(res, mid), high = mid-1;
            } else
                low = mid + 1;
        }

        cout << "Case " << cse++ << ": " << res << endl;
    }
}
