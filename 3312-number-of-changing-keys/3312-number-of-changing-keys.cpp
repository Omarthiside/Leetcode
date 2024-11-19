class Solution {
public:
    int countKeyChanges(string s) {
        if(s.empty()){
            return 0;
        }
        int changes=0;
        char lastKey = tolower(s[0]);

        for (int i = 1; i < s.length(); ++i) {

            char currentKey = tolower(s[i]);


            if (currentKey != lastKey) {
                ++changes;
                lastKey=currentKey;
            }
        }
        return changes;

        
    }
};