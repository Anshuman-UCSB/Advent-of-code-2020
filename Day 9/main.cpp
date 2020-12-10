#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

#define PREAMBLE 25

int main(){
    //p1 15690279
    long part1 = 15690279;
    fstream file("input");
    string line;
    vector<long> raw;
    long temp;
    while(getline(file, line)){
        stringstream ss(line);
        ss>>temp;
        raw.push_back(temp);
    }
    int l, h;
    for(int i = 0;i<raw.size()-2;i++){
        temp = raw[i];
        for(int j = i+1;j<raw.size();j++){
            temp+=raw[j];
            if(temp == part1){
                cout<<"Part 2: "<<i<<"->"<<j<<endl;
                l = i;
                h = j;
                goto out;
            }else if(temp > part1){
                break;
            }
        }
    }
    out:;
    long mn(raw[l]), mx(0);
    for(int i = l;i<h;i++){
        mn = min(mn, raw[i]);
        mx = max(mx, raw[i]);
    }
    cout<<"Part 2: "<<mn+mx<<endl;

}