#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(){
    fstream file("input");
    string line;
    vector<int> vals;
    while(getline(file, line)){
        vals.push_back(stoi(line));
    }
    for(int i = 0;i<vals.size()-1;i++){
        for(int j = i+1;j<vals.size();j++){
            for(int k = j+1;k<vals.size();k++){
                if(vals[i]+vals[j]+vals[k] == 2020){
                    cout<<"part 1: "<<vals[i]*vals[j]*vals[k]<<endl;
                }
            }
        }
    }
}

void part1(){
    fstream file("input");
    string line;
    vector<int> vals;
    while(getline(file, line)){
        vals.push_back(stoi(line));
    }
    for(int i = 0;i<vals.size()-1;i++){
        for(int j = i+1;j<vals.size();j++){
            if(vals[i]+vals[j] == 2020){
                cout<<"part 1: "<<vals[i]*vals[j]<<endl;
            }
        }
    }
}
