#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#include<map>
#include<set>
#include<iostream>
#include<fstream>
using namespace std;
class Node
{
    public:
    vector<vector<int> > pegs;
    string State;
    vector<Node*> Neighbors;
    vector<Node*> Predecessors;
    int dist;
    Node(int SIZE,char state){//initiates a initial state
        pegs.resize(3);
        switch(state){
            case 's'://Start
            for(int i = 0;i<SIZE;i++){
                pegs[0].push_back(i+1);
                //Starts in Reversed State: <12345|-|->
                //Target is go to State <54321|-|->
            }
            break;
            case 't'://Target
            for(int i = 0;i<SIZE;i++){
                pegs[0].push_back(SIZE-i);
                //Starts in Reversed State: <12345|-|->
                //Target is go to State <54321|-|->
            }
            break;
        }
        this->makeState();
        dist = 0;
    };
    Node(int SIZE,char state, string customize){//initiates with customized state
        pegs.resize(3);
        if(state!='c') return;
        State = customize;
        int cur = 0;
        for(int i = 0;i<customize.length();i++){
            if(customize[i] == '<'||customize[i] == '>') continue;
            else if(customize[i] == '|') cur++;
            else pegs[cur].push_back((customize[i]-'0'));
        }
    }
    Node(vector<vector<int> > state,int Dist){//initiates a state as mentioned
        pegs = state;
        dist = Dist;
        this->makeState();
    }
    void makeState(){
        State+="<";
        for(int i = 0;i<pegs.size();i++)
        {
//            if(pegs[i].size()==0) State+="-";
            if(pegs[i].size()==0) ;
            else{
                for(auto j:pegs[i]){
                    State+=to_string(j);
                }
            }
            if(i!=pegs.size()-1)State+="|";
        }

        State+=">";
    }
    void printState(){
        cout << State;
/*        for(auto i:pegs){
            for(auto j:i) cout << j;
            cout << "|";
        }cout << endl;
*/    }
};
class Edge
{
public:
    int x = -1;
    int y = -1;
    Edge(int x, int y): x(x), y(y){}

    bool operator<(const Edge& other) const {
        return (x==other.x)?(y<other.y):(x < other.x);
    }

};

class Graph
{
    public:
    Graph(Node* Start):Start(Start){};
    void Generate();
    void printGraph();
    void printinGraphForm();
    int GetNodeId(Node*);
    map<Node*,int> V;
    set<Edge> E;
    map<string,Node*> M;
    deque<string> path;
    Node* Start;
    int numberUnique = 0;
    int BFS(Node* start);
    void printPath(ofstream& out, Node* end);
};

int Graph::GetNodeId(Node* N){
    if(V.find(N)==V.end()){
        cout << "Error!!!" << endl;
        cout << "Cannot find Node: " << N->State << endl;
        return -1;
    }
    return V.find(N)->second;
}

void Graph::printPath(ofstream& out, Node* end){
	path.push_front(end->State);
	for(auto i:end->Predecessors)
	{
		printPath(out, i);
	}
	if(end==Start){
		numberUnique++;
		for(int i = 0;i<path.size();i++)
		{
			if(i==path.size()-1) out << path[i] << endl;
			else out << path[i] << " to ";
		}
	}
	path.pop_front();
}

void Graph::Generate()
{
    queue<Node*> Q;
    Q.push(Start);
    M.insert(pair<string,Node*>(Start->State,Start));
    while(!Q.empty())
    {
        Node* tmp = Q.front();
        V.insert(pair<Node*,int>(tmp,V.size()+1));
        Q.pop();

        string key = tmp->State;
        for(int i = 0;i<2;i++)
        {
            for(int j = i+1;j<3;j++)
            {
                if(tmp->pegs[i].size() == 0 && tmp->pegs[j].size() == 0)// peg i,j are empty
                {
                    continue;
                }
                else if(tmp->pegs[i].size() != 0 && tmp->pegs[j].size() == 0)// peg j is empty
                {
                    vector<vector<int> > X = tmp->pegs;
                    X[j].push_back(X[i].back());
                    X[i].pop_back();
                    Node* pushed = new Node(X,tmp->dist+1);
                    if(M.find(pushed->State) == M.end())
                        {
                            Q.push(pushed);
                            M.insert(pair<string,Node*>(pushed->State, pushed));
                            tmp->Neighbors.push_back(pushed);
                            pushed->Predecessors.push_back(tmp);
                        }
                    else
                        {
                            pushed = M.find(pushed->State)->second;
                            tmp->Neighbors.push_back(pushed);
                            if(M.find(pushed->State)->second->dist == (tmp->dist+1)) M.find(pushed->State)->second->Predecessors.push_back(tmp);
                        }
                }
                else if(tmp->pegs[i].size() == 0 && tmp->pegs[j].size() != 0)// peg i is empty
                {
                    vector<vector<int> > X = tmp->pegs;
                    X[i].push_back(X[j].back());
                    X[j].pop_back();
                    Node* pushed = new Node(X,tmp->dist+1);
                    if(M.find(pushed->State) == M.end())
                    {
                        Q.push(pushed);
                        M.insert(pair<string,Node*>(pushed->State, pushed));
                        tmp->Neighbors.push_back(pushed);
                        pushed->Predecessors.push_back(tmp);
                    }
                    else
                    {
                        pushed = M.find(pushed->State)->second;
                        tmp->Neighbors.push_back(pushed);
                        if(M.find(pushed->State)->second->dist == (tmp->dist+1)) M.find(pushed->State)->second->Predecessors.push_back(tmp);
                    }
                }
                else
                {
                    vector<vector<int> > X = tmp->pegs;
                    X[j].push_back(X[i].back());
                    X[i].pop_back();
                    Node* pushed = new Node(X,tmp->dist+1);
                    if(M.find(pushed->State) == M.end())
                    {
                        Q.push(pushed);
                        M.insert(pair<string,Node*>(pushed->State, pushed));
                                    tmp->Neighbors.push_back(pushed);
                        pushed->Predecessors.push_back(tmp);
                    }
                    else
                    {
                        pushed = M.find(pushed->State)->second;
                        tmp->Neighbors.push_back(pushed);
                        if(M.find(pushed->State)->second->dist == (tmp->dist+1)) M.find(pushed->State)->second->Predecessors.push_back(tmp);
                    }
                    vector<vector<int> > Y = tmp->pegs;
                    Y[i].push_back(Y[j].back());
                    Y[j].pop_back();
                    Node* pushed_y = new Node(Y,tmp->dist+1);
                    if(M.find(pushed_y->State) == M.end())
                    {
                        Q.push(pushed_y);
                        M.insert(pair<string,Node*>(pushed_y->State, pushed_y));
                        tmp->Neighbors.push_back(pushed_y);
                        pushed_y->Predecessors.push_back(tmp);
                    }
                    else
                    {
                        pushed_y = M.find(pushed_y->State)->second;
                        tmp->Neighbors.push_back(pushed_y);
                        if(M.find(pushed_y->State)->second->dist == (tmp->dist+1)) M.find(pushed_y->State)->second->Predecessors.push_back(tmp);
                    }
                }
            }
            //Make Neighbors of tmp
        }
    }
    return ;
}

