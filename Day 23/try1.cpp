#include "../utility.cpp"

void printRound(vector<int>& cups, int ind){
    for(int i = 0;i<cups.size();i++){
        if(i == ind){
            cout<<"(";
        }else{
            cout<<" ";
        }
        cout<<cups[i];
        if(i == ind){
            cout<<")";
        }else{
            cout<<" ";
        }
    }cout<<endl;
}

void iterate(vector<int>& cups, int& ind, bool debug = false){
    vector<int> temp(3);
    int start(cups[ind]),next(cups[(ind+4)%cups.size()]), search, newInd;
        
    for(int i =0 ;i<3;i++){
        temp[i] = cups[(ind+1)%cups.size()];
        cups.erase(cups.begin()+(ind+1)%cups.size());
    }

    for(search = start-1;;search--){
        newInd = findInd(cups, search);
        if(newInd != -1){
            break;
        }
        if(search<=0){
            search = 10;
        }
    }
    // cout<<"looking at "<<search<<endl;
    cups.insert(cups.begin()+newInd+1, temp.begin(), temp.end());
    ind = findInd(cups, next);
    if(debug)
        printRound(cups, ind);
}

int main(){
    fstream file("input");
    string line;
    getline(file, line);
    vector<int> cups, temp(3);
    for(auto& c: line)
        cups.push_back(c-'0');
    cout<<cups<<endl;
    int ind = 0;
    int round = 1;
    cout<<"Round "<<round++<<" :";
    printRound(cups, ind);
    for(int i =0 ;i<10;i++){
        cout<<"Round "<<round++<<" :";
        iterate(cups, ind, true);
    }

}