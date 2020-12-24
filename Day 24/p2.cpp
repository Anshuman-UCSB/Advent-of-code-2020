#include "../utility.cpp"
#define x first
#define y second
#define pii pair<int, int>
#define c make_pair

enum baseDirections{
    ne, e, se, sw, w, nw
};

struct Directions{
    pair<int, int> coords;
    string raw;
    
    Directions(string inp){
        raw = inp;
        coords = c(0,0);
        for(int i = 0;i<inp.size();i++){
            switch(inp[i]){
                case 'e':coords.x+=2;break;
                case 'w':coords.x-=2;break;
                case 'n':
                    i++;
                    if(inp[i] == 'w'){
                        coords.x-=1;
                        coords.y+=1;
                        break;
                    }else if(inp[i] == 'e'){
                        coords.x+=1;
                        coords.y+=1;
                        break;
                    }
                case 's':
                    i++;
                    if(inp[i] == 'w'){
                        coords.x-=1;
                        coords.y-=1;
                        break;
                    }else if(inp[i] == 'e'){
                        coords.x+=1;
                        coords.y-=1;
                        break;
                    }
            }
        }
    }


};

vector<pii> getNeighbors(const pii& coords){
    vector<pii> out(6, coords);
    out[0] = c(coords.x+1, coords.y+1);
    out[1] = c(coords.x+2, coords.y);
    out[2] = c(coords.x+1, coords.y-1);
    out[3] = c(coords.x-1, coords.y-1);
    out[4] = c(coords.x-2, coords.y);
    out[5] = c(coords.x-1, coords.y+1);
    return out;
}

void populateMap(map<pair<int, int>, bool>& m){
    map<pair<int, int>, bool> out;
    out = m;
    for(auto& p: m){
        if(p.second == false){
            out.erase(p.first);
        }
    }
    m = out;
    out.clear();
    for(auto& p: m){
        out[p.first] = p.second;
        for(auto& cd: getNeighbors(p.first)){
            if(out.count(cd) == 0){
                out[cd] = false;
            }
        }
    }
    m = out;
}

void iterate(map<pair<int, int>, bool>& m){
    populateMap(m);
    map<pair<int, int>, bool> out(m);
    for(auto& p: m){
        int sum=0;
        for(auto& crd: getNeighbors(p.first)){
            if(m.count(crd))
                sum+=m[crd];
        }
        if(m[p.first]){
            out[p.first] = !(sum == 0 || sum>2);
        }else{
            out[p.first] = (sum == 2);
        }
    }
    m = out;
}

int sumMap(map<pair<int, int>, bool>& m){
    int out = 0;
    for(auto& p: m)
        out+=p.second;
    return out;
}

int main(){
    Timer t;
    vector<string> raw =readFile("input");
    map<pair<int, int>, bool> m;
    for(auto& l : raw){
        Directions d(l);
        m[d.coords] = !m[d.coords];
    }

    cout<<"Part 1: "<<sumMap(m)<<endl;
    for(int day = 1;day<=100;day++)
        iterate(m);
    
    cout<<"Part 2: "<<sumMap(m)<<endl;

    t.stop();
}