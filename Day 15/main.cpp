#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>
#include <chrono>
using namespace std;
using namespace std::chrono;

int game(vector<int>& inp, int until);

int main(){
    fstream file("input");
    string line;
    getline(file, line);
    char trash;
    int inp;
    stringstream ss(line);
    ss>>inp;
    vector<int> inputNums = {inp};
    while(ss>>trash>>inp)
        inputNums.push_back(inp);
    auto start = high_resolution_clock::now();
    cout<<"Part 1: "<<game(inputNums, 2020);
    auto stop = high_resolution_clock::now();
    cout<<" in "<<(duration_cast<microseconds>(stop-start)).count()<<" microseconds."<<endl;
    start = high_resolution_clock::now();
    cout<<"Part 2: "<<game(inputNums, 30000000)<< " in ";
    stop = high_resolution_clock::now();
    cout<<(duration_cast<seconds>(stop-start)).count()<<" seconds."<<endl;
}


int game(vector<int>& inp, int until){
    //unordered_map
    map<int, vector<int>> m;
    // number, most recent turn
    int turn = 1;
    for(auto i: inp){
        m[i].push_back(turn++);
    }
    int last = inp.back();
    int val;
    for(;turn<=until;turn++){
        if(m[last].size()>1){
            val = m[last][0]-m[last][1];
        }else{
            val = 0;
        }
        m[val].insert(m[val].begin(),turn);
        while(m[val].size()>2){
            m[val].pop_back();
        }
        // if(rand()%10000==1)
        //     cout<<"Turn "<<turn<<": "<<val<<endl;
        last = val;
    }
    // for(auto& p: m){
    //     cout<<p.first<<" last seen at "<<p.second<<endl;
    // }
    return val;
}

