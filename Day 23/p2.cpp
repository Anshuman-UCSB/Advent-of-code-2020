#include "../utility.cpp"

struct customMap{
    vector<int> m, pickup;
    int maxCup;
    
    customMap(){}
    customMap(int size, string inp){
        vector<int>temp(size);
        m = vector<int>(size+1);
        iota(temp.begin(), temp.end(), 1);
        for(int i =0;i<inp.size();i++)
            temp[i] = (inp[i]-'0');
        m[0] = temp[0];
        for(int i = 0;i<temp.size()-1;i++){
            m[temp[i]] = temp[i+1];
        }
        m[temp.back()] = temp.front();
        maxCup = size;
    }

    void print(){
        
        cout<<"Currently at " <<m[0]<<", list is"<<endl;
        int p = m[0];
        for(int i = 0;i<min(20, int(m.size()));i++){
            cout<<p<<" ";
            p = after(p);
        }cout<<"..."<<endl;
    }

    int getDestination(){
        int out = m[0];
        if(pickup.size()!=3){
            throw("tried to find destination square without pickup.");
        }
        do{
            out--;
            if(out<=0){
                out = maxCup;
            }
        }while(inVect(pickup, out));
        
        return out;
    }

    int after(int n){
        return m[n];
    }

    void iterate(){
        if(!pickup.empty()){
            throw("ERROR PICKUP NOT EMPTY WHEN STARTING ITER.");
        }
        int curr = m[0];
        pickup.push_back(after(curr));
        pickup.push_back(after(pickup.back()));
        pickup.push_back(after(pickup.back()));
        m[curr] = after(pickup.back());
        // cout<<pickup<<endl;
        int dest = getDestination();
        int destNext = after(dest);
        m[dest] = pickup[0];
        m[pickup.back()] = destNext;
        pickup.clear();
        m[0] = after(m[0]);
    }
};

int main(){
    Timer t;
    customMap m(1000000, "716892543");
    m.print();
    const int ROUNDS = 10000000;
    for(int i = 1;i<=ROUNDS;i++){
        if(rand()%1000000 == 1){
            cout<<"On round "<<i<<endl;
        }
        // cout<<i<<": ";
        // m.print();
        m.iterate();
        // cout<<endl;
    }
    // cout<<"Finally after "<<ROUNDS<<" rounds: "<<endl;
    // m.print();
    long long p2(0), c1(m.m[1]), c2(m.m[m.m[1]]);
    cout<<"cup 1> : "<<c1<<endl;
    cout<<"cup 1>>: "<<c2<<endl;
    
    p2 = c1*c2;
    cout<<"Answer for part 2: "<<p2<<endl;
    t.stop();
}

