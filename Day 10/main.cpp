#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <string>
using namespace std;

vector<vector<int>> split(vector<int>& p){
    vector<vector<int>> out;
    out.emplace_back();
    out.back().push_back(0);
    for(int i =1;i<p.size();i++){
        if(p[i]-p[i-1] == 3){
            out.emplace_back();
        }
        out.back().push_back(p[i]);
    }
    return out;
}

int part1(set<int>& plugs){
    vector<int> v(plugs.begin(), plugs.end());
    int regs[] = {0,0,0,0};
    for(int i = 1;i<v.size();i++){
        regs[v[i]-v[i-1]]++;
    }

    return regs[1]*regs[3];
}

void part2(set<int>& plugs){
    vector<int> v(plugs.begin(), plugs.end());
    auto s = split(v);
    for(auto& t:s){
        for(auto i:t){
            cout<<i<<" ";
        }cout<<endl;
    }
}

int main(){
    fstream file("input");
    string line;
    set<int> plugs = {0};
    int temp;
    while(getline(file, line)){
        stringstream ss(line);
        ss>>temp;
        plugs.insert(temp);
    }
    plugs.insert(*plugs.rbegin()+3);
    // cout<<part1(plugs)<<endl;
    part2(plugs);
}