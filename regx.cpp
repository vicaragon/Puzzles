#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        return matchhelper(s,0,p,0);
    }
    
    bool matchhelper(string& s, int sid, string& p, int pid) {
        char sletter, pletter;
        while (sid < s.size() && pid < p.size()) {
            sletter = s[sid];
            pletter = p[pid];
            if (pletter == '*') break;
            if (pletter == '.' || sletter == pletter) {
                sid ++;
                pid ++;
            } else {
                if (pid+1 < p.size() && p[pid+1] == '*' && matchhelper(s,sid+1,p,pid+1)) return true;
                else return false;
            }
        }
        if (sid >= s.size() && pid >= p.size()) return true;
        if (pid >= p.size()) return false;
        pletter = p[pid];
        
        bool starMatch = false;
        
        if (pletter == '*') {
            if (pid == 0) return false;
            char pprevious = p[pid-1];
            sid --;
            if (pprevious == '*') return false;
            int starCount = 0;
            while ( sid+starCount < s.size()+1 && !starMatch) {
                if (pprevious != '.') {
                    cout << "starCount: " << starCount<<endl;
                    for (int i = 0; i < starCount; i++) {
                        if (s[sid+i] == '*') {
                            if (sid+i == 0) {
                                starMatch = false;
                                break;
                            }
                            if (s[sid+i-1]=='.') {
                                starMatch = true;
                                continue;
                            }
                            if (pprevious != s[sid+i-1]) {
                                starMatch = false;
                                break;
                            } starMatch = true;
                        } else if (s[sid+i] == '.') starMatch = true;
                        else {
                            if (pprevious == s[sid+i]) starMatch = true;
                            else {
                                starMatch = false;
                                break;
                            }
                        }
                    }
                    if (starCount == 0) starMatch = true;
                } else starMatch = true;
                //cout << starMatch << endl;
                if (starMatch) starMatch = matchhelper(s,sid+starCount,p,pid+1);
                starCount++;
            }
            if (starMatch) return true;
        }
        
        if (sid >= s.size()) return false;

        return starMatch;
    }
};

int main(int argc, const char** argv) {
    Solution solution;
    cout << solution.isMatch("a","a*") << endl;
}