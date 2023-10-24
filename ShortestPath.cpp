#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;
class Node
{
    public:
    vector<vector<char>> pegs;
    string State;
    vector<Node*> Neighbors;
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
    Node* Start;
    int BFS(Node* start);
};

void Graph::Generate()
{
    queue<Node*> Q;
    Q.push(Start);
    while(!Q.empty())
    {
        Node* tmp = Q.front();
        Q.pop();
        if(M.find(tmp->State) == M.end())
        {
            string key = tmp->State;
            M.insert(pair<string,Node*>(key,tmp));
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
                        Q.push(pushed);
                        tmp->Neighbors.push_back(pushed);
                    }
                    else if(tmp->pegs[i].size() == 0 && tmp->pegs[j].size() != 0)// peg i is empty
                    {
                        vector<vector<char>> X = tmp->pegs;
                        X[i].push_back(X[j].back());
                        X[j].pop_back();
                        Node* pushed = new Node(X,tmp->dist+1);
                        Q.push(pushed);
                        tmp->Neighbors.push_back(pushed);
                    }
                    else if(abs(tmp->pegs[i].back() - tmp->pegs[j].back()) == 32)// peg i and j have disks of same size
                    {
//                        cout << "Same size disks: " << abs(tmp->pegs[i].back() - tmp->pegs[j].back()) << endl;
                        vector<vector<char>> X = tmp->pegs;
                        X[j].push_back(X[i].back());
                        X[i].pop_back();
                        Node* pushed = new Node(X,tmp->dist+1);
                        Q.push(pushed);
                        tmp->Neighbors.push_back(pushed);

                        vector<vector<char>> Y = tmp->pegs;
                        Y[i].push_back(Y[j].back());
                        Y[j].pop_back();
                        Node* pushed_Y = new Node(Y,tmp->dist+1);
                        Q.push(pushed_Y);
                        tmp->Neighbors.push_back(pushed_Y);
                    }
                    else {
                        int f = tmp->pegs[i].back()>=97?tmp->pegs[i].back()-97:tmp->pegs[i].back()-65;
                        int s = tmp->pegs[j].back()>=97?tmp->pegs[j].back()-97:tmp->pegs[j].back()-65;
//                        cout << "f: " << f << ", s: " << s << endl;
                        if(f>s)
                        {
                            vector<vector<char>> X = tmp->pegs;
                            X[j].push_back(X[i].back());
                            X[i].pop_back();
                            Node* pushed = new Node(X,tmp->dist+1);
                            Q.push(pushed);
                            tmp->Neighbors.push_back(pushed);
                        }
                        else
                        {
                            vector<vector<char>> X = tmp->pegs;
                            X[i].push_back(X[j].back());
                            X[j].pop_back();
                            Node* pushed = new Node(X,tmp->dist+1);
                            Q.push(pushed);
                            tmp->Neighbors.push_back(pushed);
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
    tmp = G->M.find(D->State)->second;
    cout << "D" << tmp->State <<": " << tmp->dist << endl;
    tmp = G->M.find(S->State)->second;
    cout << "S" << tmp->State <<": " << tmp->dist << endl;
    return 0;
}
