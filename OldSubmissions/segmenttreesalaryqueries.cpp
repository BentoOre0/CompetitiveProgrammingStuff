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
        int L, R; // [L,R)
        SegmentTree* Left = nullptr;
        SegmentTree* Right = nullptr;
        int data;
        void combine_node(){
            data = 0;
            if(Left != nullptr){
                data += Left->data;
            } 
            if(Right != nullptr){
                data += Right->data;
            }
        }
    public:
        SegmentTree(int l, int r){
            Left = nullptr;
            Right = nullptr;
            L = l;
            R = r;
            data = 0;
        }        
        void point_update(int index){
            int M = (L + R) >> 1;
            if(L+1 == R){
                data++;
                return;
            }
            if(index < M){
                if(Left == nullptr){
                    Left = new SegmentTree(L, M);
                }
                Left->point_update(index);
                combine_node();
                return;
            } else {
                if(Right == nullptr){
                    Right = new SegmentTree(M, R);
                }
                Right->point_update(index);
                combine_node();
                return;
            }
        }
        void point_delete(int index){
            int M = (L + R) >> 1;
            if(L+1 == R && L == index){
                data--;
                return;
            }
            if(index < M){
                Left->point_delete(index);
                if (Left->data == 0) {
                    delete Left;
                    Left = nullptr;
                }
                combine_node();
                return;
            } else {
                Right->point_delete(index);
                if (Right->data == 0) {
                    delete Right;
                    Right = nullptr;
                }
                combine_node();
                return;
            }
        }
        int range_query(int ql, int qr){
            if(ql >= qr || qr <= L || ql >= R){
                return 0;
            } else if(ql == L && R == qr){
                return data;
            } else {
                int M = (L + R) >> 1;
                int Leftsum = 0, Rightsum = 0;
                if(Left != nullptr){
                    Leftsum = Left->range_query(ql,min(qr,M));
                }
                if(Right != nullptr){
                    Rightsum = Right->range_query(max(M,ql),qr);
                }
                return Leftsum + Rightsum;
            }
        }
 
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> v;
    int num;
    for(int i = 0; i < n; i++){
        cin >> num;
        v.push_back(num);
    }
    SegmentTree root = SegmentTree(0,(int)1e9 + 1);
    for(int i = 0; i < n; i++){
        root.point_update(v[i]);
    }
     
    char Q; int a, b;
    for(int i = 0; i < q; i++){
        cin >> Q >> a >> b;
        if(Q == '?'){
            cout << root.range_query(a,b+1) << nl;
        } else {
            int oldvalue = v[a-1];
            root.point_delete(oldvalue);
            int newvalue = b;
            v[a-1] = newvalue;
            root.point_update(b);
        }
    }
 
    
}
