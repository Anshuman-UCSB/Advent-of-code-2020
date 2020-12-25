#include "../utility.cpp"
#define ull unsigned long long

ull getIter(int subject,int iter){
    ull n = 1;
    for(int i =0;i<iter;i++)
        n = (n*subject)%20201227;
    return n;
}

int getLoop(int subject, int target){
    ull n = 1;
    int out = 0;
    while(n!=target && (out++ >=0))
        n = (n*subject)%20201227;
    return out;
}

int main(){
    vector<string> raw = readFile("input");
    int card(stoi(raw[0])), door(stoi(raw[1]));
    int cMod(0), dMod(0);
    cout<<card<<endl<<door<<endl;
    cMod = getLoop(7, card);
    // dMod = getLoop(7, door);
    // cout<<"Card: "<<cMod<<endl<<"Door: "<<dMod<<endl;
    cout<<"Part 1: "<<getIter(door, cMod)<<endl;
}