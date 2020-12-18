#include "../utility.cpp"

struct Coord{
    int x, y, z, w;
    Coord(int a, int b, int c, int d):x(a), y(b), z(c), w(d){}
    Coord(){}
    Coord(const Coord& inp):x(inp.x), y(inp.y), z(inp.z), w(inp.w){}
    bool operator <(const Coord& c) const {
        if(x<c.x){
            return true;
        }else if(x == c.x){
            if(y<c.y){
                return true;
            }else if(y==c.y){
                if(z<c.z){
                    return true;
                }else if(z==c.z){
                    return w<c.w;
                }
            }
        }
        return false;
    }
};

vector<Coord> getNeighbors(Coord inp){
    vector<Coord> c;
    for(int dx = -1;dx<=1;dx++){
        for(int dy = -1;dy<=1;dy++){
            for(int dz = -1;dz<=1;dz++){
                for(int dw = -1;dw<=1;dw++){
                    if(!(dx == 0 && dy == 0 && dz == 0 && dw == 0)){
                        c.emplace_back(inp.x+dx,inp.y+dy,inp.z+dz, inp.w+dw);
                    }
                }
            }
        }
    }
    return c;
}



ostream& operator<<(ostream& os, const Coord& c) 
{ 
	os<<"("<<c.x<<", "<<c.y<<", "<<c.z<<", "<<c.w<<")";
    return os;
} 

bool alive(map<Coord, bool>& inp, Coord c){
    vector<Coord> neighbors = getNeighbors(c);
    int sum = 0;
    for(auto& crd: neighbors){
        sum+=inp[crd];
    }
    if(inp[c]){
        return sum == 2 || sum == 3;
    }else{
        return sum == 3;
    }
}

map<Coord, bool> iter(map<Coord, bool>& inp){
    set<Coord> q;
    map<Coord, bool> out;
    for(auto& p:inp){
        for(auto& crd: getNeighbors(p.first)){
            q.insert(crd);
        }
    }
    for(auto c: q){
        if(alive(inp, c)){
            out[c]= true;
        }
    }
    return out;
}


int main(){
    map<Coord, bool> actives;
    fstream file("input");
    string line;
    int y = 0;
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        for(int x = 0;x<line.size();x++){
            if(line[x] == '#'){
                actives[Coord(x,y,0,0)]=true;
            }
        }
        y++;
    }
    // cout<<actives<<endl;
    auto t = actives;
    for(int  i = 1;i<=6;i++){
        // cout<<"Step "<<i<<endl;
        t = iter(t);
        // printMap(t);
    }
    int p1 = 0;
    for(auto& p: t){
        p1+=p.second;
    }
    cout<<"Part 1: "<<p1<<endl;
    
}