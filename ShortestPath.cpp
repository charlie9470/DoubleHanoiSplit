#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#include<map>
using namespace std;
class Node
{
    public:
    vector<vector<char>> pegs;
    string State;
    vector<Node*> Neighbors;
    vector<Node*> Predecessors;
    int dist;
    Node(int SIZE){//initiates a initial state
        pegs.resize(3);
        for(int i = 0;i<SIZE;i++){
            pegs[0].push_back(65+i);
            pegs[0].push_back(97+i);
            //Thus from the bottom to top the disks should be AaBbCcDdEe
            //Meaning that E is the smallest disk and A the biggest, whilest A and a are of the same size
        }
        this->makeState();
        dist = 0;
    };
    Node(int SIZE,char mode){//initiates a initial state
        pegs.resize(3);
        switch(mode){
        case 'U':
            for(int i = 0;i<SIZE;i++){
                pegs[0].push_back(97+i);
                pegs[2].push_back(65+i);
            }
            break;
        case 'D':
            for(int i = 0;i<SIZE;i++){
                pegs[0].push_back(65+i);
                pegs[2].push_back(97+i);
            }
            break;
        case 'S':
            for(int i = 0;i<SIZE;i++){
                pegs[1].push_back(65+i);
                pegs[2].push_back(97+i);
            }
            break;
        default:
            break;
        }
        this->makeState();
    };
    Node(vector<vector<char>> state,int Dist){//initiates a state as mentioned
        pegs = state;
        dist = Dist;
        this->makeState();
    }
    void makeState(){
        State+="<";
        for(int i = 0;i<pegs.size();i++)
        {
            if(pegs[i].size()==0) State+="-";
            else{
                for(auto j:pegs[i]){
                    State+=j;
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
                    vector<vector<char>> X = tmp->pegs;
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
                    vector<vector<char>> X = tmp->pegs;
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
                else if(abs(tmp->pegs[i].back() - tmp->pegs[j].back()) == 32)// peg i and j have disks of same size
                {
//                    cout << "Same size disks: " << abs(tmp->pegs[i].back() - tmp->pegs[j].back()) << endl;
                    vector<vector<char>> X = tmp->pegs;
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

                    vector<vector<char>> Y = tmp->pegs;
                    Y[i].push_back(Y[j].back());
                    Y[j].pop_back();
                    Node* pushed_Y = new Node(Y,tmp->dist+1);
		    if(M.find(pushed_Y->State) == M.end())
		    {
		        Q.push(pushed_Y);
			M.insert(pair<string,Node*>(pushed_Y->State, pushed_Y));
                        tmp->Neighbors.push_back(pushed_Y);
			pushed_Y->Predecessors.push_back(tmp);
		    }
		    else
		    {
                        tmp->Neighbors.push_back(pushed_Y);
			if(M.find(pushed_Y->State)->second->dist == (tmp->dist+1)) M.find(pushed_Y->State)->second->Predecessors.push_back(tmp);
		    }
                }
                else {
                    int f = tmp->pegs[i].back()>=97?tmp->pegs[i].back()-97:tmp->pegs[i].back()-65;
                    int s = tmp->pegs[j].back()>=97?tmp->pegs[j].back()-97:tmp->pegs[j].back()-65;
//                    cout << "f: " << f << ", s: " << s << endl;
                    if(f>s)
                    {
                        vector<vector<char>> X = tmp->pegs;
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
                    else
                    {
                        vector<vector<char>> X = tmp->pegs;
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
}
int main(){
    int SIZE;
    cout << "Please input size of graph: ";
    cin >> SIZE;
    Node* s = new Node(SIZE);
    Node* U = new Node(SIZE, 'U');
    Node* D = new Node(SIZE, 'D');
    Node* S = new Node(SIZE, 'S');
//    s->printState();
    Graph* G = new Graph(s);
    G->Generate();
    cout << "G Size: " << G->M.size() << endl;
//    G->printGraph();
    Node* tmp = G->M.find(U->State)->second;
    cout << "U" << tmp->State <<": " << tmp->dist << endl;
    cout << "Path(s): " << endl;
    G->printPath(tmp);
    cout << "Number of unique paths: " << G->numberUnique << endl;
    G->numberUnique = 0;
    tmp = G->M.find(D->State)->second;
    cout << "D" << tmp->State <<": " << tmp->dist << endl;
    cout << "Path(s): " << endl;
    G->printPath(tmp);
    cout << "Number of unique paths: " << G->numberUnique << endl;
    G->numberUnique = 0;
    tmp = G->M.find(S->State)->second;
    cout << "S" << tmp->State <<": " << tmp->dist << endl;
    cout << "Path(s): " << endl;
    G->printPath(tmp);
    cout << "Number of unique paths: " << G->numberUnique << endl;
    G->numberUnique = 0;
    return 0;
}
