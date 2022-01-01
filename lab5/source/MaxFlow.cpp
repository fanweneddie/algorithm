#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INFINITY = 100000000;
// represents an edge
class Edge
{
    public:
    int flow;
    int capacity;
};

// color of a vertex
enum Color
{
    WHITE,GRAY,BLACK
};

// represents a vertex in vertex list
class Vex
{
    public:
    Color color;
    int parent;
};

// the result of BFS
class Result
{
    public:
    // augmented flow
    int cf;
    vector<int> path;
};

// original Network: using adj_matrix
class Network
{
    public:
    int v_num;
    int e_num;
    int source;
    int dest;
    // adjmatrix storing flow and capacity for each edge
    vector<vector<Edge>> adj_matrix;
    // constructor
    Network(int v,int e,int src,int dst)
    {
        v_num = v;
        e_num = e;
        source = src;
        dest = dst;
        adj_matrix.resize(v_num + 1);
        for(int i = 0;i <= v_num;++i)
        {
            adj_matrix[i].resize(v_num + 1);
            for(int j = 0; j <= v_num;++j)
            {
                adj_matrix[i][j].flow = 0;
                adj_matrix[i][j].capacity = 0;
            }
        }
    }
    // add an edge with capacity to Graph
    void append_edge(int u,int v,int capa)
    {
        adj_matrix[u][v].capacity += capa;
    }

    void output()
    {
        cout << "-----------------------------\n";
        for(int i = 1; i <= v_num;++i)
        {
            for(int j = 1; j<= v_num;++j)
            {
                cout << adj_matrix[i][j].flow << " ";
            }
            cout << endl;
        }
    }
};

// Residual Network: using adjmatrix
class Res_Network
{
    public:
    int v_num;
    int e_num;
    int source;
    int dest;
    // adj_matrix to store capacity on each edge
    vector<vector<int>> adj_matrix;

    // copy constructor for init
    Res_Network(const Network &G)
    {
        v_num = G.v_num;
        e_num = G.e_num;
        source = G.source;
        dest = G.dest;

        adj_matrix.resize(v_num + 1);
        for(int i = 0;i <= v_num;++i)
        {
            adj_matrix[i].resize(v_num + 1);
        }
    }

    // get the residual network from G
    void get_residual(const Network &G)
    {
        for(int i = 1;i <= v_num;++i)
        {
            for(int j = 1;j <= v_num;++j)
            {
                if(G.adj_matrix[i][j].capacity > 0)
                    adj_matrix[i][j] = G.adj_matrix[i][j].capacity 
                        - G.adj_matrix[i][j].flow;
                else if(G.adj_matrix[j][i].capacity > 0)
                    adj_matrix[i][j] = G.adj_matrix[j][i].flow;
                else
                    adj_matrix[i][j] = 0;
            }
        }
    }

    void output()
    {
        cout << "-----------------------------\n";
        for(int i = 1; i <= v_num;++i)
        {
            for(int j = 1; j <= v_num;++j)
            {
                cout << adj_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // implementing BFS on residual network
    // get the cf and path from source to dest.
    Result BFS()
    {
        // vertex list
        vector<Vex> v_list;
        // init v_list
        Vex vex;
        vex.color = WHITE;
        vex.parent = 0;
        for(int i = 0;i <= v_num;++i)
            v_list.push_back(vex);
        // init Queue
        queue<int> Queue;
        v_list[source].color = GRAY;
        Queue.push(source);

        // BFS
        while(!Queue.empty())
        {
            int u = Queue.front();
            Queue.pop();
            for(int i = 1;i <= v_num;++i)
            {
                // get edge from adj[u]
                if(adj_matrix[u][i] > 0)
                {
                    if(v_list[i].color == WHITE)
                    {
                        v_list[i].color = GRAY;
                        v_list[i].parent = u;
                        Queue.push(i);
                    }
                }
            }// for
            v_list[u].color = BLACK;
        }// while

        // get cf in the residual network
        int v = dest;
        int u;
        // result to return
        Result result;
        result.cf = INFINITY;
        result.path.push_back(v);
        // get cf and path
        while( v_list[v].parent != 0 && v != source )
        {   
            u = v_list[v].parent;
            result.path.push_back(u);
            if(adj_matrix[u][v] < result.cf)
            {
                result.cf = adj_matrix[u][v];
            }
            v = u;
        }
        // there doesn't exist augment path
        if(v != source)
            result.cf = 0;
        return result;
    }

};

int ford_fulkerson(Network &G)
{
    Res_Network RG = Res_Network(G);
    Result BFS_res;
    int total_flow = 0;
    RG.get_residual(G);
    BFS_res = RG.BFS();
    // iteration
    while(BFS_res.cf > 0)
    {
        // alter flow
        int path_len = BFS_res.path.size()-1; 
        for(int i = path_len;i >= 1;--i)
        {
            if(G.adj_matrix[ BFS_res.path[i] ][ BFS_res.path[i-1] ].capacity > 0)
                G.adj_matrix[ BFS_res.path[i] ][ BFS_res.path[i-1] ].flow += BFS_res.cf;
            else if(G.adj_matrix[ BFS_res.path[i-1] ][ BFS_res.path[i] ].capacity > 0)
                G.adj_matrix[ BFS_res.path[i-1] ][ BFS_res.path[i] ].flow -= BFS_res.cf;
        }
        RG.get_residual(G);
        BFS_res = RG.BFS();
    }

    //cout << "last G:\n";
    //G.output();
    for(int i = 1;i <= G.v_num;++i)
    {
        total_flow += G.adj_matrix[G.source][i].flow
            - G.adj_matrix[i][G.source].flow;
    }
    return total_flow;
}


int main()
{
    // N: vertex num, M: edge num
    // S: source vertex,T: terminal vertex
    int N,M,S,T;
    cin >> N >> M >> S >> T;
    // init Graph G
    Network G = Network(N,M,S,T);
    int start,end,capacity;
    for(int i = 1; i <= M;++i)
    {
        cin >> start >> end >> capacity;
        G.append_edge(start,end,capacity);
    }

    // calculate max flow in G by using FF
    int max_flow = ford_fulkerson(G);
    cout << max_flow << endl;
    return 0;
}

/*
testcase:
3 3 1 3
1 2 2
2 3 1
1 3 3

6 9 1 4
1 2 16
1 5 13
2 3 12
3 4 20
3 5 9
5 2 4
5 6 14
6 3 7
6 4 4

4 5 1 4
1 2 1000
1 3 1000
2 4 1000
3 2 1
3 4 1000
*/
