#include "../utility.cpp"
#define vInt vector<int>
#define PI 3.14159265

enum baseDirections{
    ne, e, se, sw, w, nw
};

struct Directions{
    vector<int> dirs;
    pair<double, double> coords;
    // ne, e, se, sw, w, nw
    Directions(string inp){
        coords = make_pair(0.0,0.0);
        dirs=vector<int>(6);
        for(int i = 0;i<inp.size();i++){
            switch(inp[i]){
                case 'e':dirs[e]++;break;
                case 'w':dirs[w]++;break;
                case 'n':
                    i++;
                    if(inp[i] == 'w'){
                        dirs[nw]++; break;
                    }else if(inp[i] == 'e'){
                        dirs[ne]++; break;
                    }
                case 's':
                    i++;
                    if(inp[i] == 'w'){
                        dirs[sw]++; break;
                    }else if(inp[i] == 'e'){
                        dirs[se]++; break;
                    }
            }
        }
        double xMod = cos(PI/3);
        double yMod = sin(PI/3);

        coords.first+=dirs[0]*xMod;
        coords.second+=dirs[0]*yMod;
        
        coords.first+=dirs[1];
        
        coords.first+=dirs[2]*xMod;
        coords.second-=dirs[2]*yMod;
        
        coords.first-=dirs[3]*xMod;
        coords.second-=dirs[3]*yMod;

        coords.first-=dirs[4];

        coords.first-=dirs[5]*xMod;
        coords.second+=dirs[5]*yMod;

        coords.first = round( coords.first* 1000.0 ) / 1000.0;
        coords.second = round( coords.second* 1000.0 ) / 1000.0;
    }

    void print(){
        cout<<"("<<coords.first<<", "<<coords.second<<")"<<endl;
    }
};

int main(){
    vector<string> raw = readFile("input");
    map<pair<double, double>, bool> tiles;
    for(auto& l: raw){
        // cout<<l<<endl;
        Directions d(l);
        d.print();
        tiles[d.coords] = !tiles[d.coords];
    }
    // cout<<tiles<<endl;
    int p1= 0;
    for(auto& p: tiles){
        p1+=p.second;
    }
    cout<<"Part 1: "<<p1<<endl;
}

// 555 too high