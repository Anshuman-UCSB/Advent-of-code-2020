#include "../utility.cpp"
#define vInt vector<int>
enum baseDirections{
    ne, e, se, sw, w, nw
};

struct Directions{
    vector<int> dirs;
    // ne, e, se, sw, w, nw
    Directions(string inp){
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
    }

    void print(){
        cout<<"Ne: "<<dirs[ne]<<endl;
        cout<<"E : "<<dirs[e]<<endl;
        cout<<"Se: "<<dirs[se]<<endl;
        cout<<"Sw: "<<dirs[sw]<<endl;
        cout<<"W : "<<dirs[w]<<endl;
        cout<<"Nw: "<<dirs[nw]<<endl;
    }

    void simplify(){
        // cout<<dirs<<endl;
        map<vector<int>, vector<int>> equiv;
        equiv[vInt{1,0,0,1,0,0}] = vInt{0,0,0,0,0,0};
        equiv[vInt{0,1,0,0,1,0}] = vInt{0,0,0,0,0,0};
        equiv[vInt{0,0,1,0,0,1}] = vInt{0,0,0,0,0,0};
        equiv[vInt{1,0,1,0,0,0}] = vInt{0,1,0,0,0,0};
        equiv[vInt{0,1,0,1,0,0}] = vInt{0,0,1,0,0,0};
        equiv[vInt{0,0,1,0,1,0}] = vInt{0,0,0,1,0,0};
        equiv[vInt{0,0,0,1,0,1}] = vInt{0,0,0,0,1,0};
        equiv[vInt{1,0,0,0,1,0}] = vInt{0,0,0,0,0,1};
        equiv[vInt{0,1,0,0,0,1}] = vInt{1,0,0,0,0,0};
        for(auto& p: equiv){
            repeat:;
            for(int i =0 ;i<6;i++){
                if(dirs[i]<p.first[i]){
                    goto next;
                }
            }
            // cout<<"Matching simplification for "<<p.first<<" to "<<p.second<<endl;
            for(int i = 0;i<6;i++){
                dirs[i]-=p.first[i];
                dirs[i]+=p.second[i];
            }
            goto repeat;
            next:;            
        }
        for(int i = 0;i<6;i++){
            if(dirs[i]<0){
                dirs[(i+3)%6]-=dirs[i];
                dirs[i] = 0;
            }
        }
    }
};

int main(){
    vector<string> raw = readFile("input");
    map<vInt, bool> tiles;
    for(auto& l: raw){
        // cout<<l<<endl;
        Directions d(l);
        d.simplify();
        tiles[d.dirs] = !tiles[d.dirs];
    }
    // cout<<tiles<<endl;
    int p1= 0;
    for(auto& p: tiles){
        p1+=p.second;
    }
    cout<<"Part 1: "<<p1<<endl;
}

// 555 too high