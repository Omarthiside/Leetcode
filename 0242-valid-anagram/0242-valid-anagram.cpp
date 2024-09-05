class Solution {
public:
    bool isAnagram(string s, string t) {
        int freq[26]={};
        for(int i=0;s[i]!='\0';i++){
            freq[s[i]-'a']++;
        }
        int freq1[26]={};
        for(int i=0;t[i]!='\0';i++){
            freq1[t[i]-'a']++;
        } 
        for(int i=0;i<26;i++){
            if(freq[i]!=freq1[i]){
                return false;
            }
        }
        return true;
    }

        
};
