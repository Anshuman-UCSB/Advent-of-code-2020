#include "../utility.cpp"

template<class T>
vector<vector<T>> rotate90(const vector<vector<T>>& inp){
    vector<vector<T>> out;
    for(int i= 0;i<inp.size();i++)
        out.emplace_back(inp.size());
    
    for(int x = 0;x<inp.size();x++){
        for(int y = 0;y<inp.size();y++){
            out[x][inp.size()-y-1] = inp[y][x];
        }
    }

    return out;
}

vector<vector<bool>> getEdges(const vector<vector<bool>>& raw);

struct Tile{
    int id;
    vector<vector<bool>> raw;
    Tile():id(-1){}
    Tile(vector<string>& inp){
        stringstream ss(inp[0]);
        string temp;
        ss>>temp>>id;
        for(int i = 1;i<inp.size();i++){
            raw.emplace_back();
            for(auto c: inp[i]){
                raw.back().push_back(c=='#'?true:false);
            }
        }
    }

    Tile(const Tile& t){
        id = t.id;
        raw.clear();
        for(auto& r: t.raw){
            raw.emplace_back(r.begin(), r.end());
        }
    }

    void print(){
        cout<<" <Tile "<<id<<">"<<endl;
        for(auto& r: raw){
            cout<<"[";
            for(auto c: r){
                cout<<(c?"#":".");
            }
            cout<<"]"<<endl;
        }
    }
};

void rotate90(Tile& t){
    vector<vector<bool>> out;
    for(int i= 0;i<t.raw.size();i++)
        out.emplace_back(t.raw.size());
    
    for(int x = 0;x<t.raw.size();x++){
        for(int y = 0;y<t.raw.size();y++){
            out[x][t.raw.size()-y-1] = t.raw[y][x];
        }
    }

    t.raw = out;
}

Tile getMatch(const Tile& base, Tile& t, int dir){
    // 0 up, 1 right, 2 down, 3 left
    vector<bool> edgeToMatch = getEdges(base.raw)[dir];
    reverse(edgeToMatch.begin(), edgeToMatch.end());
    Tile temp(t);

    //First check no flips
    for(int i =0;i<4;i++){
        if(getEdges(temp.raw)[(dir+2)%4] == edgeToMatch){
            return temp;
        }
        rotate90(temp);
    }

    //x flip
    temp = t;
    for(auto& r: t.raw){
        reverse(r.begin(), r.end());
    }
    for(int i =0;i<4;i++){
        if(getEdges(temp.raw)[(dir+2)%4] == edgeToMatch){
            return temp;
        }
        rotate90(temp);
    }

    //y flip
    temp = t;
    reverse(temp.raw.begin(), temp.raw.end());
    for(int i =0;i<4;i++){
        if(getEdges(temp.raw)[(dir+2)%4] == edgeToMatch){
            return temp;
        }
        rotate90(temp);
    }

    //xy flip
    temp = t;
    for(auto& r: t.raw){
        reverse(r.begin(), r.end());
    }
    reverse(temp.raw.begin(), temp.raw.end());
    for(int i =0;i<4;i++){
        if(getEdges(temp.raw)[(dir+2)%4] == edgeToMatch){
            return temp;
        }
        rotate90(temp);
    }
    return Tile();
}


vector<vector<bool>> getEdges(const vector<vector<bool>>& raw){
    vector<vector<bool>> edges;
    edges.push_back(vector<bool>(raw[0].begin(), raw[0].end()));
    edges.emplace_back();
    for(int y = 0;y<raw.size();y++){
        edges.back().push_back(raw[y].back());
    }
    edges.push_back(vector<bool>(raw.back().rbegin(), raw.back().rend()));
    edges.emplace_back();
    for(int y = raw.size()-1;y>=0;y--){
        edges.back().push_back(raw[y][0]);
    }
    return edges;
}

vector<vector<bool>> getEdges(const Tile& t){
    return getEdges(t.raw);
}

int main(){
    fstream file("input");
    string line;
    vector<string> build;
    vector<Tile> tiles;
    while(getline(file, line)){
        if(line.back() == '\r'){
            line.pop_back();
        }
        if(line.empty()){
            tiles.emplace_back(build);
            build.clear();
        }else
            build.push_back(line);
    }
    tiles.emplace_back(build);

    for(auto& t: tiles){
        t.print();
    }
    cout<<tiles.size()<<" tiles."<<endl;

    auto tEdges = getEdges(tiles.back());
    cout<<"The edges for the last tile are: "<<endl;
    cout<<"Top:  "<<tEdges[0]<<endl;
    cout<<"Right:"<<tEdges[1]<<endl;
    cout<<"Bot : "<<tEdges[2]<<endl;
    cout<<"Left: "<<tEdges[3]<<endl;
    map<pair<int, int>, Tile> m;
    m[make_pair(0,0)] = tiles[0];
    int mnX, mnY, mxX, mxY;
    mnX = mnY = 999;
    mxX = mxY = -999;
    for(auto& p: m){
        mnX = min(mnX, p.first.first);
        mxX = max(mxX, p.first.first);
        mnY = min(mnY, p.first.second);
        mxY = max(mxY, p.first.second);
    }
    for(int x = mnX; x<=mxX;x++){
        for(int y = mnY; y<=mxY;y++){
            if(m.find(make_pair(x,y))!=m.end()){
                m[make_pair(x,y)].print();
            }
        }
    }
}
