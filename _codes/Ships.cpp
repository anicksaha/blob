#include <bits/stdc++.h>

string solution(int N, string &S, string &T) {
    
    int ship_hit = 0;
    int ship_sunk = 0;
    
    set<pair<int, int> > _set;
    int idx = 0;
    while(idx<T.length()) {
        int x = T[idx++]-'0';
        if(T[idx]>=48 && T[idx]<=57) {
            x*=10;
            x+=T[idx++]-'0';    
        }
        int y = T[idx++]-'A'; y++;
        _set.insert(make_pair(x,y));        
        idx++;
    }
    
    idx = 0;
    while(idx<S.length()) {
        int x1 = S[idx++]-'0';
        
        if(S[idx]>=48 && S[idx]<=57) {
            x1*=10;
            x1+=S[idx++]-'0';    
        }
        int y1 = S[idx++]-'A'; y1++;
        
        idx++;
        int x2 = S[idx++]-'0';
        if(S[idx]>=48 && S[idx]<=57) {
            x2*=10;
            x2+=S[idx++]-'0';    
        }
        
        int y2 = S[idx++]-'A'; y2++;
        idx++;
    
        int tot = 0;
        int hit = 0;
        
        for(int _i=x1;_i<=x2;_i++) {
            for(int _j=y1;_j<=y2;_j++) {
                tot++;
                if(_set.find(make_pair(_i,_j))!=_set.end()) {
                    hit++;
                }
            }
        }
        if(tot==hit) ship_sunk++;
        else if(hit>0) ship_hit++;
    }
    
    return to_string(ship_sunk) + "," + to_string(ship_hit);
}
