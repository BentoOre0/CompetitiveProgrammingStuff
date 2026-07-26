#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
int main(){
    ordered_set OS;
    OS.insert(/node/);
    OS.find_by_order(/n/); // iterator of nth element asif 0 indexed (ascending)
    OS.order_of_key(/n/); // find the number of elements strictly less than n        
}
