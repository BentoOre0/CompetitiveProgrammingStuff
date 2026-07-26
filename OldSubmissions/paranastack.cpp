#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';

//I am black boxing this and tweeking from geeks for geeks lul
ll merge(vector<ll> &arr, vector<ll> &temp, int left, int mid, int right){
    ll inv_count = 0;
    int i = left;
    int j = mid;
    int k = 0;
    while((i <= mid - 1) && (j <= right)){
        if(arr[i] <= arr[j]){
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i);
        }
    }
    while(i <= mid - 1){
        temp[k++] = arr[i++];
    }

    while(j <= right){
        temp[k++] = arr[j++];
    }
    k = 0;
    for(i = left; i <= right; i++){
        arr[i] = temp[k++];
    }
    return inv_count;
}

ll _mergeSort(vector<ll> &arr, vector<ll> &temp, int left, int right){
    int mid;
    ll inv_count = 0;
    if(right > left){
        mid = (left + right)/2;
        inv_count = _mergeSort(arr,temp,left,mid);
        inv_count += _mergeSort(arr,temp,mid+1,right);
        inv_count += merge(arr,temp,left,mid+1,right);
    }
    return inv_count;
}

ll countswapstoSort(vector<ll> &arr, int s, int e){
    vector<ll> temp(e - s + 1,0);
    return _mergeSort(arr,temp,s,e);
}

int main() {
    int S, T;
    cin >> S >> T;
    if(S == 0){
        vector<ll> TT;
        int num;
        for(int i = 0; i < T; i++){
            cin >> num;
            TT.push_back(num);
        }
        ll ans;
        if(T == 0){
            ans = 1;
        } else {
            ans = 2*countswapstoSort(TT,0,T-1) + T + 1;
        }
        cout << ans << nl;
    } else {
        if(T == 0){
            cout << 1 << nl;
        } else {
            vector<ll> space;
            space.reserve(S+T);
            vector<ll> SS(S),TT(T);
            ll num;
            for(int i = 0; i < S; i++){
                cin >> num;
                SS[i] = num;
            }
            reverse(SS.begin(),SS.end());
            for(int i = 0; i < T; i++){
                cin >> num;
                TT[i] = num;
            }
            ll minimum = INF;
            for(int i = 0; i < T; i++){
                minimum = min(TT[i],minimum);
            }
            int idtoget = -1;
            for(int i = S - 1; i >= 0; i--){
                if(SS[i] <= minimum){
                    idtoget = i;
                    break;
                }
            }
            for(ll elem: SS){
                space.push_back(elem);
            }
            for(ll elem: TT){
                space.push_back(elem);
            }
            ll ans;
            if(idtoget == -1){
                ll bruh = 2*countswapstoSort(space,0,space.size() - 1);
                ans = bruh + TT.size() + 1;
            } else {
                ll bruh = 2*countswapstoSort(space,idtoget,space.size() - 1);
                ans = bruh + TT.size() + 1;
                // cout << idtoget << sp << bruh << nl;
            }
            cout << ans<< nl;
        }
    }
    //IDEA SEGMENT SORTING USING MERGE SORT
}