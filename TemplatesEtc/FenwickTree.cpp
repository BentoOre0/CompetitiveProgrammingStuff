#define LSOne(S) ((S) & -(S))

class PURQTree{
    private:
        vector<int> tree;
        int sz;
   
    public:
        PURQTree() {}
        PURQTree(int n) : sz(n), tree(2 * n, 0) {}
        PURQTree(vector<int> nums){
            sz = nums.size();
            tree.assign(2 * sz, 0);
            for(int i = 0; i < sz; i++){
                tree[i + 1] = nums[i];
            }
            for(int i = 1; i <= sz; i++){
                if(i + LSOne(i) > sz) {
                    continue;
                }
                tree[i + LSOne(i)] += tree[i];
            }
        }
        int query(int i){
            int sum = 0;
            while(i > 0) {
                sum += tree[i];
                i -= LSOne(i);
            }
            return sum;
        }
        int rangequery(int i, int j){
            return query(j) - query(i - 1);
        }
        void pointupdate(int i, int k){
            while(i <= sz){
                tree[i] += k;
                i += LSOne(i);
            }
        }
};

