#include "../utility.cpp"

void printNice(int roundNum, vector<int>& p, vector<int>& e){
    cout<<" -- Round "<<roundNum<<" --"<<endl;
    cout<<"Players 1's deck: "<<p<<endl;
    cout<<"Players 2's deck: "<<e<<endl<<endl;
}

string makeHash(vector<int>& p, vector<int>& e){
    string build = "";
    for(auto& elem: p){
        build+=elem+", ";
    }
    build+='|';
    for(auto& elem: e){
        build+=elem+", ";
    }
    return build;
}


int round(vector<int>& p, vector<int>& e, set<string>& s);

int game(vector<int>& p, vector<int>& e){
    set<string> s;
    int rn = 1;
    while(!p.empty() && !e.empty()){
        int res = round(p, e, s);
        if(res)
            return res;
        printNice(rn++,p, e);
    }
    if(p.empty()){
        return 2;
    }
    if(e.empty()){
        return 1;
    }
    return -1;
}

int round(vector<int>& p, vector<int>& e, set<string>& s){
    // 0 if nothing, 1 if player win, 2 if enemy win
    if(s.insert(makeHash(p, e)).second == false){
        return 1;
    }
    int a(p[0]), b(e[0]);
    
    p.erase(p.begin());
    e.erase(e.begin());

    if(a<=p.size() && b<=e.size()){
        // cout<<"Recursing!"<<endl;
        vector<int> tempDeckA(a); vector<int> tempDeckB(b);
        int val = game(tempDeckA, tempDeckB);
        if(val == 1){
            p.push_back(a);
            p.push_back(b);
        }else if(val == 2){
            e.push_back(b);
            e.push_back(a);
        }
        return val;
        //recurse?
    }else{
        if(a>b){
            p.push_back(a);
            p.push_back(b);
        }else if(b>a){
            e.push_back(b);
            e.push_back(a);
        }
    }
    return 0;
}


int main(){
    Timer t;
    fstream file("input");
    string line;
    vector<int> player, enemy;
    getline(file, line);
    while(getline(file, line) && line.size()>1){
        player.push_back(stoi(line));
    }
    getline(file, line);
    while(getline(file, line)){
        enemy.push_back(stoi(line));
    }
    set<string> s;
    int rn = 1;
    cout<<player<<endl<<enemy<<endl;
    printNice(rn++, player, enemy);
    int winner=game(player, enemy);
    // while(!player.empty() && !enemy.empty()){
    //     int val = round(player, enemy, s);
    //     if(val == 1){
    //         winner = 1;
    //         break;
    //     }
    //     // printNice(rn++, player, enemy);
    // }

    printNice(-1, player, enemy);
    cout<<"Winner: "<<winner<<endl;
    long long p2 = 0;
    int mult= 1;
    if(player.empty()){
        for(int i = enemy.size()-1;i>=0;i--){
            p2+=enemy[i]*mult++;
        }
    }
    if(winner==1||enemy.empty()){
        for(int i = player.size()-1;i>=0;i--){
            p2+=player[i]*mult++;
        }
    }
    cout<<p2<<endl;
    t.stop();
}
//11210 too low