#include "../utility.cpp"
#define c(x,y) make_pair(x,y)

struct Tile{
    vector<string> raw;
    vector<string> edges;
    int id;
    Tile():id(-1){}
    Tile(vector<string>& inp){
        stringstream ss(inp[0]);
        string temp;
        ss>>temp>>id;
        raw = vector<string>(inp.begin()+1, inp.end());
        edges.push_back(inp[1]);
        
        edges.emplace_back("");
        for(int y = 1;y<inp.size();y++){
            edges.back()+=inp[y].back();
        }

        edges.emplace_back(inp.back());
        reverse(edges.back().begin(), edges.back().end());

        edges.emplace_back("");
        for(int y = inp.size()-1;y>=1;y--){
            edges.back()+=inp[y].front();
        }
    }

    void print(){
        cout<<" < "<<id<<" > "<<endl;
        for(auto& r: raw){
            cout<<r<<endl;
        }
    }
};

Tile getFlip(Tile& inp){
    Tile out;
    out.id = inp.id*-1;
    out.raw = vector<string>(inp.raw.rbegin(), inp.raw.rend());
    out.edges = inp.edges;
    swap(out.edges[0], out.edges[2]);
    for(int i = 0;i<4;i++){
        reverse(out.edges[i].begin(), out.edges[i].end());
    }
    return out;
}

Tile getRotate(Tile& inp){
    Tile out;
    out.id = inp.id;
    for(int x = 0;x<inp.raw.size();x++){
        out.raw.emplace_back();
        for(int y = inp.raw[x].size()-1;y>=0;y--){
            out.raw.back()+=inp.raw[y][x];
        }
    }
    out.edges.push_back(out.raw[0]);
        
        out.edges.emplace_back("");
        for(int y = 0;y<out.raw.size();y++){
            out.edges.back()+=out.raw[y].back();
        }

        out.edges.emplace_back(out.raw.back());
        reverse(out.edges.back().begin(), out.edges.back().end());

        out.edges.emplace_back("");
        for(int y = out.raw.size()-1;y>=0;y--){
            out.edges.back()+=out.raw[y].front();
    }

    return out;
}

bool checkEdges(Tile& base, Tile& check, int dir, bool debug = false){
    if(abs(base.id) == abs(check.id)){
        return false;
    }
    if(debug){
        base.print();
        cout<<base.edges<<endl;
        check.print();
        cout<<check.edges<<endl;
    }
    string edgeA(base.edges[dir]);
    string edgeB(check.edges[(dir+2)%4]);
    if(debug){
    cout<<"A: "<<edgeA<<endl;
    cout<<"B: "<<edgeB<<endl;
    }
    reverse(edgeB.begin(), edgeB.end());
    return edgeA == edgeB;
}

pair<bool, Tile> checkRotations(Tile& base, Tile& check, int dir){
    if(abs(base.id) == abs(check.id)){
        return make_pair(false, Tile());
    }
    Tile temp(check);
    for(int i = 0;i<4;i++){
        if(checkEdges(base, temp, dir)){
            return make_pair(true, temp);
        }
        temp = getRotate(temp);
    }
    return make_pair(false, Tile());
}

pair<bool, Tile> checkPermutations(Tile& base, Tile& check, int dir){
    if(abs(base.id) == abs(check.id))
        return make_pair(false, Tile());
    auto t = checkRotations(base, check, dir);
    if(t.first)
        return t;

    auto flipped = getFlip(check);
    t = checkRotations(base, flipped, dir);
    if(t.first)
        return t;
    return make_pair(false, Tile());
}

void printBoard(map<pair<int, int>, Tile>& m){
    int minX, maxX, minY, maxY;
    minX = minY = 999;
    maxX = maxY = -999;
    for(auto& p: m){
        minX = min(minX, p.first.first);
        minY = min(minY, p.first.second);
        maxX = max(maxX, p.first.first);
        maxY = max(maxY, p.first.second);
    }

    cout<<endl;
    for(int y = minY; y<=maxY;y++){
        cout<<"    ";
        for(int x = minX; x<=maxX;x++){
            if(m.find(c(x,y))!=m.end()){
                cout<<abs(m[c(x,y)].id)<<" ";
            }else{
                cout<<"???? ";
            }
        }cout<<endl;
    }
    cout<<endl;
}

pair<int, int> addCoord(pair<int, int>& a, pair<int, int>& b){
    return (c(a.first+b.first, a.second+b.second));
}

void populate(map<pair<int, int>, Tile> &m, vector<Tile>& unplaced, queue<pair<int, int>>& q, set<pair<int, int>>& s, pair<int, int> coord){
    s.insert(coord);
    cout<<"Populating coord "<<coord.first<<", "<<coord.second<<endl;
    vector<pair<int, int>> dirMod = {c(0,1), c(1,0), c(0,-1), c(-1,0)};
    for(int dir = 0;dir<4;dir++){
        for(auto& t: unplaced){
            auto temp = checkPermutations(m[coord], t, dir);
            if(temp.first){
                auto c = addCoord(dirMod[dir],coord);
                m[c] = temp.second;
                if(s.insert(c).second)
                    q.push(c);
            }
        }
    }
}

int main(){
    fstream file("input");
    string line;
    vector<string> build;
    vector<Tile> tiles;
    while(getline(file, line)){
        if(line.back() == '\r')
            line.pop_back();
        if(line.empty()){
            tiles.emplace_back(build);
            // tiles.emplace_back(getFlip(tiles.back()));
            build.clear();
        }else{
            build.push_back(line);
        }
    }
    tiles.emplace_back(build);

    vector<Tile> unplaced(tiles.begin(), tiles.end());
    queue<pair<int, int>> q;
    map<pair<int, int>, Tile> m;
    for(auto t: tiles){
        cout<< t.id<< " ";
    }cout<<endl;
    m[c(0, 0)] = unplaced[0];
    unplaced.erase(unplaced.begin() + 0);
    q.push(c(0,0));

    // for(auto& t: tiles){
    //     t.print();
    // }
    const int maxSize = 144;
    set<pair< int, int>> s;
    s.insert(c(0,0));
    while(m.size() <maxSize){
        populate(m, unplaced, q, s, q.front());
        q.pop();
        printBoard(m);
    }

    // cout<<"Edges: "<<checkEdges(tiles[0], tiles[3], 0)<<endl;
    // vector<pair<int, int>> dirMod = {c(0,1), c(1,0), c(0,-1), c(-1,0)};
    // for(auto& t: unplaced){
    //     for(int i = 0;i<4;i++){
    //         auto temp = checkPermutations(m[c(0, 0)], t, i);
    //         if(temp.first){
    //             m[dirMod[i]] = temp.second;
    //             q.push(dirMod[i]);
    //         }
    //     }
    // }

    
    // tiles[3].print();
    // getRotate(tiles[5]).print();
}