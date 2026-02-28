#include "../dsa.hpp"

using namespace std;

class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        std::unordered_map<int, int> hashmap;
    
        for (int n: nums){
            if (hashmap[n])
                return true;
            hashmap[n] = true;
        }
        return false;
    }

};

