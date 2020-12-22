#include "../utility.cpp"

int main(){
    auto v = readFile("input");
    map<string, vector<vector<string>>> m;
    map<string, int> p1Count;
    map<string, string> p2helper;

    for(auto l: v){
        stringstream ss(l);
        string temp;
        ss>>temp;
        vector<string> a, b;
        while(temp!= "(contains"){
            p1Count[temp]++;
            a.push_back(temp);
            ss>>temp;
        }
        while(ss>>temp){
            temp.pop_back();
            b.push_back(temp);
        }
        for(auto& e: b){
            m[e].insert(m[e].end(), a);
        }
    }
    cout<<m<<endl;

    map<string, vector<string>> candidates;
    for(auto& p: m){
        map<string, int> counter;
        int sizeEligible = p.second.size();
        for(auto& v: p.second){
            for(auto& e: v){
                counter[e]++;
            }
        }
        for(auto cP: counter){
            if(cP.second == sizeEligible){
                candidates[p.first].push_back(cP.first);
            }
        }
    }
    // cout<<candidates<<endl;
    map<string, string> solved;

    notDone:
        for(auto& p: candidates){
            if(p.second.size() == 1){
                solved[p.second[0]] = p.first;
                p2helper[p.first] = p.second[0];
                for(auto& t: candidates){
                    removeValue(t.second, p.second[0]);
                }
                goto notDone;
            }
        }

    cout<<"Solved: \n"<<solved<<endl;
    // cout<<"P1 count: "<<endl<<p1Count<<endl;
    int p1 = 0;
    for(auto& p: p1Count){
        if(!solved.count(p.first)){
            // cout<<"Counting "<<p.first<<endl;
            p1+=p1Count[p.first];
        }
    }
    cout<<p2helper<<endl;
    string p2 = "";
    string delim = "";
    for(auto& p: p2helper){
        p2+=delim+p.second;
        delim = ",";
    }
    cout<<"Part 1: "<<p1<<endl;
    cout<<"Part 2: "<<p2<<endl;
}