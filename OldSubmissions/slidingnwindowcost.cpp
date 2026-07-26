#include <bits/stdc++.h>                                                        
using namespace std;                                                            
using ll = long long;                                                           
using pii = pair<int,int>;                                                      
using pll = pair<long long int, long long int>;                     
const int inf = numeric_limits<int>::max();                                     
const ll INF = numeric_limits<ll>::max();                                       
const char sp = ' ';                                                            
const char nl = '\n';                                                           

void balance(int count, multiset<ll, greater<ll> > &lowerhalf, multiset<ll, less<ll> > &upperhalf, pll &totals){
    ll temp;
    while(lowerhalf.size() > ((count >> 1))){
        temp = *(lowerhalf.begin());
        lowerhalf.erase(lowerhalf.begin());
        totals.first -= temp;
        upperhalf.insert(temp);
        totals.second += temp;
    }
    while(upperhalf.size() > ((count >> 1))){
        temp = *(upperhalf.begin());
        upperhalf.erase(upperhalf.begin());
        totals.second -= temp;
        lowerhalf.insert(temp);
        totals.first += temp;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<ll> vec;
    ll num;
    for(int i = 0; i < n; i++){
        cin >> num;
        vec.push_back(num);
    }
    multiset<ll, greater<ll> > lowerhalf;
    multiset<ll, less<ll> > upperhalf;
    lowerhalf.insert(vec[0]);
    int count = 1;
    pll totals = {vec[0],0};
    for(int i = 1; i < k; i++){
        count++;
        if(vec[i] < *(lowerhalf.begin())){
            lowerhalf.insert(vec[i]);
            totals.first += vec[i];
        } else {
            upperhalf.insert(vec[i]);
            totals.second += vec[i];
        }
        // cout << lowerhalf.size() << sp << upperhalf.size() << nl;
        // cout << *(lowerhalf.begin()) << sp << *(upperhalf.begin()) << nl;
        // cout << nl;
        balance(count, lowerhalf, upperhalf, totals);
    }
    ll L = 0;
    for(int R = k - 1; R < n; R++){
        ll median;
        if(lowerhalf.size() >= upperhalf.size()){
            median = *(lowerhalf.begin());
        } else {
            median = *(upperhalf.begin());
        }
        // cout << totals.first << sp << totals.second << sp << median << nl;
        cout << llabs(totals.first - (ll)lowerhalf.size() * median) + abs(totals.second - (ll)upperhalf.size() * median) << sp;
        // cout << nl;
        if(lowerhalf.count(vec[L])){
            auto it = lowerhalf.find(vec[L]);
            lowerhalf.erase(it);
            totals.first -= vec[L];
        } else {
            auto it = upperhalf.find(vec[L]);
            upperhalf.erase(it);
            totals.second -= vec[L];
        }
        balance(k, lowerhalf, upperhalf, totals);
        if(R < n - 1){
            if(vec[R + 1] < *(lowerhalf.begin())){
                lowerhalf.insert(vec[R + 1]);
                totals.first += vec[R + 1];
            } else {
                upperhalf.insert(vec[R + 1]);
                totals.second += vec[R + 1];
            }
            balance(k, lowerhalf, upperhalf, totals);
        }
        L++;
        
    }
    
}