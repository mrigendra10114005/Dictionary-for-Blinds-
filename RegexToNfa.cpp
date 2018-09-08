#include<bits/stdc++.h>

using namespace std;

struct Nearest
{
    vector<int> a[2], e;
    bool f=0;
};

vector<Nearest> NFA;

struct dist
{
    int a[2] = {-1,-1};
    bool f=0;
};

vector<dist> DFA;

stack<int> st;

int NFA_size, DFA_size;
string distpregex;

struct Nearest init_NFA_state;

struct dist init_DFA_state;

void custom_clear() {
    for(int i=0; i<100; i++) cout<<endl;
}

// regex to NFA

string insert_concat(string regexp){
    string ret="";
    char c,c2;
    for(unsigned int i=0; i<regexp.size(); i++){
        c=regexp[i];
        if(i+1<regexp.size()){
            c2=regexp[i+1];
            ret+=c;
            if(c!='('&&c2!=')'&&c!='+'&&c2!='+'&&c2!='*'){
                ret+='.';
            }
        }
    }
    ret+=regexp[regexp.size()-1];
    return ret;
}

void character(int i)
{
    NFA.push_back(init_NFA_state);
    NFA.push_back(init_NFA_state);
    NFA[NFA_size].a[i].push_back(NFA_size+1);
    st.push(NFA_size);
    NFA_size++;
    st.push(NFA_size);
    NFA_size++;
}

void union_()
{
    NFA.push_back(init_NFA_state);
    NFA.push_back(init_NFA_state);
    int d = st.top(); st.pop();
    int c = st.top(); st.pop();
    int b = st.top(); st.pop();
    int a = st.top(); st.pop();
    NFA[NFA_size].e.push_back(a);
    NFA[NFA_size].e.push_back(c);
    NFA[b].e.push_back(NFA_size+1);
    NFA[d].e.push_back(NFA_size+1);
    st.push(NFA_size);
    NFA_size++;
    st.push(NFA_size);
    NFA_size++;
}

void concatenation()
{
    int d = st.top(); st.pop();
    int c = st.top(); st.pop();
    int b = st.top(); st.pop();
    int a = st.top(); st.pop();
    NFA[b].e.push_back(c);
    st.push(a);
    st.push(d);
}

void kleene_star()
{
    NFA.push_back(init_NFA_state);
    NFA.push_back(init_NFA_state);
    int b = st.top();
    st.pop();
    int a = st.top();
    st.pop();
    NFA[NFA_size].e.push_back(a);
    NFA[NFA_size].e.push_back(NFA_size+1);
    NFA[b].e.push_back(a);
    NFA[b].e.push_back(NFA_size+1);
    st.push(NFA_size);
    NFA_size++;
    st.push(NFA_size);
    NFA_size++;
}

void postfix_to_NFA(string postfix)
{
    for(unsigned int i=0; i<postfix.size(); i++)
    {
        switch(postfix[i])
        {
        case 'a':
        case 'b': character(postfix[i]-'a'); break;
        case '*': kleene_star(); break;
        case '.': concatenation(); break;
        case '+': union_();
        }
    }
}

void display_NFA()
{
    cout<<endl<<endl;
    cout<<"Phase 1: regex to NFA conversion using thompson's coNearestruction algorithm\n";
    cout<<"------------------------------------------------------------------------\n";
    cout<<"State\t|\ta\t|\tb\t|\teps\t|accepting state|"<<endl;
    cout<<"------------------------------------------------------------------------\n";
    for(unsigned int i=0; i<NFA.size(); i++)
    {
        cout<<i<<"\t|\t";
        for(unsigned int j=0; j<NFA[i].a[0].size(); j++)cout<<NFA[i].a[0][j]<<' ';
        cout<<"\t|\t";
        for(unsigned int j=0; j<NFA[i].a[1].size(); j++)cout<<NFA[i].a[1][j]<<' ';
        cout<<"\t|\t";
        for(unsigned int j=0; j<NFA[i].e.size(); j++)cout<<NFA[i].e[j]<<' ';
        cout<<"\t|\t";
        if(NFA[i].f)cout<<"Yes"; else cout<<"No";
        cout<<"\t|\n";
    }
    cout<<"------------------------------------------------------------------------\n";
}

