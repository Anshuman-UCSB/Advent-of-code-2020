#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
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


bool validate(map<string, string>& passport){
    try{
        
        vector<string> needed = {"byr","iyr","eyr","hgt","hcl","ecl","pid"};
        for(auto criteria:needed){
            if(passport.find(criteria) == passport.end()){
                return false;
            }
        }
        
        if(stoi(passport["byr"])>=1920 && stoi(passport["byr"])<=2002){
            //fuck you    
        }else{
            cout<<"failed on byr: "<<passport["byr"]<<endl;
            return false;
        }

        if(stoi(passport["iyr"])<2010 || stoi(passport["iyr"])>2020){
            cout<<"failed on iyr: "<<passport["iyr"]<<endl;
            return false;
        }
            
        if(stoi(passport["eyr"])<2020 || stoi(passport["eyr"])>2030){
            cout<<"failed on eyr: "<<passport["eyr"]<<endl;
            return false;
        }

        string height = passport["hgt"];
        if(height.find("in")!=string::npos){
            int ht;
            stringstream ss(height);
            ss>>ht;
            if(ht<59 || ht>76){
                cout<<"failed on ht in: "<<passport["hgt"]<<endl;

                return false;
            }
        }else if(height.find("cm")!=string::npos){
            int ht;
            stringstream ss(height);
            ss>>ht;
            if(ht<150 || ht>193){
                cout<<"failed on ht cm: "<<passport["hgt"]<<endl;

                return false;
            }
        }else{
            cout<<"failed on hgt: "<<passport["hgt"]<<endl;
            return false;
        }


        if(passport["hcl"][0] != '#'){
            cout<<"failed on hcl: "<<passport["hcl"]<<endl;
            return false;
        }
        if(passport["hcl"].size()<7){
            cout<<"failed on hcl, too small: "<<passport["hcl"]<<endl;
            return false;
        }
        string okLetters = "abcdef0123456789";
        for(int i = 1;i<7;i++){
            if(okLetters.find(passport["hcl"][i])==string::npos){
                cout<<"failed on hcl invalid char: "<<passport["hcl"]<<endl;

                return false;
            }
        }

        vector<string> valids = {"amb","blu","brn","gry","grn","hzl","oth"};
        bool eyecolor = false;
        for(auto v: valids){
            if(passport["ecl"] == v){
                eyecolor = true;
                break;
            }
        }
        if(eyecolor == false){
            cout<<"failed on ecl: "<<passport["ecl"]<<endl;
            return false;
        }
        if(passport["pid"].size()>9){
            cout<<"failed on pid: "<<passport["pid"]<<endl;

            return false;
        }
        try{
            int pid = stoi(passport["pid"]);
        }catch(...){
            cout<<"failed on pid: "<<passport["pid"]<<endl;
            return false;
        }
        
        cout<<"passed"<<endl;
        return true;

    }catch(...){
        cout<<"Other error"<<endl;
        return false;
    }
}


int main(){
    
    vector<string> raw = readinp();
    vector<string> passports = {""};
    for(auto& l: raw){
        l.pop_back(); // get rid of newlines
    }
    for(auto& l: raw){
        if(l.size()){
            passports.back()+=" "+l;
        }else{
            passports.push_back("");
        }
    }

    vector<vector<string>> passporttemp;

    for(auto& l: passports){
        passporttemp.push_back(vector<string>());
        // cout<<l<<endl;
        stringstream ss(l);
        string temp;
        while(ss>>temp){
            passporttemp.back().push_back(temp);
        }
    }

    vector<map<string, string>> pmap;
    
    for(auto& v: passporttemp){
        pmap.push_back(map<string, string>());
        for(auto& t:v){
            pmap.back()[t.substr(0,3)] = t.substr(4);
            // cout<<t<<", ";
        }
        // for(auto& p: pmap.back()){
        //     cout<<p.first<<", "<<p.second<<endl;
        // }
    }
    
    

    vector<string> needed = {"byr","iyr","eyr","hgt","hcl","ecl","pid"}; //,"cid"

    int p1 = 0;
    for(auto p: passports){
        for(auto criteria:needed){
            if (p.find(criteria) == string::npos){
                goto invalid;
            }
        }
        p1++;
        invalid:;
    }
    cout<<"Part 1: "<<p1<<endl;

    int p2 = 0;
    for(auto& p: pmap){
        if(validate(p)){
            p2++;
        }
    }
    cout<<"part2: "<<p2<<endl;
}
//196 wrong
//195 wrong
//197 wrong