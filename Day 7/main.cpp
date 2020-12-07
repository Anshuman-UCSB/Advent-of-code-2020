#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <utility>
using namespace std;

void part1(map<string, vector<pair<string, int>>> &m){
    int p1 = 0;
    set<string> s;
    s.insert("shiny gold");
    bool done = false;
    while(!done){
        done = true;
        for(auto& p: m){
            for(auto& b: p.second){
                if(s.find(b.first) != s.end()){
                    if(s.insert(p.first).second){
                        done = false;
                        break;
                    }
                }
            }
        }
    }
    for(auto& b: s){
        cout<<b<<endl;
    }
    cout<<"Part 1: "<<s.size()-1<<endl;
}

int getBagCount(map<string, vector<pair<string, int>>>& m, string base){
    auto& v = m[base];
    int out = 1;
    for(auto& p: v){
        out+=getBagCount(m, p.first)*p.second;
    }
    return out;
}

void part2(map<string, vector<pair<string, int>>>& m){
    cout<<"Part 2: "<<getBagCount(m, "shiny gold")-1<<endl;
}

int main(){
    map<string, vector<pair<string, int>>> m;
    fstream file("input");
    string line;
    while(getline(file, line)){
        if(line.back() == '\r'){
            line.pop_back();
        }
        stringstream ss(line);
        string a, b, base, trash;
        int num;
        ss>>a>>b>>trash>>trash;
        base = a+" "+b;
        if(ss.str().find(" no ") != string::npos){
            m[base] = {};
            cout<<base<<" is an empty bag."<<endl;
            continue;
        }
        //by here I can assume has other bags
        do{
            ss>>num>>a>>b>>trash;
            string name = a+" "+b;
            m[base].push_back(make_pair(name, num));
        }while(trash.back()==',');
    }

    for(auto& p: m){
        cout<<p.first<<": ";
        for(auto& b: p.second){
            cout<<"("<<b.first<<", "<<b.second<<") ";
        }cout<<endl;
    }
    // part1(m);
    part2(m);
}