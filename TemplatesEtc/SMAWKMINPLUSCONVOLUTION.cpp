#ifdef NACHIA
#define _GLIBCXX_DEBUG
#else
#define NDEBUG
#endif
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <array>
#include <cmath>
#include <functional>
using namespace std;


// bool Func(y, xl, xr) , xl < xr
//   returns if A[y][xl] < A[y][xr]
template<class Func>
std::vector<int> SmawkAlgorithm(
    int height, int width,
    Func f
){
    auto reduce = [&](int yst, const std::vector<int>& cols)
     -> std::vector<int> {
        int p = 0;
        int w = int(cols.size());
        std::vector<int> idx;
        int r = -1;
        for(int q=0; q<w; q++){
            if(idx.empty()){
                idx.push_back(q); r += yst;
                continue;
            }
            int a = cols[idx.back()];
            int b = cols[q];
            if(f(r,a,b)){
                if(r+yst < height){ idx.push_back(q); r += yst; }
            } else {
                idx.pop_back(); q--; r -= yst;
            }
        }
        return idx;
    };
    auto ysts = std::vector<int>(1,1);
    auto cols = std::vector<std::vector<int>>(1);
    for(int i=0; i<width; i++) cols[0].push_back(i);
    cols[0] = reduce(1, cols[0]);
    while(true){
        int nxst = ysts.back() * 2;
        if(height < nxst) break;
        auto nxc = reduce(nxst, cols.back());
        int w = nxc.size();
        for(int i=0; i<w; i++) nxc[i] = cols.back()[nxc[i]];
        cols.push_back(move(nxc));
        ysts.push_back(nxst);
    }
    std::vector<int> ans(height);
    while(cols.size()){
        auto x = std::move(cols.back()); cols.pop_back();
        int st = ysts.back(); ysts.pop_back();
        int p = 0;
        for(int y=st-1; y<height; y+=st*2){
            int r = y+st < height ? ans[y+st] : width-1;
            ans[y] = x[p];
            while(p+1 < int(x.size()) && x[p+1] <= r){
                int xp = x[++p];
                if(!f(y,ans[y],xp)) ans[y] = xp;
            }
        }
    }
    return ans;
}


int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    std::vector<int> A(N), B(M);
    for(int i=0; i<N; i++) cin >> A[i];
    for(int i=0; i<M; i++) cin >> B[i];
    auto smawk = SmawkAlgorithm(N+M-1, M, [&](int y, int xl, int xr){
        if(y < xl || N <= y-xl) return false;
        if(y < xr || N <= y-xr) return true;
        return A[y-xl] + B[xl] < A[y-xr] + B[xr];
    });
    std::vector<int> ans(N+M-1);
    for(int i=0; i<N+M-1; i++){
        if(i) cout << ' ';
        cout << (A[i-smawk[i]] + B[smawk[i]]);
    } cout << '\n';
    return 0;
}


