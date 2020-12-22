#include "../utility.cpp"

vector<string> rotateVector(vector<string> v){
    auto out = v;
    for(int y = 0;y<v.size();y++){
        for(int x = 0;x<v[y].size();x++){
            out[x][v.size()-y-1]=v[y][x];
        }
    }

    return out;
}


vector<string> flipVector(vector<string> v){
    auto out = v;
    reverse(out.begin(), out.end());
    return out;
}

int main(){
    auto v = readFile("p2Grid.txt");
    // auto v = readFile("exGrid.txt");

    // for(auto& l: v){
    //     cout<<l<<endl;
    // }
    vector<string> monsterFrame = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };

    int p2 = 0;
    int temp;
    int monsters = 0;
    int monsterSize = 15;
    for(int j = 0;j<2;j++){
        for(int i = 0;i<4;i++){
            int monstersTemp= 0;
            for(int y = 0;y<v.size()-3;y++){
                for(int x = 0;x<v[y].size()-20;x++){
                    temp = 0;
                    for(int dy = 0;dy<3;dy++){
                        for(int dx = 0;dx<20;dx++){

                            if(monsterFrame[dy][dx] == '#'){
                                if(v[y+dy][x+dx] != '#'){
                                    goto invalid;
                                }
                            }
                        }
                    }
                    monstersTemp++;
                    invalid:;
                }
            }
            monsters = max(monsters, monstersTemp);
            v = rotateVector(v);
        }
        v = flipVector(v);
    }
    p2 = monsters*-monsterSize;
    for(auto& l: v){
        for(auto c: l){
            p2+=(c=='#');
        }
    }
    cout<<"Monster: "<<monsters<<endl;
    cout<<"Part 2: "<<p2<<endl;

    //1778 too low
}

