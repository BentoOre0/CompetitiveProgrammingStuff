#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';

ll tri(ll a){
    return (a * (a + 1)) >> 1;
}

struct SegmentTree{
    private:
        int L, R;
        ll value;
        bool pendingupdate;
        ll lazy_common_diff;
        ll lazy_starting_value;

        //endingpoint = starting_point + (R - L - 1)* common diff
        //Total = lazy_common_diff * (R - L + 1);
        SegmentTree* Left;
        SegmentTree* Right;

        ll identity(){
            return 0;
        }

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
            if(pendingupdate){
                ll M = (L + R) >> 1;
                if(Left != nullptr){
                    Left->value += (((lazy_starting_value) * 2 + (M - L - 1) * lazy_common_diff) * (M - L)) >> 1;
                    Left->lazy_starting_value += lazy_starting_value;
                    Left->lazy_common_diff += lazy_common_diff;
                    Left->pendingupdate = true;
                }
                if(Right != nullptr){
                    ll rightstart = lazy_starting_value + (M - L) * lazy_common_diff;
                    Right->value += (((rightstart) * 2 + (R - M - 1) * lazy_common_diff) * (R - M)) >> 1;;
                    Right->pendingupdate = true;
                    Right->lazy_starting_value += rightstart;
                    Right->lazy_common_diff += lazy_common_diff;
                }
                lazy_common_diff = 0;
                lazy_starting_value = 0;
                pendingupdate = false;
            }
        }
    public:
        SegmentTree(vector<ll> &arr, int qL, int qR){
            L = qL;
            R = qR;
            value = 0;
            lazy_common_diff= 0;
            lazy_starting_value = 0;
            pendingupdate = false;
            Left = nullptr;
            Right = nullptr;
            if(L + 1 == R){
                value = arr[L];
            } else {
                int M = (L + R) >> 1;
                if(L < M){
                    Left = new SegmentTree(arr, L, M);
                }
                if(M < R){
                    Right = new SegmentTree(arr, M, R);
                }
                combine_nodes();
            }
        }

        void range_update(ll common_difference, ll starting_value, int qL, int qR){
            if(qL >= qR){
                return;
            } else if(L == qL && R == qR){
                value += (((starting_value) * 2 + (qR - qL - 1) * common_difference) * (qR - qL)) >> 1;
                lazy_common_diff += common_difference;
                lazy_starting_value += starting_value;
                pendingupdate = true;
                return;
            } else {
                propagate();
                int M = (L + R) >> 1;
                if(L <= qL && qR <= M){
                    Left->range_update(common_difference,starting_value,qL,qR);
                } else if(M <= qL && qR <= R){
                    Right->range_update(common_difference,starting_value,qL,qR);
                } else {
                    if(Left != nullptr){
                        Left->range_update(common_difference,starting_value,qL,M);
                    }
                    if(Right != nullptr){
                        Right->range_update(common_difference,starting_value + (M - qL) * common_difference,M,qR);
                    }
                }
                combine_nodes();
            }
        }
        ll range_query(int qL, int qR){
            if(qL >= qR){
                return identity();
            } else if(qL == L && qR == R){
                return value;
            } else {
                propagate();
                int M = (L + R) >> 1;
                ll lv = 0, rv = 0;
                if(Left != nullptr){
                    lv = Left->range_query(qL, min(M,qR));
                }
                if(Right != nullptr){
                    rv = Right->range_query(max(M,qL),qR);
                }
                return lv + rv;
            }
        }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;

    vector<ll> starray(N,0);
    for(int i = 0; i < N; i++){
        cin >> starray[i];
    }
    SegmentTree ST = SegmentTree(starray,0,N);
    int type;
    ll a, b;
    for(int i = 0; i < Q; i++){
        cin >> type;
        if(type == 1){
            cin >> a >> b;
            ST.range_update(1,1,a-1,b);
        } else {
            cin >> a >> b;
            // cout << a-1 << sp << b << nl;
            // ST.range_query(a-1,b);
            cout << ST.range_query(a-1,b) << nl;
        }
        // cout << ST.range_query(5,6) << nl;
    }
}
