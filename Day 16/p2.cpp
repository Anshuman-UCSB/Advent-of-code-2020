#include "../utility.cpp"
typedef pair<int, int> rPair;

bool satisfyRule(pair<rPair, rPair>& ranges, int val);

int main(){
    fstream file("rawinp");
    string line;
    map<string, pair<rPair, rPair>> m;
    while(getline(file, line) && line.size()>2){
        string name, trash;
        char charTrash;
        int a, b, c, d;
        name = upTo(line, ':');
        stringstream ss(after(line, ':'));
        // cout<<ss.str()<<endl;
        ss>>a>>charTrash>>b>>trash>>c>>charTrash>>d;
        auto p = make_pair(make_pair(a,b) ,make_pair(c,d));
        m[name] = p;
    }

    for(auto& p: m){
        cout<<p.first<<" : "<<p.second.first.first<<"-"<<p.second.first.second<<", "<<p.second.second.first<<"-"<<p.second.second.second<<endl;
    }
    getline(file, line);
    getline(file, line);
    line.push_back(',');
    vector<int> ticket;
    stringstream ss(line);
    char t;
    int temp;
    while(ss>>temp>>t){
        ticket.push_back(temp);
    }
    cout<<ticket<<endl;

    getline(file, line);
    getline(file, line);
    
    vector<vector<int>> otherTickets;
    while(getline(file, line)){
        otherTickets.emplace_back();
        line.push_back(',');
        stringstream ss(line);
        while(ss>>temp>>t)
            otherTickets.back().push_back(temp);
    }
    // cout<<otherTickets<<endl;
    
    for(int i =0;i<otherTickets.size();i++){
        auto tick = otherTickets[i];
        for(int j = 0;j<tick.size();j++){
            for(auto r: m){
                if(satisfyRule(r.second, tick[j])){
                    goto validNum;
                }
            }
            otherTickets.erase(otherTickets.begin()+i--);
            break;
            validNum:;
        }
    }

    // cleaned bad tickets
    vector<string> possibles;
    for(auto& p: m){
        possibles.push_back(p.first);
    }
    // cout<<possibles<<endl;
    vector<vector<string>> possib;
    for(int i = 0;i<ticket.size();i++){
        possib.emplace_back(possibles);
    }
    
    //m is rule map
    for(auto t: otherTickets){ //t is ticket
        for(int i = 0;i<t.size();i++){ //i is number in ticket 
            for(int j = 0;j<possib[i].size();j++){ // j is index of name in possib[i]
                auto r = m[possib[i][j]];
                if(!satisfyRule(r, t[i])){
                    // cout<<t[i]<<" did not satisfy rule "<<possib[i][j]<<endl;
                    possib[i].erase(possib[i].begin()+j--);
                }
            }
        }
    }
    "After first sift, now recursively clean ones with one possibliity.";
    vector<string> solved(20);
    bool done = false;
    while(!done){
        done = true;
        for(int i = 0;i<possib.size();i++){
            auto v= possib[i];
            if(v.size() == 1){
                // cout<<"Found pos of "<<v[0]<<endl<<endl;
                solved[i] = v[0];
                for(int j = 0;j<possib.size();j++){
                    for(int k = 0;k<possib[j].size();k++){
                        if(possib[j][k] == solved[i]){
                            possib[j].erase(possib[j].begin()+k);
                        }
                    }
                }
                done = false;
                possib[i] = {};
            }
        }
        // cout<<possib<<endl;
    }
    cout<<solved<<endl;
    long long p2 = 1;
    for(int i = 0;i<solved.size();i++){
        if(solved[i].find("departure")!=string::npos){
            p2*=ticket[i];
        }
    }
    cout<<"Part 2: "<<p2<<endl;
}

bool satisfyRule(pair<rPair, rPair>& ranges, int val){
    return (ranges.first.first<=val && ranges.first.second>=val)
        || (ranges.second.first<=val && ranges.second.second>=val);
}