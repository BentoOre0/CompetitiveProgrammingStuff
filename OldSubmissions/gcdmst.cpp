#include <bits/stdc++.h>
#define LSOne(S) ((S) & (-S))
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 0x3f3f3f3f;
const int NINF = 0xcfcfcfcf;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const double EPS = 1e-9;

int t, n, p;
vi A;
vii vals;
// connected[i] => is there a path from (i -- i + 1) in the MST?
// if connected[i] for all i from 0 to n - 2, the MST is connected
vector<bool> connected;

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> p;
        A.clear();
        connected.clear();
        vals.clear();
        A.resize(n);
        connected.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i];
            vals.push_back({A[i], i});
        }
        sort(vals.begin(), vals.end());

        // there are two types of edges in the graph:
        // 1. those that connect adjacent nodes (with weight p)
        // 2. those that connect i, j iff gcd(A[i:j]) = min(A[i:j])
        //    (inclusive)
        // we consider all edges of type 2 first with weight < p.
        //
        // take all values in A in increasing order
        // the edges that this value will contribute will be = val
        ll ans = 0;
        for (auto &[val, idx]: vals) {
            // not optimal to consider this value; break
            // and consider elements of type 1
            if (val >= p) break;
            // consider, for example, this array:
            // [5 3 3 6 10 100 9 15]
            //    ^ (val = 3, idx = 1)
            // where the min is highlighted as below
            // this will be the min GCD of an array that
            // contains it as long as A[k] % A[val] == 0
            // for some k
            
            // grow left first (let this growth be ptr)
            // connect node idx with nodes on the left
            // by adding the edge ptr -- idx (w/ ptr > idx)
            int ptr = idx;
            while (ptr > 0) {
                if (connected[ptr - 1]) break;
                // [9 6 3]
                //    ^ ^
                //  p-1 v
                // as long as val divides A[ptr - 1],
                // there exists an edge between (ptr - 1) to i
                // because the GCD of the subarray will be v
                // (by definition of the gcd)
                if (A[ptr - 1] % val == 0) {
                    // add the edge (ptr - 1) -- ptr
                    connected[ptr - 1] = true;
                    ans += val;
                    ptr--;
                } else {
                    break;
                }
            }
            // now consider idx -- ptr (w/ ptr > idx)
            // same arguments as above but consider rightward
            // [3 6 9]
            //  ^ ^
            //  v p+1
            ptr = idx;
            while (ptr < n - 1) {
                if (connected[ptr]) break;
                if (A[ptr + 1] % val == 0) {
                    // add the edge (ptr) -- (ptr + 1)
                    connected[ptr] = true;
                    ans += val;
                    ptr++;
                } else {
                    break;
                }
            }
        }
        // once we've considered all edges of type 2, 
        // fill in the mst with edges of type 1
        for (int i = 0; i < n - 1; i++) {
            if (!connected[i]) {
                ans += p;
            }
        }
        cout << ans << endl;
    }
    return 0;
}