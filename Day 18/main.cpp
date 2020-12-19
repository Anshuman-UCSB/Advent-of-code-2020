#include "../utility.cpp"

vector<long long> toVect(string inp){
    map<char, long long> mapping = {{'+',-1}, {'*',-2}, {'(',-3}, {')',-4}};
    vector<long long> out;
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

void printEq(vector<long long> inp){
    for(long long c: inp){
        switch(c){
            case -1: cout<<'+';break;
            case -2: cout<<'*';break;
            case -3: cout<<'(';break;
            case -4: cout<<')';break;
            default: cout<<c;break;
        }
    }
}

long long mult(long long a, long long b){
    return a*b;
}

long long add(long long a, long long b){
    return a+b;
}

long long eval(vector<long long> inp){
    if(inVect<long long>(inp, -3) || inVect<long long>(inp, -4)){
        long long l, r;
        long long level = 0;
        l = findInd<long long>(inp, -3);
        for(long long i = l+1;i<inp.size();i++){
            if(inp[i] == -3){
                level++;
            }
            if(inp[i] == -4){
                if(level){
                    level--;
                }else{
                    r = i;
                    break;
                }
            }
        }
        vector<long long> temp = subVector(inp, l+1, r);
        long long insideVal = eval(temp);
        inp.erase(inp.begin()+l, inp.begin()+1+r);
        inp.insert(inp.begin()+l, insideVal);
        // printEq(inp);
        // cout<<endl;
        return eval(inp);
        // cout<<temp<<" = "<<insideVal<<endl;
    }else{ //Base case, no parenthesis.
        queue<long long> nums, op;
        for(auto v: inp){
            if(v>=0){
                nums.push(v);
            }else{
                op.push(v);
            }
            if(op.size()>=1 && nums.size()>=2){
                long long a, b;
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
    long long ans = 0;
    auto inp = readFile();
    for(auto l: inp){
        auto v = toVect(l);
        long val = eval(v);
        printEq(v);
        cout<<" = "<<val<<endl;
        ans += val;
    }
    cout<<"Part 1: "<<ans<<endl;
    //5554483793 too low
}