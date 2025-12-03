#ifndef graph_H
#define graph_H

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <sstream>
#include <algorithm> 
#include <string>
#include <cstdlib> 

using namespace std;

class Graph { 
private:
    int *adjMatrix;
    int nodes;
    vector< list<int> > adjList;

    void addEdgeAdjMatrix(int u, int v);
    void addEdgeAdjList(int u, int v);

    string printAdjListHelper();
    string printAdjMatHelper();
    
    // Espacio añadido: vector<vector<int> >
    void parse_graph_input(const string &input, vector<vector<int> > &edges); 
    
    bool contains(const list<int> &L, int v); 
    string print_visited(const list<int> &visited); 
    
    string depthHelper(int start, int goal, stack<int> &st, list<int> &visited, vector<int> &paths);
    
    string breadthHelper(int start, int goal, queue<int> &q, list<int> &visited, vector<int> &paths);
    string print_path(const vector<int> &paths, int start, int goal); 

public:
    Graph(); 
    ~Graph(); 
    
    void loadGraphMat(const string &input, int num_nodes, int num_cols); 
    void loadGraphList(const string &input, int num_nodes); 
    
    string printAdjList();
    string printAdjMat();
    string DFS(int, int);
    string BFS(int, int);
};

#endif

Graph::Graph() { 
    adjMatrix = NULL;
    nodes = 0;
}

Graph::~Graph() { 
    if (adjMatrix) delete[] adjMatrix;
}

void Graph::parse_graph_input(const string &input, vector<vector<int> > &edges) {
    stringstream ss(input);
    char trash;
    int u, v;

    while (ss >> trash >> u >> trash >> v >> trash) {
        vector<int> edge;
        edge.push_back(u);
        edge.push_back(v);
        edges.push_back(edge); 
    }
}

bool Graph::contains(const list<int> &L, int v) {
    return find(L.begin(), L.end(), v) != L.end();
}

string Graph::print_visited(const list<int> &visited) {
    stringstream ss;
    ss << "visited: ";
    list<int>::const_iterator it;
    for (it = visited.begin(); it != visited.end(); ++it) {
        ss << *it << " ";
    }
    return ss.str();
}

void Graph::addEdgeAdjList(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        adjList[u].push_back(v);
        adjList[u].sort();
        
        adjList[v].push_back(u);
        adjList[v].sort();
    }
}

void Graph::loadGraphList(const string &input, int num_nodes) {
    nodes = num_nodes;
    adjList.clear();
    adjList.resize(nodes);

    vector<vector<int> > edges;
    parse_graph_input(input, edges);

    for (size_t i = 0; i < edges.size(); ++i) {
        addEdgeAdjList(edges[i][0], edges[i][1]);
    }
}

void Graph::addEdgeAdjMatrix(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        adjMatrix[u * nodes + v] = 1;
        adjMatrix[v * nodes + u] = 1;
    }
}

void Graph::loadGraphMat(const string &input, int num_nodes, int num_cols) {
    if (adjMatrix) delete[] adjMatrix;
    nodes = num_nodes;
    
    adjMatrix = new int[nodes * nodes];

    for (int i = 0; i < nodes * nodes; i++)
        adjMatrix[i] = 0;

    vector<vector<int> > edges;
    parse_graph_input(input, edges);

    for (size_t i = 0; i < edges.size(); ++i) {
        addEdgeAdjMatrix(edges[i][0], edges[i][1]);
    }
}

string Graph::printAdjListHelper() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        aux << "vertex " << i << " : ";
        list<int>::iterator it;
        for (it = adjList[i].begin(); it != adjList[i].end(); ++it)
            aux << *it << " ";
    }
    return aux.str();
}

string Graph::printAdjList() {
    return printAdjListHelper();
}

string Graph::printAdjMatHelper() {
    stringstream aux;
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            aux << adjMatrix[i * nodes + j] << " ";
    return aux.str();
}

string Graph::printAdjMat() {
    return printAdjMatHelper();
}

string Graph::print_path(const vector<int> &paths, int start, int goal) {
    if (paths[goal] == -1 && goal != start) {
        return "path: not found";
    }

    vector<int> reverse_path;
    int node = goal;
    
    while (node != -1) {
        reverse_path.push_back(node);
        node = paths[node];
    }
    
    if (reverse_path.empty() || reverse_path.back() != start) {
        return "path: not found"; 
    }

    stringstream ss;
    ss << "path: ";
    for (int i = reverse_path.size() - 1; i >= 0; i--) {
        ss << reverse_path[i] << (i != 0 ? " " : "");
    }
    return ss.str();
}

string Graph::DFS(int start, int goal) {
    stack<int> st;
    list<int> visited;
    vector<int> paths(nodes, -1); 
    
    st.push(start);
    
    return depthHelper(start, goal, st, visited, paths);
}

string Graph::depthHelper(int start, int goal, stack<int> &st,
                          list<int> &visited,
                          vector<int> &paths) { 
    
    vector<bool> seen(nodes, false); 

    while (!st.empty()) {

        int node = st.top();
        st.pop();
        if (!seen[node]) {
            seen[node] = true;
            visited.push_back(node);
        }

        if (node == goal) {
            break;
        }
        for (int v : adjList[node]) {
            if (!seen[v]) {
                paths[v] = node;

                st.push(v); 
            }
        }
    }

    stringstream ss;
    ss << print_visited(visited);

    if (contains(visited, goal)) {
        ss << print_path(paths, start, goal);
    } else {
        ss << "path: not found";
    }
    
    return ss.str();
}

string Graph::BFS(int start, int goal) {
    queue<int> q;
    list<int> visited;
    vector<int> paths(nodes, -1); 

    q.push(start);
    return breadthHelper(start, goal, q, visited, paths);
}

string Graph::breadthHelper(int start, int goal, queue<int> &q,
                            list<int> &visited,
                            vector<int> &paths) {

    vector<bool> seen(nodes, false);
    seen[start] = true;
    
    while (!q.empty()) {
        int node = q.front(); q.pop();
        visited.push_back(node);

        if (node == goal) {
            break;
        }

        list<int>::iterator it;
        for (it = adjList[node].begin(); it != adjList[node].end(); ++it) {
            int v = *it;
            if (!seen[v]) {
                q.push(v);
                seen[v] = true;
                paths[v] = node;
            }
        }
    }

    stringstream ss;
    ss << print_visited(visited);
    
    if (contains(visited, goal)) {
        ss << print_path(paths, start, goal);
    } else {
        ss << "path: not found";
    }
    
    return ss.str();
}

