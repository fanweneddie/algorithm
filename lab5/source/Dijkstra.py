from queue import PriorityQueue


class Edge(object):
    def __init__(self, v, w):
        self.dst = v
        self.weight = w


# vertex in a graph
class Vertex(object):
    def __init__(self, u):
        self.key = u
        self.adj_list = []


# vertex in dijkstra
class Vex(object):
    def __init__(self, u, dist):
        self.key = u
        self.dist = dist
    
    # self-defined comparator
    def __lt__(self, other):
        return self.dist < other.dist


# use adjList to represent a graph
class Graph(object):
    def __init__(self, v_num):
        self.vertex_list = [Vertex(i) for i in range(0, v_num + 1)]
        self.vertex_num = v_num

    # append an edge into the graph
    def add_edge(self, src, dst, weight):
        new_e = Edge(dst, weight)
        self.vertex_list[src].adj_list.append(new_e)

    # output the graph
    def output(self):
        for v in self.vertex_list:
            print(v.key)
            for e in v.adj_list:
                tu = (e.dst, e.weight)
                print(tu)


# Dijkstra shortest path algo: O(elgv)
def Dijkstra(graph, src, dst):
    # use a minimum priority queue
    INFINITY = (1 << 31) - 1
    pq = PriorityQueue()
    # init single source distance
    visit = [0]*(graph.vertex_num + 1)
    dist = [INFINITY]*(graph.vertex_num + 1)
    dist[src] = 0
    # start iteration 
    pq.put(Vex(src, dist[src]))
    while not pq.empty():
        vex = pq.get()

        if visit[vex.key] == 1:
            continue
        # marks that the key is visited
        visit[vex.key] = 1
        if vex.key == dst:
            break
        # relax the edges
        for e in graph.vertex_list[vex.key].adj_list:
            if dist[vex.key] + e.weight < dist[e.dst]:
                dist[e.dst] = dist[vex.key] + e.weight
                pq.put(Vex(e.dst, dist[e.dst]))
                
    # regard as INF
    if dist[dst] > 100000000:
        print(-1)
    else:
        print(dist[dst])
        

def main():
    # vertex num, edge num, source and destination
    v_num, e_num, src, dst = map(int, input().strip().split())
    # init Graph
    graph = Graph(v_num)
    # input edge and weight
    for i in range(0, e_num):
        start, end, weight = map(int, input().strip().split())
        graph.add_edge(start, end, weight)
    
    # graph.output()
    # search shortest path
    Dijkstra(graph, src, dst)

if __name__ == "__main__":
    main()
