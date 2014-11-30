//6743 - Movie
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

long long specs[8][3] = { {1024, 768, 319},
                    {1024, 600, 419},
                    {960, 640, 450},
                    {2048, 1536, 519},
                    {1136, 640, 599},
                    {1280, 800, 600},
                    {1080, 1920, 630},
                    {1136, 640, 719}
                    };

int main() {
    freopen("6743 - Movie.in", "r", stdin);
    int dim[2];
    while(cin >> dim[0] >> dim[1] && dim[0] && dim[1]) {
        unsigned long long bh = 0, bw = 0, bcoeff = dim[0], bd = 0;
        for(int j = 0; j < 2; j++)
            for(int i = 0; i < 8; i++) {
                unsigned long long H = dim[j], W = dim[(j+1)%2], coeff, xh, xw, xcoeffL, xcoeffR;

                if(specs[i][0]*W < specs[i][1]*H) {
                    xh = specs[i][0];
                    xw = specs[i][0]*W;
                    coeff = H;
                    xcoeffL = xw;
                    xcoeffR = specs[i][1];
                } else {
                    xh = specs[i][1]*H;
                    xw = specs[i][1];
                    coeff = W;
                    xcoeffL = specs[i][0];
                    xcoeffR = xh;
                }

                unsigned long long  LHS = xcoeffL*specs[bd][0]*specs[bd][1]*bcoeff,
                                    RHS =  bh*bw*xcoeffR*coeff;

                if(LHS > RHS) {
                    bh = xw, bw = xw, bd = i, bcoeff = coeff;
                } else if(LHS == RHS && specs[bd][2] >= specs[i][2]) {
                    bh = xw, bw = xw, bd = i, bcoeff = coeff;
                }
            }
        cout << specs[bd][2] << endl;
    }
    return 0;
}
