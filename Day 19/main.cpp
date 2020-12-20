#include "../utility.cpp"

struct Rule{
    int id;
    vector<vector<int>> raw;
    string rgx;
    Rule():id(-1), rgx(""){}
    Rule(string inp){
        rgx = "";
        stringstream ss(inp);
        ss>>id;
        string temp;
        ss>>temp>>temp;
        if(temp[0]=='"'){
            rgx=string(1, temp[1]);
        }else{
            raw.emplace_back();
            raw.back().push_back(stoi(temp));
            while(ss>>temp){
                if(temp[0]=='|'){
                    raw.emplace_back();
                }else{
                    raw.back().push_back(stoi(temp));
                }
            }
        }
    }
};

int main(){
    map<int, Rule> r;

    fstream file("input");
    string line;
    while(getline(file,line)){
        if(line.size() == 1){
            break;
        }
        if(line.back() == '\r'){
            line.pop_back();
        }
        Rule temp(line);
        r[temp.id]=temp;
        cout<<temp.raw<<endl;
        cout<<temp.rgx<<endl;
    }

    bool done = false;
    while(!done){
        done = true;
        for(auto& p: r){
            if(p.second.rgx.empty()){
                for(auto ruleset: p.second.raw){
                    for(auto val: ruleset){
                        if(r[val].rgx.empty()){
                            if(val == 8 && p.first == 8){
                                // only god
                            }else if(val == 11 && p.first == 11){
                                // can judge me
                            }else
                                goto invalid;
                        }
                    }
                }
                cout<<"Building "<<p.first<<endl;
                //Part 2:
                vector<string> temp;
                for(auto ruleset: p.second.raw){
                    string build = "";
                    for(auto val: ruleset){
                        if(r[val].rgx.find("|")!=string::npos){
                            build+="("+r[val].rgx+")";
                        }else{
                            build+=r[val].rgx;
                        }
                    }
                    temp.push_back(build);
                }
                string delim = "";
                for(auto& s: temp){
                    // cout<<p.first<<" > "<<s<<endl;
                    p.second.rgx+=delim+"("+s+")";
                    delim="|";
                }
                if(p.first == 8){
                    p.second.rgx = "("+p.second.rgx+")+";
                }
                done = false;
            }
            // for(auto& p: r){
            //     cout<<p.second.raw<<endl;
            //     cout<<p.second.rgx<<endl;
            // }
            invalid:;
        }
    }

    // for(auto& p: r){
    //     cout<<p.second.raw<<endl;
    //     cout<<p.second.rgx<<endl;
    // }

    string p1Regex = "^"+r[0].rgx+"$";
    // string p1Regex = "^a(((aa|bb)(ab|ba))|((ab|ba)(aa|bb)))b$";

    // cout<<p1Regex<<endl;
    int p1 = 0;
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        if(regex_search(line, regex(p1Regex)))//{
            p1++;
            // cout<<"M> "<<line;
        // }else
            // cout<<" > "<<line;
        // cout<<endl;
    }
    cout<<"P1: "<<p1<<endl;

    // string p2Regex = "";
    // p2Regex+=r[8].rgx+"+";
    // p2Regex+="(("+r[42].rgx+r[31].rgx+")";
    // p2Regex+="|("+r[42].rgx+r[42].rgx+r[31].rgx+r[31].rgx+")";
    // p2Regex+="|("+r[42].rgx+r[42].rgx+r[42].rgx+r[31].rgx+r[31].rgx+r[31].rgx+")";
    // p2Regex+="|("+r[42].rgx+r[42].rgx+r[42].rgx+r[42].rgx+r[31].rgx+r[31].rgx+r[31].rgx+r[31].rgx+")";
    // p2Regex+=")";
    // cout<<p2Regex<<endl;

    // int p2 = 0;
    // while(getline(file, line)){
    //     if(line.back() == '\r')
    //         line.pop_back();
    //     if(regex_search(line, regex(p2Regex))){
    //         p2++;
    //         cout<<"M> "<<line;
    //     }else
    //         cout<<" > "<<line;
    //     cout<<endl;
    // }
    // cout<<"P2: "<<p2<<endl;
}

//p2: 196, 313 too low