int priority(char c){
    switch(c){
        case '*': return 3;
        case '.': return 2;
        case '+': return 1;
        default: return 0;
    }
}

string regexp_to_postfix(string regexp)
{
    string postfix="";
    stack<char> op;
    char c;
    for(unsigned int i=0; i<regexp.size(); i++)
    {
        switch(regexp[i])
        {
            case 'a':
            case 'b':
                postfix+=regexp[i]; break;
            case '(':
                op.push(regexp[i]); break;
            case ')':
                while(op.top()!='('){
                    postfix+=op.top();
                    op.pop();
                }
                op.pop();
                break;
            default:
                while(!op.empty()){
                    c=op.top();
                    if(priority(c)>=priority(regexp[i])){
                        postfix+=op.top();
                        op.pop();
                    }
                    else break;
                }
                op.push(regexp[i]);
        }
        //cout<<regexp[i]<<' '<<postfix<<endl;
    }
    while(!op.empty())
    {
        postfix += op.top();
        op.pop();
    }
    return postfix;
}

// NFA to DFA 

void print_DFA(){
    cout<<endl;
    cout<<"NFA TO DFA CONVERSION"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"STATE\t|\t"<<"a"<<"\t|\t"<<"b"<<"\t|\t"<<"FINAL"<<"\t|"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for(int i=0;i<DFA.size();i++){
        cout<<i<<"\t|\t"<<DFA[i].a[0]<<"\t|\t"<<DFA[i].a[1]<<"\t|\t"<<DFA[i].f<<"\t|"<<endl;
    }
    cout<<"---------------------------------------------------------"<<endl;
}

void epsilon_closure(int state,set<int>&si){
    for(unsigned int i=0;i<NFA[state].e.size();i++){
        if(si.count(NFA[state].e[i])==0){
            si.insert(NFA[state].e[i]);
            epsilon_closure(NFA[state].e[i],si);
        }
    }
}

set<int> state_change(int c,set<int>&si){
    set<int> temp;
    if(c==1){
        for (std::set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            for(unsigned int j=0;j<NFA[*it].a[0].size();j++){
                temp.insert(NFA[*it].a[0][j]);
            }
        }
    }
    else{
        for (std::set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            for(unsigned int j=0;j<NFA[*it].a[1].size();j++){
                temp.insert(NFA[*it].a[1][j]);
            }
        }
    }
    return temp;
}

void NFA_to_DFA(set<int>&si,queue<set<int> >&que,int start_state){
    map<set<int>, int> mp;
    mp[si]=-1;
    set<int> temp1;
    set<int> temp2;
    int ct=0;
    si.clear();
    si.insert(0);
    epsilon_closure(start_state,si);
    if(mp.count(si)==0){
        mp[si]=ct++;
        que.push(si);
    }
    int p=0;
    bool f1=false;
    while(que.size()!=0){
        DFA.push_back(init_DFA_state);
        si.empty();
        si=que.front();
        f1=false;
        for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            if(NFA[*it].f==true)
                f1=true;
        }
        DFA[p].f=f1;
        temp1=state_change(1,si);
        si=temp1;
        for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            epsilon_closure(*it,si);
        }
        if(mp.count(si)==0){
            mp[si]=ct++;
            que.push(si);
            DFA[p].a[0]=ct-1;
        }
        else{
            DFA[p].a[0]=mp.find(si)->second;
        }
        temp1.clear();

        si=que.front();
        temp2=state_change(2,si);
        si=temp2;
        for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            epsilon_closure(*it,si);
        }
        if(mp.count(si)==0){
            mp[si]=ct++;
            que.push(si);
            DFA[p].a[1]=ct-1;
        }
        else{
            DFA[p].a[1]=mp.find(si)->second;
        }
        temp2.clear();
        que.pop();
        p++;
    }
    for(int i=0;i<p;i++){
        if(DFA[i].a[0]==-1)DFA[i].a[0]=p;
        if(DFA[i].a[1]==-1)DFA[i].a[1]=p;
    }
    DFA.push_back(init_DFA_state);
    DFA[p].a[0]=p;
    DFA[p].a[1]=p;
    //cout<<p<<endl;
}

