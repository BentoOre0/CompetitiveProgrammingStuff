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
        int L, R;
        bool pendingupdate;
        SegmentTree* Left;
        SegmentTree* Right;
        ll value;
        ll lazy_B;
        ll lazy_C;

        void combine(){
            value = 0;
            if(Left != nullptr){
                value += Left->value;
                value %= MOD;
            }
            if(Right != nullptr){
                value += Right->value;
                value %= MOD;
            }
        }

        void propagate(){
            if(pendingupdate){
                if(Left != nullptr){
                    Left->value*=lazy_B;
                    Left->value%=MOD;
                    Left->value+=lazy_C*(Left->R - Left->L);
                    Left->value%=MOD;
                    Left->lazy_B*=lazy_B;
                    Left->lazy_B%=MOD;
                    Left->lazy_C*=lazy_B;
                    Left->lazy_C%=MOD;
                    Left->lazy_C+=lazy_C;
                    Left->lazy_C%=MOD;
                    Left->pendingupdate = true;
                }
                if(Right != nullptr){
                    Right->value*=lazy_B;
                    Right->value%=MOD;
                    Right->value+=lazy_C * (Right->R - Right->L);
                    Right->value%=MOD;
                    Right->lazy_B*=lazy_B;
                    Right->lazy_B%=MOD;
                    Right->lazy_C*=lazy_B;
                    Right->lazy_C%=MOD;
                    Right->lazy_C+=lazy_C;
                    Right->lazy_C%=MOD;
                    Right->pendingupdate = true;
                }
                pendingupdate = false;
                lazy_B = 1;
                lazy_C = 0;
            }
        }
    public:
        SegmentTree(vector<ll> &a, ll qL, ll qR){
            L = qL;
            R = qR;
            Left = nullptr;
            Right = nullptr;
            pendingupdate = false;
            value = 0;
            lazy_B = 1;
            lazy_C = 0;
            if(qL + 1 == qR){
                value = a[qL];
            } else {
                ll M = (qL + qR) >> 1;
                if(L < M){
                    Left = new SegmentTree(a, qL, M);
                    value += Left->value;
                    value %= MOD;
                }
                if(M < R){
                    Right = new SegmentTree(a, M, qR);
                    value += Right->value;
                    value %= MOD;
                }
            }
        }

        void range_update(ll B, ll C, ll qL, ll qR){
            if(qR <= qL){
                return;
            } else {
                if(L == qL && R == qR){
                    value*=B;
                    value%=MOD;
                    value+=C*(R - L);
                    value%=MOD;
                    lazy_B*=B;
                    lazy_B %=MOD;
                    lazy_C*=B;
                    lazy_C %=MOD;
                    lazy_C+=C;
                    lazy_C %=MOD;
                    pendingupdate = true;
                } else {
                    propagate();
                    ll M = (L + R) >> 1;
                    if(Left != nullptr){
                        Left->range_update(B,C,qL,min(M,qR));
                    }
                    if(Right != nullptr){
                        Right->range_update(B,C,max(M,qL),qR);
                    }
                    combine();
                }
            }
        }

        ll range_query(ll qL, ll qR){
            if(qR <= qL){
                return 0;
            } else {
                if(L == qL && R == qR){
                    return value;
                } else {
                    propagate();
                    ll M = (L + R) >> 1;
                    ll qval = 0;
                    if(Left != nullptr){
                        qval += Left->range_query(qL,min(qR,M));
                        qval %= MOD;
                    }
                    if(Right != nullptr){
                        qval += Right->range_query(max(M,qL), qR);
                        qval %= MOD;
                    }
                    qval %= MOD;
                    return qval;
                }
            }
        }

};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    vector<ll> starr(N,0);
    for(int i = 0; i < N; i++){
        cin >> starr[i];
    }
    SegmentTree ST = SegmentTree(starr,0,N);
    int qtype;
    ll l,r;
    for(int i = 0; i < Q; i++){
        cin >> qtype;
        if(qtype == 1){
            cin >> l >> r;
            cout << ST.range_query(l,r) << nl;
        } else {
            ll uB, uC;
            cin >> l >> r >> uB >> uC;
            ST.range_update(uB,uC,l,r);
        }
        
    }


    
}
