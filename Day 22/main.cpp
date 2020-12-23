#include "../utility.cpp"

void printNice(int roundNum, vector<int>& p, vector<int>& e){
    cout<<" -- Round "<<roundNum<<" --"<<endl;
    cout<<"Players 1's deck: "<<p<<endl;
    cout<<"Players 2's deck: "<<e<<endl<<endl;
}

void round(vector<int>& p, vector<int>& e){
    int a(p[0]), b(e[0]);
    if(a>b){
        p.push_back(a);
        p.push_back(b);
    }else{
        e.push_back(b);
        e.push_back(a);
    }
    p.erase(p.begin());
    e.erase(e.begin());
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
    int rn = 1;
    // cout<<player<<endl<<enemy<<endl;
    // printNice(rn++, player, enemy);
    while(!player.empty() && !enemy.empty()){
        round(player, enemy);
        // printNice(rn++, player, enemy);
    }

    long long p1 = 0;
    int mult= 1;
    if(player.empty()){
        for(int i = enemy.size()-1;i>=0;i--){
            p1+=enemy[i]*mult++;
        }
    }
    if(enemy.empty()){
        for(int i = player.size()-1;i>=0;i--){
            p1+=player[i]*mult++;
        }
    }
    cout<<p1<<endl;
    t.stop();
}