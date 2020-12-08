#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>
#include <stack>
using namespace std;

bool loops(vector<pair<string, int>> &r){
    set<int> visited;
    int i = 0;
    string instr;
    while(visited.insert(i).second){
        // cout<<"On step "<<i+1<<endl;
        if(i == r.size()){
            return false;
        }
        if(i > r.size()){
            return true;
        }
        instr = r[i].first;
        if(instr == "nop"){
            i++;
        }else if(instr == "acc"){
            i++;
        }else if(instr == "jmp"){
            i+=r[i].second;
        }
    }
    return true;
}
int eval(vector<pair<string, int>> &r){
    int i(0), acc(0);
    string instr;
    while(i!=r.size()){
        // cout<<"On step "<<i+1<<endl;
        instr = r[i].first;
        if(instr == "nop"){
            i++;
        }else if(instr == "acc"){
            acc+=r[i].second;
            i++;
        }else if(instr == "jmp"){
            i+=r[i].second;
        }
    }
    return acc;
}
void part2(vector<pair<string, int>> &r){
    for(int i = 0;i<r.size();i++){
        if(r[i].first == "jmp" || r[i].first == "nop"){
            auto t = r;
            t[i].first = (r[i].first == "jmp"?"nop":"jmp");
            // for(auto &p: t){
            //     cout<<p.first<<": " <<p.second<<endl;
            // }cout<<"---"<<endl;
            if(!loops(t)){
                cout<<"Part 2: "<<eval(t)<<endl;
            }
        }
    }
    
}

void part1(vector<pair<string, int>> &r){
    set<int> visited;
    int i = 0;
    int acc = 0;
    string instr;
    while(visited.insert(i).second){
        // cout<<"On step "<<i+1<<endl;
        instr = r[i].first;
        if(instr == "nop"){
            i++;
        }else if(instr == "acc"){
            acc+=r[i].second;
            i++;
        }else if(instr == "jmp"){
            i+=r[i].second;
        }
    }
    cout<<"Part 1: "<<acc<<endl;
}

int main(){
    fstream file("input");
    string line;
    vector<pair<string, int>> raw;
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        stringstream ss(line);
        string a;
        int b;
        ss>>a>>b;
        raw.push_back(make_pair(a,b));
    }
    // for(auto p: raw){
    //     cout<<p.first<<": " <<p.second<<endl;
    // }
    part2(raw);
}