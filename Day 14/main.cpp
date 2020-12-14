#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <bitset>
using namespace std;

struct mask{

    vector<int> adj;
    string bMask;
    mask(){}

    mask(string inp){
        stringstream ss(inp);
        string temp;
        ss>>temp>>temp>>temp;
        for(auto c: temp)
            adj.push_back(c!='X'?c-'0':-1);
        bMask = temp;
        // -1 means do nothing
    }

    vector<long long> translate2(int inp){
        string bInp = bitset<36>(inp).to_string();
        //bMask
        for(int i = 0;i<bInp.size();i++){
            bInp[i] = bMask[i]==0?bInp[i]:bMask[i];
        }
        vector<string> temp = {bInp};
        for(int i = 0;i<temp.size();i++){
            if(temp[i].find("X")!=string::npos){
                string tString = temp[i];
                temp.erase(temp.begin()+i);
                i = 0;
                for(int j = 0;j<tString.size();j++){
                    if(tString[j] == 'X'){
                        temp.emplace_back(tString);
                        temp.back()[j]=0;
                        temp.emplace_back(tString);
                        temp.back()[j]=1;
                    }
                }
            }
        }
        vector<long long> out;
        for(auto& s: temp){
            out.emplace_back(bitset<36>(s).to_ulong());
        }
        return out;
    }

    long long translate(long long inp){
        vector<int> v(36);
        int ind = 35;
        while(inp>0){
            v[ind--]=inp%2;
            inp/=2;
        }
        for(int i = 0;i<adj.size();i++){
            v[i] = adj[i]!=-1?adj[i]:v[i];
        }
        long long mult = 1;
        long long out = 0;
        for(int i = adj.size()-1;i>=0;i--){
            out+=mult*v[i];
            mult*=2;
        }
        return out;
    }
};

void part2(){
    mask msk("mask = 000000000000000000000000000000X1001X");
    auto a = msk.translate2(14);
    for(auto l: a){
        cout<<l<<endl;
    }
    // cout<<a<<endl;
    // msk.translate2(14);
}

void part1(){
    map<int, long long> m;
    fstream file("input");
    string line;
    mask msk;
    while(getline(file, line)){
        if(line[1] == 'a'){
            msk = mask(line);
        }else{
            int a;
            long long b;
            stringstream ss(line);
            string trsh;
            char trash;
            ss>>trash>>trash>>trash>>trash>>a>>trsh>>trsh>>b;
            // cout<<a<<", "<<b<<endl;
            m[a]=msk.translate2(b)[0];
        }
    }
    long long int p1 = 0; 
    for(auto& p: m){
        // cout<<p.first<<" - "<<p.second<<endl;
        p1+=p.second;
    }
    cout<<"Part 1: "<<p1<<endl; //-365233965380
    // mask m("mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X");
    // cout<<m.translate(101)<<endl;
}

int main(){
    part2();
}