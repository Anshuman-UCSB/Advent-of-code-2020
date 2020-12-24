#include "../utility.cpp"
#define vInt vector<int>
#define PI 3.14159265

enum baseDirections{
    ne, e, se, sw, w, nw
};

struct Directions{
    vector<int> dirs;
    string raw;
    pair<double, double> coords;
    // ne, e, se, sw, w, nw
    
    Directions(string inp){
        coords = make_pair(0.0,0.0);
        raw = inp;
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

    void populateMap(map<pair<double, double>, bool>& m){
        vector<string> dirString = {"ne", "e", "se", "sw", "w", "nw"};
        for(auto& s: dirString){
            Directions neighbor(raw+s);
            m[neighbor.coords] = m[neighbor.coords];
        }
    }

    void print(){
        cout<<"("<<coords.first<<", "<<coords.second<<")"<<endl;
    }
};

double getDist(const pair<double, double>& a,const pair<double, double>& b){
    double out = 0;
    out+=pow(b.first-a.first,2);
    out+=pow(b.second-a.second,2);
    return sqrt(out);
}

int getNeighbors(pair<double, double>& c, map<pair<double, double>, bool>& m){
    const double dist = 1.3;
    int out = -m[c];
    for(auto& p: m){
        if(getDist(p.first, c)<dist){
            out+=m[p.first];
        }
    }
    return out;
}

map<pair<double, double>, bool> iterate(map<pair<double, double>, bool>& m){
    map<pair<double, double>, bool> out;
    for(auto& p: m){
        
    }
}

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