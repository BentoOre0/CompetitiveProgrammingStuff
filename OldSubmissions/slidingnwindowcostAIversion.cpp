#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class MedianFinder {
private:
    multiset<ll, greater<ll>> lowerHalf;  // max heap
    multiset<ll, less<ll>> upperHalf;     // min heap
    ll lowerSum = 0;
    ll upperSum = 0;
    
    void rebalance(int windowSize) {
        // Ensure size difference is at most 1
        while (lowerHalf.size() > (windowSize + 1) / 2) {
            ll value = *lowerHalf.begin();
            lowerHalf.erase(lowerHalf.begin());
            lowerSum -= value;
            upperHalf.insert(value);
            upperSum += value;
        }
        
        while (upperHalf.size() > windowSize / 2) {
            ll value = *upperHalf.begin();
            upperHalf.erase(upperHalf.begin());
            upperSum -= value;
            lowerHalf.insert(value);
            lowerSum += value;
        }
    }
    
public:
    void add(ll num) {
        if (lowerHalf.empty() || num < *lowerHalf.begin()) {
            lowerHalf.insert(num);
            lowerSum += num;
        } else {
            upperHalf.insert(num);
            upperSum += num;
        }
    }
    
    void remove(ll num) {
        auto it = lowerHalf.find(num);
        if (it != lowerHalf.end()) {
            lowerHalf.erase(it);
            lowerSum -= num;
        } else {
            it = upperHalf.find(num);
            upperHalf.erase(it);
            upperSum -= num;
        }
    }
    
    ll getDeviationSum() {
        ll median = lowerHalf.size() >= upperHalf.size() ? 
                   *lowerHalf.begin() : *upperHalf.begin();
                   
        return llabs(lowerSum - (ll)lowerHalf.size() * median) + 
               llabs(upperSum - (ll)upperHalf.size() * median);
    }
    
    void balance(int windowSize) {
        rebalance(windowSize);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<ll> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    
    MedianFinder finder;
    
    // Initialize first window
    for (int i = 0; i < k; i++) {
        finder.add(numbers[i]);
        finder.balance(i + 1);
    }
    
    // Process all windows
    for (int right = k - 1; right < n; right++) {
        cout << finder.getDeviationSum() << ' ';
        
        if (right < n - 1) {
            // Remove leftmost element of current window
            finder.remove(numbers[right - k + 1]);
            finder.balance(k - 1);
            
            // Add next element
            finder.add(numbers[right + 1]);
            finder.balance(k);
        }
    }
    
    return 0;
}