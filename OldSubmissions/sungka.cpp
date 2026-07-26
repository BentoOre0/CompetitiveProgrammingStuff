#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
/*
LEFT MOST
            \/
0 0 0 0 3 0 0
0 1 0 0 0 0 5

LEFT MOST
              \/
  0 1 2 3 4 5 6 7
7 6 5 4 3 2 1 0
  /\

0 0 0 0 3 0 0 ULO
5 0 0 0 0 1 0 ULO
*/

vector<int> opposite = {6,5,4,3,2,1,0};


int findplace(int num, const vector<ll>& barbie, const vector<ll>& jak){
    if(num == 0){
        ll temp = INF;
        int id = -1;
        for(int i = 6; i >= 0; i--){
            if(barbie[i] < temp && barbie[i] != 0){
                id = i;
                temp = barbie[i];
            }
        }
        return id;
    } else {
        ll temp = INF;
        int id = -1;
        for(int i = 6; i >= 0; i--){
            if(jak[i] < temp && jak[i] != 0){
                id = i;
                temp = jak[i];
            }
        }
        return id;
    }
}

pii barbie_move(ll shells, int id, int p, vector<ll>& barbie, vector<ll>& jak){
    if(p == 1){
        jak[id] = 0;
    } else {
        barbie[id] = 0;
    }
    ll rem = shells % 15;
    ll norm = shells / 15;
    for(int i = 0; i < 8; i++){
        barbie[i] += norm;
    }
    for(int i = 0; i < 7; i++){
        jak[i] += norm;
    }
    int sid = id, P = p;
    while(rem){
        sid++;
        rem--;
        if(sid == 8 && P == 0){
            sid = 0;
            P = 1;
        }
        if(sid == 7 && P == 1){
            sid = 0;
            P = 0;
        }
        if(P == 0){
            barbie[sid]++;
        } else {
            jak[sid]++;
        }
    }
    if(sid != 7){
        if(P == 0){
            if(barbie[sid] > 1){
                ll temp = barbie[sid];
                barbie[sid] = 0;
                return barbie_move(temp, sid, P, barbie, jak);
            }
        }
        if(P == 1){
            if(jak[sid] > 1){
                ll temp = jak[sid];
                jak[sid] = 0;
                return barbie_move(temp, sid, P, barbie, jak);
            }
        }
    }
    return {P,sid};
}

pii jak_move(ll shells, int id, int p, vector<ll>& barbie, vector<ll>& jak){
    if(p == 1){
        jak[id] = 0;
    } else {
        barbie[id] = 0;
    }

    ll rem = shells % 15;
    ll norm = shells / 15;
    for(int i = 0; i < 8; i++){
        jak[i] += norm;
    }
    for(int i = 0; i < 7; i++){
        barbie[i] += norm;
    }
    int sid = id, P = p;
    while(rem){
        sid++;
        rem--;
        if(sid == 8 && P == 1){
            sid = 0;
            P = 0;
        }
        if(sid == 7 && P == 0){
            sid = 0;
            P = 1;
        }
        if(P == 0){
            barbie[sid]++;
        } else {
            jak[sid]++;
        }
    }
    if(sid != 7){
        if(P == 0){
            if(barbie[sid] > 1){
                ll temp = barbie[sid];
                barbie[sid] = 0;
                return jak_move(temp, sid, P, barbie, jak);
            }
        }
        if(P == 1){
            if(jak[sid] > 1){
                ll temp = jak[sid];
                jak[sid] = 0;
                return jak_move(temp, sid, P, barbie, jak);
            }
        }
    }
    return {P,sid};
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<ll> barbie(8, 0), jak(7, 0);
    for(int i = 0; i < 7; i++){
        cin >> barbie[i];
    }
    for(int i = 0; i < 7; i++){
        cin >> jak[i];
    }
    reverse(jak.begin(), jak.end());
    jak.push_back(0);
     while(true){
         int a = findplace(0,barbie,jak);
         while(a != -1){
             pii end = barbie_move(barbie[a],a,0,barbie,jak);
             if(end.first == 0 && end.second != 7){
                 if(barbie[end.second] == 1 && jak[opposite[end.second]] > 0){
                     barbie[7] += barbie[end.second];
                     barbie[7] += jak[opposite[end.second]];
                     barbie[end.second] = 0;
                     jak[opposite[end.second]] = 0;
                     break;
                 } else {
                     break;
                 }
             } else if(end.second == 7){
                 a = findplace(0,barbie,jak);
             } else {
                 break;
             }
         }
         int b = findplace(1,barbie,jak);
         while(b != -1){
             pii end = jak_move(jak[b],b,1,barbie,jak);
             if(end.first == 1 && end.second != 7){
                 if(jak[end.second] == 1 && barbie[opposite[end.second]] > 0){
                     jak[7] += jak[end.second];
                     jak[7] += barbie[opposite[end.second]];
                     jak[end.second] = 0;
                     barbie[opposite[end.second]] = 0;
                     break;
                 } else {
                     break;
                 }
             } else if(end.second == 7){
                 b = findplace(1,barbie,jak);
             } else {
                 break;
             }
         }
         if(a == -1 && b == -1){
             break;
         }
     }
    // cout << nl;
    cout << barbie[7] << sp << jak[7] << nl;
}