//minimum DFA 

// Function to minimize DFA
pair<int,vector<tuple<int,int,bool> > > minimize_DFA(vector<dist> DFA) {
    //cout<<DFA.size()<<endl;
    vector<int> grp(DFA.size());    /// Group number for states
    vector<vector<int> > part(2, vector<int>());   /// Partition for groups

    // Initializing the groups
    part[0].push_back(0);
    for(int i=1; i<(int)grp.size(); i++) {
        if(DFA[i].f==DFA[0].f) {
            grp[i]=0;
            part[0].push_back(i);
        } else {
            grp[i]=1;
            part[1].push_back(i);
        }
    }

    if(!part[1].size()) part.erase(part.end());

    // Loop until no new partition is created
    bool chk=true;  // Check if any new partition is created
    int strt = 0;   // Starting State
    while(chk) {
        chk=false;

        
        //Iterate over partitions and alphabets
        for(int i=0; i<part.size(); i++) {
            for(int j=0; j<2; j++) {
                vector<pair<int,int> > trans(part[i].size());   /// Transitions for the states of partitions
                // Iterate over states of partitions and find transition groups
                for(int k=0; k<part[i].size(); k++) {
                    if(DFA[part[i][k]].a[j] >= 0)
                        trans[k] = make_pair(grp[DFA[part[i][k]].a[j]],part[i][k]);
                    else
                        trans[k] = make_pair(-1,part[i][k]);
                }
                sort(trans.begin(), trans.end());

                // Break partition in case of different transitions
                if(trans[0].first!=trans[trans.size()-1].first) {
                    chk=true;

                    int k, m = part.size()-1;

                    part[i].clear();
                    part[i].push_back(trans[0].second);
                    for(k=1; k<trans.size() and (trans[k].first==trans[k-1].first); k++) {
                        part[i].push_back(trans[k].second);
                    }

                    while(k<trans.size()) {
                        if(trans[k].first!=trans[k-1].first) {
                            part.push_back(vector<int> ());
                            m++;
                        }
                        grp[trans[k].second] = m;
                        part[m].push_back(trans[k].second);
                        k++;
                    }
                }
            }
        }
    }

    for(int i=0; i<part.size(); i++) {
        for(int j=0; j<part[i].size(); j++) {
            if(part[i][j]==0) strt=i;
        }
    }

    vector<tuple<int,int,bool> > ret(part.size());
    
    for(int i=0; i<(int)part.size(); i++) {
       
        get<0>(ret[i]) = (DFA[part[i][0]].a[0]>=0)?grp[DFA[part[i][0]].a[0]]:-1;
        get<1>(ret[i]) = (DFA[part[i][0]].a[1]>=0)?grp[DFA[part[i][0]].a[1]]:-1;
        get<2>(ret[i]) = DFA[part[i][0]].f;
    }

    return make_pair(strt, ret);
}

void print_menu(){
    cout<<"\n---------------------------------------\n";
    cout<<"Input Regex: "<<distpregex<<endl<<endl;
    cout<<"1. NFA\n";
    cout<<"2. Intermediate DFA\n";
    cout<<"3. Minimized DFA\n";
    cout<<"4. Simulation\n";
    cout<<"Press any other key to exit...\n\n";
}

