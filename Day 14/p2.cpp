#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
using namespace std;

struct mask{
    string msk;
    mask(){msk="";}
    mask(string inp){
        stringstream ss(inp);
        string trash;
        ss>>trash>>trash>>msk;
    }

    vector<string> translate(string inp){
        vector<string> out;
        // cout<<msk<<endl;
        // cout<<inp<<endl;
        for(int i = 0;i<inp.size();i++){
            inp[i]=msk[i]=='0'?inp[i]:msk[i];
        }
        out.push_back(inp);
        // cout<<"Start iter: "<<out[0]<<endl;
        for(int i =0 ;i<out.size();i++){
            int pos = out[i].find("X");
            if(pos != string::npos){
                out.push_back(out[i]);
                out.back()[pos]='0';
                out.push_back(out[i]);
                out.back()[pos]='1';
                out.erase(out.begin()+i);
                i = -1;
            }
        }
        return out;
    }
};

int main(){
    map<string, long> mp;
    // mask m(       "mask = 000000000000000000000000000000X1001X");
    // auto v = m.translate("000000000000000000000000000000101010");
    // for(auto l:v){
    //     cout<<l<<endl;
    // }
    fstream file("input");
    string line;
    mask msk;
    while(getline(file, line)){
        if(line[1] == 'a'){
            msk = mask(line);
        }else{
            string l;
            int temp, r;
            stringstream ss(line);
            char c;
            ss>>c>>c>>c>>c>>temp>>c>>l>>r;
            vector<string> ads = msk.translate(bitset<36>(temp).to_string());
            for(auto& l: ads){
                mp[l] = r;
            }
        }
    }
    long long p2 = 0;
    for(auto& p: mp){
        p2+=p.second;
    }
    cout<<"Part 2: "<<p2<<endl;
}