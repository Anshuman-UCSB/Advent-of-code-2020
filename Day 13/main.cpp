#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int part1(){
    // Raw input for input
    int start = 1008141;
    vector<int> busses = {17, 41, 523, 13, 19, 23, 787, 37, 29};
    // int start = 939; // TEST CASE
    // vector<int> busses = {7,13,59,31,19};
    for(int i = start;;i++){
        for(auto& b: busses){
            if(i%b==0){
                return (i-start)*b;
            }
        }
    }
    //793411689 too high
}

long long part2(){
    fstream file("input");
    int start;
    string line;
    getline(file, line);
    start = stoi(line);
    cout<<start<<endl;
    getline(file, line);
    if(line.back() == '\r')
        line.pop_back();
    for(auto& c: line)
        if(c == ',')
            c = ' ';
    cout<<line<<endl;
    stringstream ss(line);
    int i = 0;
    vector<pair<int, int>> bus;
    while(ss>>line){
        if(line[0] != 'x'){
            bus.push_back(make_pair(i, stoi(line)));
        }
        i++;
    }
    for(auto& p: bus){
        cout<<p.first<<" : "<<p.second<<endl;
    }

    for(long long i = start;;i++){
        for(auto& p: bus){
            if((i+p.first)%p.second != 0){
                goto invalid;
            }
        }
        return i;
        invalid:;
    }
}

int main(){
    cout<<"Part 1: "<<part1()<<endl;
    cout<<"Part 2: "<<part2()<<endl;
}