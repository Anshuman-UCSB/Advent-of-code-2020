#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;


void part1(vector<string> raw){
    int out = 0;
    int l, h, count;
    char trash, letter;
    string pw;
    for(auto line: raw){
        stringstream ss(line);
        count = 0;
        ss>>l;
        ss>>trash>>h;
        ss>>letter>>trash>>pw;
        // cout<<l<<", "<<h<<" for "<<letter<<" in "<<pw<<endl;
        for(auto c: pw){
            count+=c==letter?1:0;
        }
        if(l<=count & count<=h){
            cout<<pw<<endl;
            out++;
        }
    }
    cout<<"Part 1: "<<out<<endl;
}

void part2(vector<string> raw){
    int out = 0;
    int l, h, count;
    char trash, letter;
    string pw;
    for(auto line: raw){
        stringstream ss(line);
        count = 0;
        ss>>l;
        ss>>trash>>h;
        ss>>letter>>trash>>pw;
        // cout<<l<<", "<<h<<" for "<<letter<<" in "<<pw<<endl;
        if((pw[l-1] == letter || pw[h-1] == letter) && pw[l-1] != pw[h-1]){
            cout<<pw<<endl;
            out++;
        }
    }
    cout<<"Part 1: "<<out<<endl;
}

int main(){
    fstream file("input");
    string line;
    vector<string> raw;
    while(getline(file, line)){
        raw.push_back(line);
    }
    part2(raw);
}

