#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#include<map>
using namespace std;
class Node
{
    public:
    vector<vector<int>> pegs;
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
    Node(vector<vector<int>> state,int Dist){//initiates a state as mentioned
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
    }
};
class Graph
{
    public:
    Graph(Node* Start):Start(Start){};
    void Generate();
    void printGraph();
    map<string,Node*> M;
    deque<string> path;
    Node* Start;
    int numberUnique = 0;
    int BFS(Node* start);
    void printPath(Node* end);
};

void Graph::printPath(Node* end){
	path.push_front(end->State);
	for(auto i:end->Predecessors)
	{
		printPath(i);
	}
	if(end==Start){
		numberUnique++;
		for(int i = 0;i<path.size();i++)
		{
			if(i==path.size()-1) cout << path[i] << endl;
			else cout << path[i] << " to ";
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
                    vector<vector<int>> X = tmp->pegs;
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
                            tmp->Neighbors.push_back(pushed);
                            if(M.find(pushed->State)->second->dist == (tmp->dist+1)) M.find(pushed->State)->second->Predecessors.push_back(tmp);
                        }
                }
                else if(tmp->pegs[i].size() == 0 && tmp->pegs[j].size() != 0)// peg i is empty
                {
                    vector<vector<int>> X = tmp->pegs;
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
                        tmp->Neighbors.push_back(pushed);
                        if(M.find(pushed->State)->second->dist == (tmp->dist+1)) M.find(pushed->State)->second->Predecessors.push_back(tmp);
                    }
                }
                else
                {
                    vector<vector<int>> X = tmp->pegs;
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
                        tmp->Neighbors.push_back(pushed);
                        if(M.find(pushed->State)->second->dist == (tmp->dist+1)) M.find(pushed->State)->second->Predecessors.push_back(tmp);
                    }
                    vector<vector<int>> Y = tmp->pegs;
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
int main(){
    int SIZE;
    cout << "Please input size of graph: ";
    cin >> SIZE;
    Node* s = new Node(SIZE,'s');
    Node* t = new Node(SIZE,'t');
//    s->printState();
    Graph* G = new Graph(s);
    G->Generate();
    cout << "G Size: " << G->M.size() << endl;
    // G->printGraph();
    Node* tmp = G->M.find(t->State)->second;
    cout << "Dist: " << tmp->dist << endl;
    G->printPath(tmp);
    return 0;
}
