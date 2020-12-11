#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

ostream& operator<<(ostream& os, const vector<vector<int>>& mp){
    for(auto& r:mp){
        for(auto c:r){
            switch(c){
                case -1:os<<".";break;
                case  0:os<<"L";break;
                case  1:os<<"#";break;
            }
        }os<<endl;
    }
    return os;
}

string toString(vector<vector<int>>& mp){
    string build = "";
    for(auto& r:mp){
        for(auto c: r){
            build+=to_string(c);
        }
    }
    return build;
}

vector<vector<int>> iterate(vector<vector<int>>& mp){
    vector<vector<int>> out(mp);
    for(int i = 0;i<mp.size();i++){
        for(int j = 0;j<mp[i].size();j++){
            int adj = 0;
            if(mp[i][j] == 0){
                for(int dx = -1;dx<=1;dx++)
                    for(int dy = -1;dy<=1;dy++){
                        if(0<=i+dy &&i+dy<mp.size() && 0<=j+dx && j+dx<mp[i].size())
                            adj+=max(0,mp[i+dy][j+dx]);
                    }
                if(adj == 0){
                    out[i][j] = 1;
                }
            }else if(mp[i][j] == 1){
                adj--; //since its own seat is occupied
                for(int dx = -1;dx<=1;dx++)
                    for(int dy = -1;dy<=1;dy++){
                        if(0<=i+dy &&i+dy<mp.size() && 0<=j+dx && j+dx<mp[i].size())
                            adj+=max(0,mp[i+dy][j+dx]);
                    }
                if(adj >=4){
                    out[i][j] = 0;
                }
            }
        }
    }
    return out;
}

vector<vector<int>> iterate2(vector<vector<int>>& mp){
    vector<vector<int>> out(mp);
    for(int i = 0;i<mp.size();i++){
        for(int j = 0;j<mp[i].size();j++){
            int adj = 0;
            if(mp[i][j] == 0){
                for(int dx = -1;dx<=1;dx++)
                    for(int dy = -1;dy<=1;dy++){
                        int mod;
                        for(mod = 1;0<=i+mod*dy && i+mod*dy<mp.size() && 0<=j+mod*dx && j+mod*dx<mp[i].size() && (mp[i+mod*dy][j+mod*dx] == -1); mod++){}
                        if(0<=i+mod*dy &&i+mod*dy<mp.size() && 0<=j+mod*dx && j+mod*dx<mp[i].size()){
                            adj+=mp[i+mod*dy][j+mod*dx];
                        }
                    }
                if(adj == 0){
                    out[i][j] = 1;
                }
            }else if(mp[i][j] == 1){
                adj--; //since its own seat is occupied
                for(int dx = -1;dx<=1;dx++)
                    for(int dy = -1;dy<=1;dy++){
                        int mod;
                        for(mod = 1;0<=i+mod*dy && i+mod*dy<mp.size() && 0<=j+mod*dx && j+mod*dx<mp[i].size() && (mp[i+mod*dy][j+mod*dx] == -1); mod++){}
                        if(0<=i+mod*dy &&i+mod*dy<mp.size() && 0<=j+mod*dx && j+mod*dx<mp[i].size()){
                            adj+=mp[i+mod*dy][j+mod*dx];
                        }
                    }
                    if(adj >=5){
                        out[i][j] = 0;
                }
            }
        }
    }
    return out;
}

int main(){
    vector<string> raw;
    fstream file("input");
    string line;
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        raw.push_back(line);
    }
    vector<vector<int>> mp;
    for(auto& l: raw){
        mp.emplace_back();
        for(auto c: l){
            switch(c){
                case 'L': mp.back().push_back(0); break;
                case '#': mp.back().push_back(1); break;
                case '.': mp.back().push_back(-1); break;
            }
        }
    }


    // PART 1
    // auto temp = iterate(mp);
    // string old = toString(mp);
    // while(toString(temp) != old){
    //     old = toString(temp);
    //     temp = iterate(temp);        
    //     // cout<<temp<<endl<<" ----- "<<endl;
    // }
    // int p1 = 0;
    // for(auto& r: temp){
    //     for(auto c: r){
    //         p1+=max(c,0);
    //     }
    // }
    // cout<<"Part 1: "<<p1<<endl;

    // PART 2
    auto temp = iterate2(mp);
    string old = toString(mp);
    while(toString(temp) != old){
        old = toString(temp);
        temp = iterate2(temp);        
        // cout<<temp<<endl<<" ----- "<<endl;
    }
    int p2 = 0;
    for(auto& r: temp){
        for(auto c: r){
            p2+=max(c,0);
        }
    }
    cout<<"Part 2: "<<p2<<endl;
}