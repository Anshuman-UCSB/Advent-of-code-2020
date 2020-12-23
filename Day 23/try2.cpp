#include "../utility.cpp"

void iterate(vector<int>& v){

}

struct Node{
    Node():val(-1), next(0){};
    Node(int dat):val(dat), next(0){};
    Node(int dat, Node* n):val(dat), next(n){};
    int val;
    Node* next;  
};



int main(){
    fstream file("input");
    string line;
    getline(file, line);
    vector<int> temp;
    for(auto& c: line)
        temp.push_back(c-'0');
    vector<int> cups(1000000);
    cups = vector<int>(10);
    iota(cups.begin(), cups.end(), 1);
    for(int i = 0;i<temp.size();i++)
        cups[i] = temp[i];
    
    Node* m[1000001];
    for(auto& v: cups)
        m[v] = new Node(v);
    
    for(int i = 0;i<cups.size()-1;i++)
        m[cups[i]]->next = m[cups[i+1]];
    m[cups.back()]->next = m[cups.front()];

    Node* head = m[cups.front()];
    Node* pickupF, *pickupB, *destination;
    Node* insF, *insB;
    for(int i = 0;i<10;i++){
        destination = head->next->next->next->next;
        pickupF = head->next;
        pickupB = head->next->next->next;
        head->next = destination;
        vector<int> invalid= {pickupF->val,
                          pickupF->next->val,
                          pickupB->val};

        int insPoint = head->val - 1;
        while(insPoint == 0 || inVect(invalid, insPoint)){
            if(insPoint == 0)
                insPoint = 1000001;
            insPoint--;
        }
        insF = m[insPoint];
        insB = insF->next;

        insF->next = pickupF;
        pickupB->next = insB;
        head = destination;
    }
    
}