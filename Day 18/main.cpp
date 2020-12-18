#include "../utility.cpp"

vector<int> toVect(string inp){
    map<char, int> mapping = {{'+',-1}, {'*',-2}, {'(',-3}, {')',-4}};
    vector<int> out;
    string build="";
    bool building = false;
    for(char c: inp){
        // cout<<"C: "<<c<<endl;
        if(c>='0' && c<='9' && building == false){
            building = true;
            build = "";
            build+=c;
        }
        else if(building == true && !(c>='0' && c<='9')){
            building = false;
            out.push_back(stoi(build));
            build = "";
            if(c != ' ')
                out.push_back(mapping[c]);
        }else if(building){
            build+=c;
        }else{
            if(c != ' ')
                out.push_back(mapping[c]);
        }
    }
    if(!build.empty()){
        out.push_back(stoi(build));
    }
    return out;
}

void printEq(vector<int> inp){
    for(int c: inp){
        switch(c){
            case -1: cout<<'+';break;
            case -2: cout<<'*';break;
            case -3: cout<<'(';break;
            case -4: cout<<')';break;
            default: cout<<c;break;
        }
    }
}

int mult(int a, int b){
    return a*b;
}

int add(int a, int b){
    return a+b;
}

int eval(vector<int>& inp){
    if(inVect(inp, -3) || inVect(inp, -4)){
        cout<<"Has parenth."<<endl; 
    }else{ //Base case, no parenthesis.
        queue<int> nums, op;
        for(auto v: inp){
            if(v>=0){
                nums.push(v);
            }else{
                op.push(v);
            }
            if(op.size()>=1 && nums.size()>=2){
                int a, b;
                b = nums.front();
                nums.pop();
                a = nums.front();
                nums.pop();
                switch(op.front()){
                    case -1:
                        nums.push(add(a,b));
                        break;
                    case -2:
                        nums.push(mult(a,b));
                        break;
                }
                op.pop();
            }
        }
        return nums.front();
    }
}

int main(){
    // vector<int> temp(10);
    // iota(temp.begin(), temp.end(), 0);
    // cout<<temp<<endl;
    // cout<<subVector(temp, 1, 4)<<endl;

    // exit(1);
    auto inp = readFile();
    for(auto l: inp){
        auto v = toVect(l);
        printEq(v);
        cout<<" or "<<v<<endl;
        cout<<endl;
        cout<<eval(v)<<endl;
    }
}