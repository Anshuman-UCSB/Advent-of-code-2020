#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
using namespace std;

void part2Cleaner(){
    fstream file("input");
    string line;
    vector<string> raw;
    vector<vector<int>> groups = {vector<int>(27)};
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        raw.push_back(line);
    }
    for(int i = 0;i<raw.size();i++){
        vector<int> &active = groups.back();
        if(raw[i].empty()){
            groups.emplace_back(27);
        }else{
            active[26]++;
            for(auto c: raw[i]){
                active[c-'a']++;
            }
        }
    }
    int p2 = 0;
    for(auto& v: groups){
        for(int i = 0;i<26;i++){
            if(v[i] == v[26]){
                p2++;
            }
        }
    }
    cout<<"Part 2: "<<p2<<endl;
}

void part2(){
    fstream file("input");
    string line;
    vector<string> raw;
    vector<string> groups = {""};
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        raw.push_back(line);
    }
    for(int i = 0;i<raw.size();i++){
        if(groups.back().empty()){
            groups.back()+=raw[i];
        }else if(raw[i].empty()){
            groups.emplace_back("");
        }else{
            for(int j = 0; j<groups.back().size();j++){
                if(raw[i].find(groups.back()[j]) == string::npos){
                    groups.back().erase(groups.back().begin()+j);
                    j--;
                }
            }
        }
    }
    int p2= 0;
    for(auto l:groups){
        p2+=l.size();
        cout<<l<<endl;
    }

    cout<<"Part 2: "<< p2<<endl;
}

int main(){
    part2Cleaner();
    return 1;
    fstream file("input");
    string line;
    vector<set<char>> groups = {set<char>()};
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        if(line.empty()){
            groups.emplace_back();
        }else{
            for(auto& c: line){
                groups.back().insert(c);
            }
        }
    }
    int p1 = 0;
    for(auto& s: groups){
        p1 += s.size();
        string delim = "";
        for(auto& c: s){
            cout<<delim<<c;
            delim = ", ";
        }cout<<endl;
    }
    cout<<"Part 1: "<<p1<<endl;
}

//3289 too high