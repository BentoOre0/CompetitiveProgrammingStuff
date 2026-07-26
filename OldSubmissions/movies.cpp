#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = 1e18;
const char sp = ' ';
const char nl = '\n';

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<pll> movies;
    // map<ll,ll> peopletimes;
    for(int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b;
        movies.push_back({b,a});
    }
    sort(movies.begin(), movies.end());

    map<ll,int> mp;
    mp[0] = k;
    int ans = 0;
    for(int i = 0; i < n; i++){
        auto [timeend, timestart] = movies[i];
        auto it = mp.upper_bound(timestart);
        if(it == mp.begin()){
            continue;
        } else {
            it--;
            ans++;
            auto [time,number] = *it;
            mp[time]--;
            mp[timeend]++;
            if(!mp[time]){
                mp.erase(time);
            }
        }
    }
    cout << ans << nl;

}
