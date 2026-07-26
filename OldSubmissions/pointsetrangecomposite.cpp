#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';


ll MOD = 998244353;
struct SegmentTree{
    private:
        int L, R; // [L, R)
        pll data; //A, B
        SegmentTree* Left;
        SegmentTree* Right;
        pll identity(){
            return {1,0};
        }
        void combine_node(){
            data = identity();
            pll LeftData = identity();
            if(Left != nullptr){
                LeftData = Left->data;
            }
            pll RightData = identity();
            if(Right != nullptr){
                RightData = Right->data;
            }

            data = {((RightData.first % MOD)*(LeftData.first % MOD)) % MOD, 
                (((RightData.first % MOD) * (LeftData.second % MOD) % MOD) + (RightData.second % MOD)) % MOD};
        }

        pll combine_answer(pll LeftData, pll RightData){
            return  {((RightData.first % MOD)*(LeftData.first % MOD)) % MOD, 
                (((RightData.first % MOD) * (LeftData.second % MOD) % MOD) + (RightData.second % MOD)) % MOD};
        }
    public:
        SegmentTree(vector<pll> &arr, int pL, int pR){
            L = pL;
            R = pR;
            if(pL + 1 == pR){
                data = arr[pL];
            } else {
                data = identity();
                int M = (L + R) >> 1;
                if(L < M){
                    Left = new SegmentTree(arr, pL, M);
                }
                if(M < R){
                    Right = new SegmentTree(arr, M, pR);
                }
                combine_node();
            }
        }

        void point_update(int idx, ll A, ll B){
            if(L + 1 == R){
                data = {A,B};
                return;
            } else {
                int M = (L + R) >> 1;
                if(idx < M && Left != nullptr){
                    Left->point_update(idx,A,B);
                }
                if(idx >= M && Right != nullptr){
                    Right->point_update(idx,A,B);
                }
                combine_node();
            }
        }

        pll range_query(int qL, int qR){
            if(qR <= qL || qL >= R || qR < L){
                return identity();
            } else {
                if(qL == L && qR == R){
                    return data;
                } else {
                    int M = (L + R) >> 1;
                    pll LeftData = identity(), RightData = identity();
                    if(Left != nullptr){
                        LeftData = Left->range_query(qL, min(M,qR));
                    }
                    if(Right != nullptr){
                        RightData = Right->range_query(max(M,qL), qR);
                    }
                    return combine_answer(LeftData, RightData);
                }
            }
            
        }


};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    vector<pll> arr(N);
    ll A, B;
    for(int i = 0; i < N; i++){
        cin >> A >> B;  
        arr[i] = {A,B};
    }
    SegmentTree ST = SegmentTree(arr,0,N);
    ll q, m, n, v;
    for(int i = 0; i < Q; i++){
        cin >> q >> m >> n >> v;
        if(q == 0){
            ST.point_update(m,n,v);
        } else {
            pll temp = ST.range_query(m,n);
            A = temp.first;
            B = temp.second;
            v %= MOD;
            v *= A;
            v %= MOD;
            v += B;
            v %= MOD;
            cout << v << nl;
        }
    }
}
