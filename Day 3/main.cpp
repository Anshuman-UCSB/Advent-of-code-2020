#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> readinp(){
    fstream file("input");
    string line;
    vector<string> out;
    while(getline(file,line)){
        out.push_back(line);
    }
    return out;
}

int main(){
    vector<vector<bool>> mp;
    vector<string> raw = readinp();
    for(auto& l:raw){
        mp.push_back(vector<bool>());
        for(auto c: l){
            if(c == '.'){
                mp.back().push_back(false);
            }else{
                mp.back().push_back(true);
            }
        }
        mp.back().pop_back();
    }
    int dx(1), dy(2);
    int x, y;
    x = y = 0;
    for(auto& r: mp){
        for(auto v: r){
            cout<<v?"#":".";
        }cout<<endl;
    }
    cout<<mp[y][x%mp[0].size()]<<endl;
    int p1 = 0;
    while(y<mp.size()){
        p1+=mp[y][x%mp[0].size()];
        y+=dy;
        x+=dx;
    }
    cout<<"Part 1: "<<p1<<endl;
}