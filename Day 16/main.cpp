#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
using namespace std;
void p1();
void p2();

struct Rule{
    string name;
    vector<pair<int, int>> ranges;
    Rule(){};
    Rule(vector<pair<int, int>> range, string n):ranges(range), name(n){}
};

vector<int> readTicket(string inp){
    stringstream ss(inp);
    int temp;
    char c;
    ss>>temp;
    vector<int> out = {temp};
    while(ss>>c>>temp){
        out.push_back(temp);
    }
    return out;
}

vector<vector<int>> inputTickets(){
    fstream file("input");
    string line;
    vector<vector<int>> out;
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        line.push_back(',');
        out.emplace_back();
        stringstream ss(line);
        int temp;
        char c;
        while(ss>>temp>>c){
            out.back().push_back(temp);
        }
    }
    return out;
}

vector<Rule> rules(){
    vector<Rule> out;
    out.emplace_back(vector<pair<int, int>>{make_pair(40,261), make_pair(279,955)}, "departure location");
    out.emplace_back(vector<pair<int, int>>{make_pair(33,375), make_pair(394,963)}, "departure station");
    out.emplace_back(vector<pair<int, int>>{make_pair(39,863), make_pair(877,970)}, "departure platform");
    out.emplace_back(vector<pair<int, int>>{make_pair(30,237), make_pair(256,955)}, "departure track");
    out.emplace_back(vector<pair<int, int>>{make_pair(47,731), make_pair(741,950)}, "departure date");
    out.emplace_back(vector<pair<int, int>>{make_pair(38,301), make_pair(317,954)}, "departure time");
    out.emplace_back(vector<pair<int, int>>{make_pair(26,598), make_pair(623,969)}, "arrival location");
    out.emplace_back(vector<pair<int, int>>{make_pair(50,835), make_pair(854,971)}, "arrival station");
    out.emplace_back(vector<pair<int, int>>{make_pair(44,535), make_pair(549,958)}, "arrival platform");
    out.emplace_back(vector<pair<int, int>>{make_pair(36,672), make_pair(685,967)}, "arrival track");
    out.emplace_back(vector<pair<int, int>>{make_pair(34,217), make_pair(236,974)}, "class");
    out.emplace_back(vector<pair<int, int>>{make_pair(29,469), make_pair(483,970)}, "duration");
    out.emplace_back(vector<pair<int, int>>{make_pair(45,111), make_pair(120,965)}, "price");
    out.emplace_back(vector<pair<int, int>>{make_pair(32,751), make_pair(760,954)}, "route");
    out.emplace_back(vector<pair<int, int>>{make_pair(25,321), make_pair(339,954)}, "row");
    out.emplace_back(vector<pair<int, int>>{make_pair(38,423), make_pair(438,958)}, "seat");
    out.emplace_back(vector<pair<int, int>>{make_pair(45,798), make_pair(813,954)}, "train");
    out.emplace_back(vector<pair<int, int>>{make_pair(40,487), make_pair(503,954)}, "type");
    out.emplace_back(vector<pair<int, int>>{make_pair(46,916), make_pair(938,949)}, "wagon");
    out.emplace_back(vector<pair<int, int>>{make_pair(25,160), make_pair(184,957)}, "zone");
    return out;
}

int p1Invalid(vector<Rule>& rules, vector<int>& ticket){
    for(int num:ticket){
        for(Rule r: rules){
            for(auto p: r.ranges){
                if(p.first<=num && num <=p.second){
                    goto next;
                }
            }
        }
        return num;
        next:;
    }
    return 0;
}

bool satisfiesRule(int num, vector<pair<int, int>>& range){
    for(auto& p: range){
        if(p.first<=num && num<=p.second){
            return true;
        }
    }
    return false;
}

int main(){
    vector<Rule> rs(rules());
    
    vector<int> ticket = {73,59,83,127,137,151,71,139,67,53,89,79,61,109,131,103,149,97,107,101};
    vector<vector<int>> otherTickets(inputTickets());
    int p1= 0;
    for(auto v: otherTickets){
        p1+=(p1Invalid(rs, v));
    }
    cout<<"Part 1: "<<p1<<endl;

    for(int i =0;i<otherTickets.size();i++){
        if(p1Invalid(rs,otherTickets[i])){ //invalid ticket
            otherTickets.erase(otherTickets.begin()+i--);
        }
    }

    "By now, otherTickets is only valids.";

    vector<string> possibleTemplate;
    for(auto r: rs){
        possibleTemplate.push_back(r.name);
    }
    vector<vector<string>> possibles;
    for(int k = 0;k<20;k++){
        possibles.emplace_back(vector<string>(possibleTemplate));
    }

    for(auto& v: possibles){
        cout<<"[";
        string delim = "";
        for(auto& r: v){
            cout<<delim<<r;
            delim = ", ";
        }cout<<"]"<<endl;
    }
    map<string, vector<pair<int, int>>> rm;
    for(auto r: rs){
        rm[r.name] = r.ranges;
    }

    for(auto valid: otherTickets){
        for(int i = 0;i<20;i++){
            for(int j = 0;j<possibles.size();j++){
                cout<<j<<endl;
                string ruleName = possibles[i][j];
                if(!satisfiesRule(valid[i],rm[ruleName])){
                    cout<<valid[i]<<" Doesn't satisfy "<<ruleName<<endl;
                    cout<<possibles[i].size()<<endl;
                    possibles[i].erase(possibles[i].begin()+j++);
                }
            }
        }
    }
}