#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';

struct SegTree{
    private:
        int L, R;
        bool pending_update;
        ll lazy;
        SegTree* Left;
        SegTree* Right;
        ll value = 0;

        void combine_nodes(){
            value = 0;
            if(Left != nullptr){
                value += Left->value;
            }
            if(Right != nullptr){
                value += Right->value;
            }
        }

        void propagate(){
            if(pending_update){
                if(Left != nullptr){
                    Left->value += (Left->R - Left->L) * lazy;
                    Left->pending_update = true;
                    Left->lazy += lazy;
                }

                if(Right != nullptr){
                    Right->value += (Right->R - Right->L) * lazy;
                    Right->pending_update = true;
                    Right->lazy += lazy;
                }

                pending_update = false;
                lazy = 0;
            }
        }
    public:
        SegTree(vector<ll> &arr, int qL, int qR){
            L = qL;
            R = qR;
            lazy = 0;
            pending_update = false;
            value = 0;
            Left = nullptr;
            Right = nullptr;
            if(qL + 1 == qR){
                value = arr[qL];
            } else {
                int M = (L + R) >> 1;
                if(L < M){
                    Left = new SegTree(arr, L, M);
                }
                if(M < R){
                    Right = new SegTree(arr, M, R);
                }
                combine_nodes();
            }
        }

        ll range_query(int qL, int qR){
            if(qL >= qR){
                return 0;
            } else if(L == qL && R == qR){
                return value;
            } else {
                propagate();
                int M = (L + R) >> 1;
                ll temp = 0;
                if(Left != nullptr){
                    temp += Left->range_query(qL, min(M,qR));
                }
                if(Right != nullptr){
                    temp += Right->range_query(max(M,qL), qR);
                }
                return temp;
            }
        }

        void range_update(int qL, int qR, ll K){
            if(qL >= qR){
                return;
            } else if(L == qL && R == qR){
                value += (R - L) * K;
                pending_update = true;
                lazy += K;
            } else {
                propagate();
                int M = (L + R) >> 1;
                if(Left != nullptr){
                    Left->range_update(qL, min(M,qR),K);
                }
                if(Right != nullptr){
                    Right->range_update(max(M,qL), qR,K);
                }
                combine_nodes();
            }
        }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin >> n >> q;
    vector<ll> bruhs(n,0);
    for(int i = 0; i < n; i++){
        cin >> bruhs[i];
    }
    SegTree ST = SegTree(bruhs,0, n);
    int query;
    for(int i = 0; i < q; i++){
        cin >> query;
        if(query == 2){
            int num;
            cin >> num;
            num--;
            cout << ST.range_query(num,num+1) << nl;
        } else {
            ll SL, SR;
            ll K;
            cin >> SL >> SR >> K;
            SL--;
            ST.range_update(SL,SR,K);
        }
    }
}