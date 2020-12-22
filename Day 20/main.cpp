#include "../utility.cpp"

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
            tiles.emplace_back(getFlip(tiles.back()));
            build.clear();
        }else{
            build.push_back(line);
        }
    }
    map<string, vector<int>> m;
    for(auto& t: tiles){
        for(auto e: t.edges){
            m[e].push_back(t.id);
        }
        cout<<endl<<" < "<<t.id<<" > "<<endl;
        for(auto& r: t.raw){
            cout<<r<<endl;
        }
        cout<<t.edges<<endl;
    }
    cout<<m<<endl;
    map<int, int> counter;
    for(auto& p: m){
        for(auto id: p.second){
            if(p.second.size()>1)
                counter[id]++;
        }
    }
    cout<<counter<<endl;
}