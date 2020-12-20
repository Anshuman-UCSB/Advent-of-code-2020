#include "../utility.cpp"

struct Rule{
    bool solved;
    int id;
    vector<vector<int>> raw;
    vector<string> solutions;
    Rule():solved(false){}
    Rule(string inp){
        solved = false;
        stringstream ss(inp);
        raw.emplace_back();
        string temp;
        ss>>id>>temp>>temp;
        if(temp[0] == '"'){
            solved = true;
            solutions.push_back(string(1,temp[1]));
            return;
        }
        raw.back().emplace_back(stoi(temp));
        while(ss>>temp){
            if(temp == "|"){
                raw.emplace_back();
            }else{
                raw.back().emplace_back(stoi(temp));
            }
        }
    }
};
 
ostream& operator<<(ostream& os, const Rule& r) 
{ 
	os<<"Rule "<<r.id<<":"<<endl;
    if(r.solved){
        os<<"solved: ";
        string delim = "";
        for(auto soln : r.solutions){
            cout<<delim<<soln;
            delim = ", ";
        }
    }else
        os<<"Raw:  "<<r.raw<<endl;
    return os;
} 

template<class T>
vector<T> permute(vector<T>& a, vector<T>& b){
    vector<T> out;
    for(auto v: a){
        for(auto v2: b){
            out.push_back(v+v2);
        }
    }
    return out;
}

int main(){
    map<int, Rule> rules;
    fstream file("input");
    string line;
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        if(line.size()<=0){
            break;
        }
        stringstream ss(line);
        int id;
        ss>>id;
        rules[id]=Rule(line);
    }
    // cout<<rules;
    // cout<<endl;
    cout<<rules<<endl;
    
    bool unchanged = false;
    while(!unchanged){
        unchanged = true;
        for(auto& p: rules){
            if(!p.second.solved){
                for(auto& ruleSet: p.second.raw){
                    for(auto rNum: ruleSet){
                        if(rules[rNum].solved == false){
                            continue;
                        }
                    }
                }
                // All subs are solved
                vector<string> temp = {""};
                for(auto& ruleSet: p.second.raw){
                    temp.clear();
                    temp.push_back("");
                    for(auto num: ruleSet){
                        cout<<"Before: "<<temp<<endl;
                        temp= permute(p.second.solutions, rules[num].solutions);
                        cout<<"After : "<<temp<<endl;
                        cout<<p.second.solutions<<endl;
                    }
                }
                p.second.solutions.insert(p.second.solutions.begin(),temp.begin(), temp.end());
                p.second.solved = true;
                unchanged = false;
            }
        }
        cout<<rules<<endl;
    }
}