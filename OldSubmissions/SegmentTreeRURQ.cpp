#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';
struct SegmentTree{
    private:
        int L, R;
        ll val;
        ll lazy; // pending update to children?
        SegmentTree* Left;
        SegmentTree* Right;

        ll identity(){
            return 0;
        }

        void propagate(){
            if(Left != nullptr){
                Left->lazy += lazy;
                Left->val += (Left->R - Left->L) * lazy;
            }
            if(Right != nullptr){
                Right->lazy += lazy;
                Right->val += (Right->R - Right->L) * lazy;
            }
            lazy = 0;
        }

        void combine_nodes(){
            val = 0;
            if(Left != nullptr){
                val += Left->val;
            }
            if(Right != nullptr){
                val += Right->val;
            }
            
        }

    public:
        SegmentTree(vector<int> &arr, int qL, int qR){
            L = qL;
            R = qR;
            val = 0;
            lazy = 0;
            Left = nullptr;
            Right = nullptr;
            if(qL + 1 == qR){
                val = arr[qL];
            } else {
                int M = (L + R) >> 1;
                if(L < M){
                    Left = new SegmentTree(arr, L, M);
                }
                if(M < R){
                    Right = new SegmentTree(arr,M, R);
                }
                combine_nodes();
            }
        }
        void range_update(int value, int qL, int qR){
            // cout << L << sp << R << sp << qL << sp << qR << nl;
            if(qL >= qR){
                return;
            }else if(L == qL && R == qR){
                val += (R - L) * value;
                lazy += value;
                return;
            } else {
                propagate();
                int M = (L + R) >> 1;
                if(Left != nullptr){
                    Left->range_update(value,qL,min(qR,M));
                }
                if(Right != nullptr){
                    Right->range_update(value,max(qL,M),qR);
                }
                combine_nodes();
            }
        }

        ll range_query(int qL, int qR){
            if(qL >= qR){
                return identity();
            } else if(L == qL && R == qR){
                return val;
            } else {
                propagate();
                int M = (L + R) >> 1;
                ll Lt = 0, Rt = 0;
                if(Left != nullptr){
                    Lt = Left->range_query(qL,min(qR,M));
                }
                if(Right != nullptr){
                    Rt = Right->range_query(max(qL,M),qR);
                }
                
                return Lt + Rt;
            }
            

        }
        
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,q;
    cin >> n >> q;
    vector<int> bruh(n,0);
    for(int i = 0; i < n; i++){
        cin >> bruh[i];
    }
    SegmentTree ST = SegmentTree(bruh,0,n);
    int qtype;
    for(int i = 0; i < q; i++){
        cin >> qtype;
        if(qtype == 2){
            int id;
            cin >> id;
            cout << ST.range_query(id-1,id) << nl;
        } else {
            int S,E,V;
            cin >> S >> E >> V;
            ST.range_update(V,S-1,E);
        }
    }

}
