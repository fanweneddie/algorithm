# kruskal algorithm for minimum spanning tree
# edge in an undirected weighted graph
class Edge:
    def __init__(self):
        self.start = 0
        self.end = 0
        self.weight = 0


# disjoint set
class UnionFind(object):

    def __init__(self,len):
        self.parent = [i for i in range(0,len+1)]

    def findSet(self,x):
        if x != self.parent[x]:
            self.parent[x] = self.findSet(self.parent[x])
        return self.parent[x]

    def connected(self,x,y):
        return self.findSet(x) == self.findSet(y)

    # just link x to y
    def union(self,x,y):
        x_root = self.findSet(x)
        y_root = self.findSet(y)
        self.parent[x_root] = y_root

# get weight to sort the list
def takeWeight(edge):
    return edge.weight

def main():
    # vertex num and edge num
    v_num,e_num = map(int,input().strip().split())
    # total cost
    total = 0
    # makeSet for each vertex v
    union_set = UnionFind(v_num)
    # edge list
    e_list = []
    # input edge and weight
    for i in range(0, e_num):
        temp = Edge()
        temp.start,temp.end,temp.weight = map(int,input().strip().split())
        e_list.append(temp)

    # sort the vertex list in an ascending order
    e_list.sort(key=takeWeight)
    
    # search for minimum spanning tree as Kruskal
    for i in range(0, e_num):
        u = e_list[i].start
        v = e_list[i].end
        if union_set.findSet(u) != union_set.findSet(v):
            total = total + e_list[i].weight
            union_set.union(u,v)
    # print the result of min total cost
    print(total)

if __name__ == '__main__':
    main()
