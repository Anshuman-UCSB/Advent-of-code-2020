#include "../utility.cpp"


void iterate(vector<int>& cups, int& ind, bool debug = false){
    
}

void rotateVect(vector<int>& v, int ind){
    rotate(v.begin(), v.begin()+ind, v.end());
}

void iterate(vector<int>& v){
    int next = v[4];
    vector<int> temp(v.begin()+1, v.begin()+4);
    v.erase(v.begin()+1, v.begin()+4);
    int look = v[0]-1;
    int lInd;
    for(;;look--){
        if(look==0)
            look = 9;
        lInd = findInd(v, look);
        if(lInd!=-1)
            break;
    }
    v.insert(v.begin()+lInd+1, temp.begin(), temp.end());
    rotateVect(v, findInd(v,next));
}

int main(){
    fstream file("input");
    string line;
    getline(file, line);
    vector<int> cups, temp(3);
    for(auto& c: line)
        cups.push_back(c-'0');
    cout<<cups<<endl;
    for(int i = 0;i<100;i++){
        iterate(cups);
    }
    cout<<cups<<endl;
    rotateVect(cups, findInd(cups, 1));
    rotateVect(cups, 1);
    string p1="";
    for(auto& c: cups){
        p1+=to_string(c);
    }
    p1.pop_back();
    cout<<"Part 1: "<<p1<<endl;

}