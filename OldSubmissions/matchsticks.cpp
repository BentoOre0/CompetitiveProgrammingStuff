#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long,long long>;
const char nl = '\n';
const char sp = ' ';
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();

//crappy dp, can optimise to chars if needed
ll GCD(ll A, ll B){
    cout << A << sp << B << nl;
    if(B == 0){
        return A;
    } else {
        return GCD(B,A % B);
    }
}

vector<char> nums = {'1','2','3','4','5','6','7','8','9','0'};
vector<int> cost = {2,5,5,4,5,6,3,7,6,6};

string best(string a, string b){
    if(a.size() > b.size()){
        return a;
    } else if(b.size() > a.size()){
        return b;
    } else{
        if(a > b){
            return a;
        } else {
            return b;
        }
    }
}

string worst(string a, string b){
    if(a.size() < b.size()){
        return a;
    } else if(b.size() < a.size()){
        return b;
    } else{
        if(a < b){
            return a;
        } else {
            return b;
        }
    }
}
string mx[51][101];
string mn[51][101];
int startingsticks;
string maxim(int index, int sticks){
    if(index == 50 || sticks < 0 || sticks == 1){
        return "";
    }
    if(mx[index][sticks] != "."){
        return mx[index][sticks];
    } else {
        string value = "";
        for(int i = 0; i < 10; i++){
            if(sticks == startingsticks && i == 9){
                continue;
            }
            if(sticks - cost[i] == 1 || sticks - cost[i] < 0){
                continue;
            }
            string a = best(nums[i] + maxim(index, sticks - cost[i]),nums[i] + maxim(index + 1, sticks - cost[i]));
            value = best(value,a);
        }
        mx[index][sticks] = value;
        return mx[index][sticks];
    }
}

string minim(int index, int sticks){
    if(index == 50 || sticks < 0 || sticks == 1){
        return "";
    }
    if(mn[index][sticks] != "."){
        return mn[index][sticks];
    } else {
        string value = "";
        for(int i = 0; i < 10; i++){
            if(sticks == startingsticks && i == 9){
                continue;
            }
            if(sticks - cost[i] == 1 || sticks - cost[i] < 0){
                continue;
            }
            string a = worst(nums[i] + minim(index, sticks - cost[i]),nums[i] + minim(index + 1, sticks - cost[i]));
            if(value == ""){
                value = a;
            } else {
                value = worst(value,a);
            }
        }
        mn[index][sticks] = value;
        return mn[index][sticks];
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    int num;
    while(t--){
        for(int i = 0; i < 51; i++){
            for(int j = 0; j < 101; j++){
                mx[i][j] = ".";
                mn[i][j] = ".";
            }
        }
        cin >> num;
        startingsticks = num;
        cout << minim(0,num) << sp << maxim(0,num) << nl;
        // break;
    }
    
}