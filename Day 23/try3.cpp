#include "../utility.cpp"


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
    
    vector<int> cards(1000000);
    iota(cards.begin(), cards.end(), 1);
    for(int i = 0;i<line.size();i++)
        cards[i]=(line[i]-'0');
    vector<Node*> m(cards.size()+1);
    for(auto v: cards)
        m[v] = new Node(v);
    
    // cout<<cards<<endl;

    for(int i = 0;i<cards.size()-1;i++)
        m[cards[i]]->next = m[cards[i+1]];
    m[cards.back()]->next = m[cards.front()];

    Node *head, *headB, *pickA, *pickB, *destA, *destB;
    head = m[cards.front()];
    for(int i =0;i<100000000;i++){
        if(rand()%100000 == 1){
            cout<<"Round "<<i<<endl;
        }
        auto headB = head->next->next->next->next;
        pickA = head->next;
        pickB = pickA->next->next;
        head->next = headB;
        // cout<<"headB: "<<headB->val<<endl;
        vector<int> pickUp = {pickA->val, pickA->next->val, pickB->val};
        int look = head->val -1;
        while(look<=0 || inVect(pickUp, look)){
            if(look == 0)
                look = 10;// look = 1000001;
            look--;
        }
        // cout<<look<<endl;
        destA = m[look];
        destB = destA->next;
        destA->next = pickA;
        pickB->next = destB;
        head = headB;
        
    }
    // auto p = head;
    // for(int i = 0;i<10;i++){
    //     cout<<p->val<<" ";
    //     p = p->next;
    // }cout<<endl;
    cout<<m[1]->next->val<<", "<<m[1]->next->next->val<<endl;
    cout<<"Part 2: "<<(m[1]->next->val)*(m[1]->next->next->val)<<endl;
}

//41812937676 part 2