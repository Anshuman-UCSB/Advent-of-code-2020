// Have tile be a vector of strings
// Have function get edges, gets left to right or top to bottom
// Have rotate string, flip x, flip y return a string functions
// Have a check border function

#include "../utility.cpp"

struct Tile{
    int id;
    vector<string> dat;
    Tile():id(-1){}
    Tile(vector<string>& inp){
        stringstream ss(inp[0]);
        string trash;
        ss>>trash>>id;
        for(int i =1;i<inp.size();i++)
            dat.emplace_back(inp[i]);
    }

    void print(){
        cout<<"<Tile "<<id<<">" << endl;
        for(auto& r: dat)
            cout<<r<<endl;
    }
};

vector<string> getEdges(Tile& inp){
    vector<string> out;
    out.push_back(inp.dat.front());

    out.emplace_back();
    for(int y = 0;y<inp.dat.size();y++){
        out.back()+=inp.dat[y].back();
    }

    out.push_back(inp.dat.back());

    out.emplace_back();
    for(int y = 0;y<inp.dat.size();y++){
        out.back()+=inp.dat[y].front();
    }

    return out;
}

Tile flipX(const Tile& inp){
    Tile out;
    out.id = inp.id;
    for(auto r: inp.dat){
        reverse(r.begin(), r.end());
        out.dat.emplace_back(r);
    }
    return out;
}

Tile flipY(const Tile& inp){
    Tile out;
    out.id = inp.id;
    for(int i = inp.dat.size()-1;i>=0;i--){
        out.dat.emplace_back(inp.dat[i]);
    }
    return out;
}

Tile rotate90(const Tile& inp){
    Tile out;
    out.id = inp.id;
    for(int x = 0;x<inp.dat.size();x++){
        string build = "";
        for(int y = inp.dat.size()-1;y>=0;y--){
            build+=inp.dat[y][x];
        }
        out.dat.emplace_back(build);
    }
    return out;
}

int checkNeighbor(Tile& base, Tile& checker){
    vector<string> aEdges, bEdges;
    aEdges = getEdges(base);
    bEdges = getEdges(checker);

    if(aEdges[0] == bEdges[2])
        return 0;
    if(aEdges[1] == bEdges[3])
        return 1;
    if(aEdges[2] == bEdges[0])
        return 2;
    if(aEdges[3] == bEdges[1])
        return 3;
    return -1;
}

pair<int, int> crd(int x,int y){
    return make_pair(x, y);
}

int main(){
    vector<Tile> inp;
    fstream file("input");
    string line;
    vector<string> build;
    while(getline(file, line)){
        if(line.back() == '\r'){
            line.pop_back();
        }
        if(line.empty()){
            inp.emplace_back(build);
            build.clear();
        }else
            build.push_back(line);
    }
    inp.emplace_back(build);

    for(auto& t: inp){
        t.print();
    }

    map<pair<int, int>, Tile> m;
    m[crd(0,0)] = inp[0];
    for(int i =1;i<inp.size();i++){
        int dir = checkNeighbor(inp[0], inp[i]);
        if(dir != -1){
            cout<<"Tiles"<<endl;
            inp[0].print();
            cout<<"And "<<endl;
            inp[i].print();
            cout<<"Are neighbors! in the "<<dir<<" direction."<<endl;
            switch(dir){
                case 0: m[crd(0,1)] = inp[i]; inp.erase(inp.begin()+i);break;
                case 1: m[crd(1,0)] = inp[i]; inp.erase(inp.begin()+i);break;
                case 2: m[crd(0,-1)] = inp[i]; inp.erase(inp.begin()+i);break;
                case 3: m[crd(-1,0)] = inp[i]; inp.erase(inp.begin()+i);break;
            }
        }
    }
    
    for(int x = -1;x<=1;x++){
        for(int y = -1;y<=1;y++){
            if(m.find(crd(x,y))!=m.end()){
                cout<<m[crd(x,y)].id<<" ";
            }else{
                cout<<"???? ";
            }
        }cout<<endl;
    }
}