#include "../utility.cpp"

vector<int> toVect(string inp){
    map<char, int> mapping = {{'+',-1}, {'*',-2}, {'(',-3}, {')',-4}};
    vector<int> out;
    string build="";
    bool building = false;
    for(char c: inp){
        if(c>='0' && c<='9' && building == false){
            building = true;
            build+=c;
        }
        else if(building == true && !(c>='0' && c<='9')){
            building = false;
            out.push_back(stoi(build));
            build="";
        }
    }
}

void printEq(vector<int> inp){
    for(int c: inp){
        switch(c){
            case -1: cout<<'+';break;
            case -2: cout<<'*';break;
            default: cout<<c;break;
        }
    }
}

int eval(vector<int>& inp){

}

int main(){
    auto inp = readFile();
    for(auto l: inp){
        printEq(toVect(l));
        cout<<endl;
    }
}