void print(vector<tuple<int,int,bool> > min_DFA) {
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"State\t|\tA\t|\tB\t|\tFinal\t|"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for(int i=0; i<(int)min_DFA.size(); i++) {
        cout<<i<<"\t|\t";
        cout<<get<0>(min_DFA[i])<<"\t|\t";
        cout<<get<1>(min_DFA[i])<<"\t|\t";
        if(get<2>(min_DFA[i])) cout<<"Yes\t|"; else cout<<"No\t|";
        cout<<endl;
    }
    cout<<"---------------------------------------------------------"<<endl;
}

void simulate(int start_st,vector<tuple<int,int,bool> >min_DFA){
    print_menu();
    cout<<"Enter string : ";
    string input;
    cin.ignore();
    getline(cin,input);
    int curr_state,next_state;
    curr_state=start_st;
    custom_clear();
    cout<<"-----------------------------------------"<<endl;
    cout<<"Input\t|\tCurrent\t|\tNext\t|"<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(unsigned i=0;i<input.size();i++){
        if(input[i]=='a')
            next_state=get<0>(min_DFA[curr_state]);
        else
            next_state=get<1>(min_DFA[curr_state]);
        cout<<input[i]<<"\t|\t"<<curr_state<<"\t|\t"<<next_state<<"\t|\n";
        curr_state=next_state;
    }
    cout<<"-----------------------------------------"<<endl;
    cout<<endl<<"Verdict: ";
    if(curr_state>=0&&get<2>(min_DFA[curr_state]))cout<<"Accepted"; else cout<<"Rejected";

    cout<<endl;
}


int main()
{
    custom_clear();
    string regexp,postfix;
    cout<<"Enter Regular Expression: ";
    cin>>regexp;
    distpregex=regexp;
    regexp=insert_concat(regexp);
    postfix = regexp_to_postfix(regexp);
    cout<<"Postfix Expression: "<<postfix<<endl;
    postfix_to_NFA(postfix);

    int final_state=st.top();st.pop();
    int start_state=st.top();st.pop();
    //cout<<start_state<<' '<<final_state<<endl;
    NFA[final_state].f=1;

    set<int> si;
    queue<set<int> > que;
    NFA_to_DFA(si,que,start_state);

    cout<<endl<<endl;

    pair<int,vector<tuple<int,int,bool> > > min_DFA_tmp = minimize_DFA(DFA);

    vector<tuple<int,int,bool> >  min_DFA= min_DFA_tmp.second;
    int start_st = min_DFA_tmp.first;

    getchar();
    custom_clear();


    while(1){
        print_menu();
        char choice;
        choice=getchar();
        custom_clear();

        switch(choice) {
        case '1':
            display_NFA();
            getchar();
            break;
        case '2':
            print_DFA();
            getchar();
            break;
        case '3':
            print(min_DFA);
            getchar();
            break;
        case '4':
            simulate(start_st,min_DFA);
            break;
        default:
            exit(EXIT_SUCCESS);
        }
    }
    cout<<endl<<endl;
    cout<<"Enter string : ";
    string input;
    cin.ignore();
    getline(cin,input);
    int curr_state,next_state;
    while(input!=""){
        //cout<<input<<endl;
        curr_state=start_st;
        for(unsigned i=0;i<input.size();i++){
            if(curr_state>=0){
                if(input[i]=='a')
                    next_state=get<0>(min_DFA[curr_state]);
                else
                    next_state=get<1>(min_DFA[curr_state]);
                if(next_state>=0){
                    cout<<input[i]<<" : State "<<curr_state<<" -> State "<<next_state<<endl;
                }
                else cout<<input[i]<<" : State "<<curr_state<<" -> Trap State"<<endl;
            }
            else cout<<input[i]<<" : Trapped"<<endl;
            curr_state=next_state;
        }
        if(curr_state>=0&&get<2>(min_DFA[curr_state]))cout<<"accepted"; else cout<<"rejected";
        cout<<endl<<endl;
        cout<<"Enter string : ";
        getline(cin,input);
    }
    return 0;
}
//input using c++11 only
//g++ -std=c++11 RegexToNFA.cpp
