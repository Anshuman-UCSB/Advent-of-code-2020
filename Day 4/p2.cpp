#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct passport{
    bool valid;
    int byr, iyr, eyr;
    string hgt, hcl, ecl, pid;
    passport(string inp){
        stringstream ss(inp);
        string temp;

        vector<string> neccesary = {"byr","iyr","eyr","hgt","hcl","ecl","pid"};
        for(auto& s: neccesary){
            if(inp.find(s) == string::npos){
                valid = false;
                return;
            }
        }

        try{
            while(ss>>temp){
                string id = temp.substr(0,3);
                if(id == "byr"){
                    byr = stoi(temp.substr(4));
                }else if(id == "iyr"){
                    iyr = stoi(temp.substr(4));
                }else if(id == "eyr"){
                    eyr = stoi(temp.substr(4));
                }else if(id == "hgt"){
                    hgt = temp.substr(4);
                }else if(id == "hcl"){
                    hcl = temp.substr(4);
                }else if(id == "ecl"){
                    ecl = temp.substr(4);
                }else if(id == "pid"){
                    pid = temp.substr(4);
                }
            }
            valid = true;
        }catch(...){
            valid = false;
        }
    }

    void print(){
        cout<<"--------"<<endl;
        cout<<"Valid: "<<(valid?"TRUE":"FALSE")<<endl;
        cout<<"byr: "<<byr<<endl;
        cout<<"iyr: "<<iyr<<endl;
        cout<<"eyr: "<<eyr<<endl;
        cout<<"hgt: "<<hgt<<endl;
        cout<<"hcl: "<<hcl<<endl;
        cout<<"ecl: "<<ecl<<endl;
        cout<<"pid: "<<pid<<endl;
        cout<<"--------"<<endl;
    }

    void validate(){
        if(valid == false){
            return;
        }

        if(!(1920<=byr && byr<=2002)){
            valid = false;
            return;
        }

        if(!(2010<=iyr && iyr<=2020)){
            valid = false;
            return;
        }

        if(!(2020<=eyr && eyr<=2030)){
            valid = false;
            return;
        }

        if(hgt.find("in")!=string::npos){
            stringstream ss(hgt);
            int ht;
            ss>>ht;
            if(!(59<=ht && ht<=76)){
                valid = false;
                return;
            }
        }else if(hgt.find("cm")!=string::npos){
            stringstream ss(hgt);
            int ht;
            ss>>ht;
            if(!(150<=ht && ht<=193)){
                valid = false;
                return;
            }
        }else{
            valid = false;
            return;
        }

        if(hcl[0] != '#' || hcl.size()<7){
            valid = false;
            return;
        }
        string valids = "0123456789abcdef";
        for(int i = 1;i<7;i++){
            if(valids.find(hcl[i])== string::npos){
                valid = false;
                return;
            }
        }

        if(!(ecl == "amb" || ecl == "blu"
          || ecl == "brn" || ecl == "gry"
          || ecl == "grn" || ecl == "hzl" 
          || ecl == "oth")){
              valid = false;
              return;
        }

        if(pid.size()!=9){
            valid = false;
            return;
        }
        try{
            int temp = stoi(pid);
        }catch(...){
            valid = false;
            return;
        }
        valid = true;
    }
};



int main(){
    fstream file("input");
    string line;
    vector<passport> passports;
    string build ="";
    while(getline(file, line)){
        if(line.size() == 1){
            passports.emplace_back(build);
            cout<<build<<endl;
            build = "";
        }else{
            build += line+" ";
        }
    }

    int p2 = 0;
    for(auto& p: passports){
        p.validate();
        p2+=p.valid;
        p.print();
        cout<<endl;
    }
    cout<<"Part 2: "<<p2<<endl;
}