void Graph::printGraph()
{
    for(auto i:M)
    {
        i.second->printState();
        cout << endl << "Dist : " << i.second->dist << endl << "Neighbors : ";
        for(auto j:i.second->Neighbors)
        {
            j->printState();
            cout << ", ";
        }cout << endl;
        cout << "Predecessors: ";
        for(auto j:i.second->Predecessors)
        {
            j->printState();
            cout << ", ";
        }cout << endl;
    }
    cout << "Graph printed" << endl;
}

void Graph::printinGraphForm(){
    ofstream outputFile;
    outputFile.open("3_output.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return ; // Return error code
    }

    // Write data to the file
//    outputFile << "Hello, World!" << std::endl;
//    outputFile << "This is a line written to the file." << std::endl;

    for (auto it = V.begin(); it != V.end(); ++it) {
        Node* cur = it->first;
        for(auto j:cur->Neighbors){
            int small = (GetNodeId(cur)>GetNodeId(j))?GetNodeId(j):GetNodeId(cur);
            int big = (GetNodeId(cur)>GetNodeId(j))?GetNodeId(cur):GetNodeId(j);
            Edge etmp = Edge(small,big);
            E.insert(etmp);
        }
    }

    for (auto it = V.begin(); it != V.end(); ++it) {
        outputFile << GetNodeId(it->first) << /*" " << it->first->State <<*/ endl;
    }
    for (auto i = E.begin(); i != E.end(); ++i) {
        outputFile << i->x << " " << i->y /*<< " 1"*/ << endl;
    }

    // Close the file
    outputFile.close();
    outputFile.open("Accordance.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return ; // Return error code
    }

    for(int i = 1;i<=V.size();i++){
        for(auto j = V.begin(); j != V.end(); ++j){
            if(GetNodeId(j->first)==i){
                outputFile << i << ": " << j->first->State << endl;
                break;
            }
        }
    }
    outputFile.close();
}

int main(){
    int SIZE;
    int samples;
    char type;
    ofstream out;
    out.open("out_7.txt");
    cout << "Please input size of graph: ";
    cin >> SIZE;
    cout << "Please input the type of input:\nc for customized, s for standard, m for multiple samples with same source.\n";
    cin >> type;
    Node* s;
    Node* t;
    if(type == 's'){
        s = new Node(SIZE,'s');
        t = new Node(SIZE,'t');
    }
    else if(type == 'c'){
        string ttmp;
        cout << "Please input the starting state" << endl;
        cin >> ttmp;
        s = new Node(SIZE,'c', ttmp);
        cout << "Please input the target state" << endl;
        cin >> ttmp;
        t = new Node(SIZE,'c', ttmp);
        s->printState();
        t->printState();
    }
    else if (type == 'm'){
        cout << "Please input number of samples: ";
        cin >> samples;
        s = new Node(SIZE,'t');
    }
    Graph* G = new Graph(s);
    G->Generate();
    cout << "G Size: " << G->M.size() << endl;
    if(type=='m'){
        while(samples--){
            string target;
            cin >> target;
            Node* tmp = G->M.find(target)->second;
            out << "Dist: " << tmp->dist << endl;
            G->printPath(out, tmp);
        }
    }
    else{
        Node* tmp = G->M.find(t->State)->second;
        out << "Dist: " << tmp->dist << endl;
        G->printPath(out, tmp);
    }
    /*
    s->printState();
    // G->printGraph();
//    G->printinGraphForm();
    */
    return 0;
}
