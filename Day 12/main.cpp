#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>

using namespace std;

int main(){
    vector<pair<char, int>> inp;
    fstream file("input");
    string line;
    char instr;
    int temp;
    while(getline(file, line)){
        stringstream ss(line);
        ss>>instr>>temp;
        inp.push_back(make_pair(instr, temp));
    }
    
    // for(auto p: inp){
    //     cout<<p.first<<" : "<<p.second<<endl;
    // }

    int coords[2] = {0,0};
    int waypoint[2] = {10,1};

    for(auto& p: inp){
        switch(p.first){
            case 'N': waypoint[1]+=p.second;break;
            case 'E': waypoint[0]+=p.second;break;
            case 'S': waypoint[1]-=p.second;break;
            case 'W': waypoint[0]-=p.second;break;
            case 'L':
                for(int i = 0;i<p.second;i+=90){
                    swap(waypoint[0],waypoint[1]);
                    waypoint[0]*=-1;
                }
                break;
            case 'R':
                for(int i = 0;i<p.second;i+=90){
                    swap(waypoint[0],waypoint[1]);
                    waypoint[1]*=-1;
                }
                break;
            case 'F': 
                coords[0]+=p.second*waypoint[0];
                coords[1]+=p.second*waypoint[1];
                break;
        }
        cout<<p.first<<p.second<<" ("<<coords[0]<<", "<<coords[1]<<")"<<endl;
    }
    cout<<"Part 2: "<<abs(coords[0])+abs(coords[1])<<endl;

}
//part 2 15428 too low

// PART 1
/*
int main(){
    vector<pair<char, int>> inp;
    fstream file("input");
    string line;
    char instr;
    int temp;
    while(getline(file, line)){
        stringstream ss(line);
        ss>>instr>>temp;
        inp.push_back(make_pair(instr, temp));
    }
    
    // for(auto p: inp){
    //     cout<<p.first<<" : "<<p.second<<endl;
    // }

    int coords[2] = {0,0};
    int dir = 1;
    vector<pair<int, int>> mapping;
    mapping.push_back(make_pair(0,1));
    mapping.push_back(make_pair(1,0));
    mapping.push_back(make_pair(0,-1));
    mapping.push_back(make_pair(-1,0));

    for(auto& p: inp){
        switch(p.first){
            case 'N': coords[1]+=p.second;break;
            case 'E': coords[0]+=p.second;break;
            case 'S': coords[1]-=p.second;break;
            case 'W': coords[0]-=p.second;break;
            case 'L':dir-=p.second/90;break;
            case 'R':dir+=p.second/90;break;
            case 'F': 
                auto d = mapping[dir%4<0?(dir%4+4):dir%4];
                coords[0] += p.second*d.first;
                coords[1] += p.second*d.second;
                break;
        }
        cout<<p.first<<p.second<<" ("<<coords[0]<<", "<<coords[1]<<")"<<"Dir : "<<dir%4<<endl;
    }
    cout<<"Part 1: "<<abs(coords[0])+abs(coords[1])<<endl;

}*/