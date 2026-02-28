#include "../dsa.hpp"

using namespace std;

class Solution {
public:
    struct Debug {
        string &a;
        string &b;

        Debug(string &a_, string &b_) : a(a_), b(b_) {}

        void show() const {
            std::cout << a << std::endl;
            std::cout << b << std::endl;
        }
    };

    bool isAnagram(string s, string t) {
        if (s.size() != t.size())
            return false;

        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());

        Debug dbg(s, t);
        dbg.show();

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i])
                return false;
        }
        return true;
    }
};