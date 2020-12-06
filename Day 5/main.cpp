#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <utility>
using namespace std;


vector<string> read(){
    fstream file("input");
    string line;
    vector<string> out;
    while(getline(file, line)){
        out.push_back(line);
    }
    return out;
}


pair<int, int> getSeat(string inp){
    int xl(0), xh(127), yl(0), yh(7);
    for(int i = 0;i<7;i++){
        if(inp[i] == 'F'){
            xh = (xh+xl)/2;
        }else if(inp[i] == 'B'){
            xl = (xh+xl)/2+1;
        }
    }
    for(int i = 7;i<10;i++){
        if(inp[i] == 'L'){
            yh = (yh+yl)/2;
        }else if(inp[i] == 'R'){
            yl = (yh+yl)/2+1;
        }
    }
    return make_pair(xl, yl);
}

int getId(string inp){
    return getSeat(inp).first*8+getSeat(inp).second;
}

int main(){
    vector<string> raw = read();
    int mx = -1;
    set<int> ids;
    for(auto& s: raw){
        ids.insert(getId(s));
        mx = max(getId(s), mx);
    }
    int i;
    for(i = 63;ids.find(i)!=ids.end();i++){
    }
    cout<<"Part 1: "<<mx<<endl;
    cout<<"Part 2: "<<i<<endl;
    
}
//812 too low