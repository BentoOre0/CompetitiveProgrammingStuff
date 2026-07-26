#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        deque<int> origA,origB;
        int num;
        for(int i = 0; i < n; i++){
            cin >> num;
            origA.push_front(num);
        }
        int m;
        cin >> m;
        for(int i = 0; i < m; i++){
            cin >> num;
            origB.push_front(num);
        }
        vector<ll> rs;
        for(int k = 1; k <= m + n; k++){
            ll count = 0;
            unordered_set<int> inA,inB;
            deque<int> A,B;
            for(int j = n - 1; j >= 0; j--){
                A.push_front(origA[j]);
                inA.insert(origA[j]);
            }
            for(int j = m - 1; j >= 0; j--){
                B.push_front(origB[j]);
                inB.insert(origB[j]);
            }
            for(int finding = 1; finding <= m+n; finding++){
                if(finding == k){
                    continue;
                } else {
                    if(inA.count(finding)){
                        while(A.front() != finding){
                            int f = A.front();
                            A.pop_front();
                            inA.erase(f);
                            B.push_front(f);
                            inB.insert(f);
                            count++;
                        }
                        A.pop_front();
                        inA.erase(finding);
                    } else if(inB.count(finding)){
                        while(B.front() != finding){
                            int f = B.front();
                            B.pop_front();
                            inB.erase(f);
                            A.push_front(f);
                            inA.insert(f);
                            count++;
                        }
                        B.pop_front();
                        inB.erase(finding);
                    }
                    // cout << count << nl;
                }
            }
            rs.push_back(count);
            // break;
        }
        for(int i = 0; i < rs.size(); i++){
            cout << rs[i] << sp;
        }
        cout << nl;
    }
}