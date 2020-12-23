#include "../utility.cpp"

void printNice(int roundNum, vector<int>& p, vector<int>& e){
    cout<<" -- Round "<<roundNum<<" --"<<endl;
    cout<<"Players 1's deck: "<<p<<endl;
    cout<<"Players 2's deck: "<<e<<endl<<endl;
}

string makeHash(vector<int> p, vector<int> e){
    string out = "";
    for(int v: p){
        out+=to_string(v) + ", ";
    }
    out+="|";
    for(int v: e){
        out+=to_string(v) + ", ";
    }
    // cout<<"returning "<<out<<endl;
    return out;
}

struct Game{
    set<string> seen;
    vector<int> a, b;
    int level;
    Game():level(-1){}
    Game(vector<int> player, vector<int> enemy, int lvl = 0){
        level = lvl;
        a = player;
        b = enemy;
    }
    int getWinner(){
        int roundWinner;
        while(!a.empty() && !b.empty()){
            if(level>0){
                int maxA(-1), maxB(-1);
                for(auto& v: a){
                    maxA = max(maxA, v);
                }
                for(auto& v: b){
                    maxB = max(maxB, v);
                }
                if(maxA>maxB && maxA>a.size()+b.size()-2){
                    return 1;
                }
            }

            cout<<("\033c");
            printNice(level, a, b);
            cout<<"So far seen "<<seen.size()<<endl;
            roundWinner = 0;
            if(seen.insert(makeHash(a, b)).second == false){
                return 1;
            }
            int aCard(a[0]), bCard(b[0]);
            a.erase(a.begin());
            b.erase(b.begin());
            if(aCard<=a.size() && bCard<=b.size()){
                Game newRound(vector<int>(a.begin(), a.begin()+aCard), vector<int>(b.begin(), b.begin()+bCard), level+1);
                roundWinner = newRound.getWinner();
            }else{
                roundWinner = (bCard>aCard)+1;
            }
            switch(roundWinner){
                case 1:
                    a.push_back(aCard);
                    a.push_back(bCard);
                    break;
                case 2:
                    b.push_back(bCard);
                    b.push_back(aCard);
                    break;
            }
        }

        if(a.empty()){
            return 2;
        }else{
            return 1;
        }
    }
};

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
    Game g(player, enemy);
    cout<<g.getWinner()<<endl;
    printNice(0, g.a, g.b);
    auto v = (g.a.empty() ? g.b : g.a);
    long long p2= 0;
    int mult = 1;
    for(int i = v.size()-1;i>=0;i--){
        p2+=v[i]*mult++;
    }
    cout<<"Part 2: "<<p2<<endl;
    t.stop();
}
//5870, 11210 too low
//34555 too high