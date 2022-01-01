#include <iostream>
#include <vector>
#include <map>
using namespace std;
const int INFINITY = 1000000000;
// attribute of vex in dijkstra
vector<bool> visit;
vector<int> dist;
vector<int> pos;


class Edge
{
    public:
    int start;
    int end;
    int weight;

    Edge(int start, int end, int weight): 
        start(start),end(end),weight(weight){}
};

class Vertex
{
    public:
    int key;
    vector<Edge> adj_list;

    Vertex(int key_in): key(key_in) {}
    Vertex(){key = 0;}
};

class Graph
{
    public:
    int v_num;
    int e_num;
    map<int,Vertex> vertex_list;
    
    Graph(int v_num_in,int e_num_in): 
        v_num(v_num_in), e_num(e_num_in) {}

    // add an edge into the graph
    void append_edge(Edge edge)
    {
        int start_vex = edge.start;
        // vex unfound, insert it
        if(vertex_list.count(start_vex) == 0)
        {
            Vertex new_vex = Vertex(start_vex);
            vertex_list.insert
                (map<int, Vertex>::value_type(start_vex,new_vex));
        }
        vertex_list[start_vex].adj_list.push_back(edge);
    }

    void output()
    {
        map<int, Vertex>::iterator iter;
        for (iter = vertex_list.begin();
            iter != vertex_list.end();iter++)
        {
            int len = iter->second.adj_list.size();
            for(int i = 0;i < len;++i)
            {
                Edge edge = iter->second.adj_list[i];
                cout << edge.start << "--" << edge.end 
                    << " " << edge.weight << endl;
            }
        }
    }
};



// a min heap
class MinHeap
{
    private:
    // in a heap: the first index is 1(not 0)
    int arr_len;
    // the length of the heap
    int heap_len;
    // vex array
    vector<int> arr;
    
    public:
    MinHeap()
    {
        arr_len = 0;
        heap_len = 0;
    }

    // some setters and getters
    int get_arr_len()
    {
        return arr_len;
    }

    void set_arr_len(int arr_len)
    {
        this->arr_len = arr_len;
    }

    int get_heap_len()
    {
        return heap_len;
    }

    bool is_empty()
    {
        return heap_len == 0;
    }

    // return parent node's index of node_i
    int get_parent(int node_i)
    {
        return node_i/2;
    }

    // return left node's index of node_i
    int get_left_child(int node_i)
    {
        return node_i*2;
    }

    // return right node's index of node_i
    int get_right_child(int node_i)
    {
        return node_i * 2 + 1;
    }

    // maintain the struture of min heap
    // @param node_i: the possible node that 
    // - might damage the structure of min heap 
    // assume that node_i's left_child and right_child
    // are both the root of a min heap
    void min_heapify(int node_i)
    {
        int l_child = get_left_child(node_i);
        int r_child = get_right_child(node_i);
        // the index of max data 
        // - among arr[node_i],arr[l_child] and arr[r_child]
        int min_index = node_i;
        // check whether l_child is in heap 
        // - and data in l_child's rest is smaller
        if( l_child <= heap_len && 
            dist[arr[l_child]] < dist[arr[min_index]] )
            min_index = l_child;
        // check whether r_child is in heap
        // - and data in r_child's rest is smaller
        if( r_child <= heap_len && 
            dist[arr[r_child]] < dist[arr[min_index]] )
            min_index = r_child;
        // if node_i's rest is not the smallest
        // - exchange arr[node_i] with arr[min_index]
        // - and continue min_heapify arr[min_index] 
        if(min_index != node_i)
        {
            // update position
            pos[arr[min_index]] = node_i;
            pos[arr[node_i]] = min_index;
            // swap
            int temp = arr[min_index];
            arr[min_index] = arr[node_i];
            arr[node_i] = temp;
            min_heapify(min_index);
        }
    }

    // get and pop out the min element in the heap
    int extract_min()
    {
        if(heap_len < 1)
        {
            cout << "error: heap underflow\n";
        }
        // min is the minimal element
        int min = arr[1];
        // maintain the minheap structure
        arr[1] = arr[heap_len];
        // update pos
        pos[arr[heap_len]] = 1;
        heap_len--;
        min_heapify(1);
        return min;
    }

    // decrease the rest value of arr[node_i]
    void decrease_key(int node_i)
    {
        // maintain the structure of minheap
        while( node_i > 1 && 
            dist[arr[get_parent(node_i)]] 
                > dist[arr[node_i]] )
        {
            // update pos
            pos[arr[get_parent(node_i)]] = node_i;
            pos[arr[node_i]] = get_parent(node_i);
            // swap
            int temp = arr[get_parent(node_i)];
            arr[get_parent(node_i)] = arr[node_i];
            arr[node_i] = temp;
            node_i = get_parent(node_i);
        }
    }

    // insert a new task into the heap
    void insert_key(int new_vex)
    {
        heap_len++;
        // allocate space for arr
        if(heap_len >= arr.size())
            arr.resize(2*heap_len);
        arr[heap_len] = new_vex;
        pos[new_vex] = heap_len;
        decrease_key(heap_len);
    }
};

void Dijkstra(Graph G,int src,int dst)
{
    // marks whether each vertex has been visited
    visit.resize(G.v_num + 1);
    for(int i = 1;i <= G.v_num;++i)
        visit[i] = false;
    // marks the distance between src and each vex
    dist.resize(G.v_num + 1);
    for(int i = 1;i <= G.v_num;++i)
        dist[i] = INFINITY;
    pos.resize(G.v_num + 1);
    // init src's distance
    dist[src] = 0;

    // minimum priority queue
    MinHeap heap;
    for(int i = 1; i <= G.v_num;++i)
        heap.insert_key(i);

    while( !heap.is_empty() )
    {
        int vex = heap.extract_min();
        if(vex == dst)
            break;
        // relax
        int len = G.vertex_list[vex].adj_list.size();
        for(int i = 0;i < len;++i)
        {
            int u = vex;
            int v = G.vertex_list[vex].adj_list[i].end;
            int w = G.vertex_list[vex].adj_list[i].weight;
            if(dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                heap.decrease_key(pos[v]);
            }
        }
    }

    if(dist[dst] > 100000000)
        cout << -1 << endl;
    else
        cout << dist[dst] << endl;
}

int main()
{
    //  vertex num, edge num, source and destination
    int v_num,e_num,src,dst;
    cin >> v_num >> e_num >> src >> dst;
    // init graph G
    Graph G = Graph(v_num,e_num);
    for(int i = 0; i < e_num;++i)
    {
        int start,end,weight;
        cin >> start >> end >> weight;
        Edge edge = Edge(start,end,weight);
        G.append_edge(edge);
    }
    Dijkstra(G,src,dst);
    return 0;
}
