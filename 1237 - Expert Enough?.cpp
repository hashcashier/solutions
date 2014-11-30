//1237 - Expert Enough?
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int D;
        cin >> D;
        string M[D];
        int L[D], H[D];
        for(int i = 0; i < D; i++)
            cin >> M[i] >> L[i] >> H[i];
        int Q;
        cin >> Q;
        for(int i = 0; i < Q; i++) {
            int P;
            cin >> P;
            string res = "";
            for(int j = 0; j < D; j++)
                if(L[j] <= P && P <= H[j])
                    if(res == "")
                        res = M[j];
                    else
                        res = "UNDETERMINED";
            if(res == "")
                cout << "UNDETERMINED" << endl;
            else
                cout << res << endl;
        }
        if(T) cout << endl;
    }
}
