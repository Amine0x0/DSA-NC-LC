#include "../dsa.hpp"

#define DEBUG_NUMS {1,2,3,4,5,56,6,7,7,5,4,4,23,23,23,}

struct Data{
    std::vector<int> nums = DEBUG_NUMS;
};

typedef enum{
    MERGE,
    BUBBLE,
}   methods;

namespace Debug{
    void check(std::vector<int>& nums, ssize_t bonus){
        for (auto n : nums)
            std::cout << " >> " << n;
        std::cout << std::endl;
        std::cout << "Sorted in " << bonus << " comparisons" << std::endl;
    }

    void log(methods m){
        switch (m){
            case MERGE:
                std::cout << "[MERGE SORT]" << std::endl;
                break;
            case BUBBLE:
                std::cout << "[BUBBLE SORT]" << std::endl;
                break;
            default:
                break;
        }
    }
}

class Solution{
private:
    Data &data;
    ssize_t move_counter = 0;

    void swap(int &a, int &b){
        int temp = a;
        a = b;
        b = temp;
    }

        void merge(std::vector<int>& arr, int left, int mid, int right){
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);
        for(int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for(int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while(i < n1 && j < n2){
            move_counter++;
            if(L[i] <= R[j]){
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        while(i < n1) arr[k++] = L[i++];
        while(j < n2)  arr[k++] = R[j++];
    }

    void merge_sort(std::vector<int>& arr, int left, int right){
        if(left >= right) return;
        int mid = left + (right - left)/2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }

public:
    Solution(Data& data) : data(data) {}

    ssize_t bubble_solve(){
        move_counter = 0;
        std::vector<int>& current = data.nums;
        for (int i = 0; i < current.size(); i++){
            for (int j = i + 1; j < current.size(); j++){
                move_counter++;
                if (current[i] > current[j])
                    swap(current[i], current[j]);
            }
        }
        return move_counter;
    }

    ssize_t merge_solve(){
        move_counter = 0;
        merge_sort(data.nums, 0, data.nums.size() - 1);
        return move_counter;
    }
};

int main(){
    {
        Data data;
        Solution S(data);
        Debug::log(BUBBLE);
        ssize_t moves = S.bubble_solve();
        Debug::check(data.nums, moves);
    }

    {
        Data data;
        Solution S(data);
        Debug::log(MERGE);
        ssize_t moves = S.merge_solve();
        Debug::check(data.nums, moves);
    }
}