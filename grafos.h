#ifndef GRAFOS_H
#define GRAFOS_H

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

class Grafos { // Nombre de clase corregido
private:
    int *adjMatrix;
    int nodes;
    vector< list<int> > adjList;

    void addEdgeAdjMatrix(int u, int v);
    void addEdgeAdjList(int u, int v);

    string printAdjListHelper();
    string printAdjMatHelper();
    
    void parse_graph_input(const string &input, vector<vector<int>> &edges); 
    
    bool contains(const list<int> &L, int v); 
    string print_visited(const list<int> &visited); 
    
    // Firmas DFS (vector<vector<int>>)
    string depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths);
    string print_path(const vector<vector<int>> &paths, int start, int goal);
    
    // Firmas BFS (vector<int>)
    string breadthHelper(int start, int goal, queue<int> &q, list<int> &visited, vector<int> &paths);
    string print_path(const vector<int> &paths, int start, int goal); 

public:
    Grafos(); // Nombre de constructor corregido
    ~Grafos(); // Nombre de destructor corregido
    
    void loadGraphMat(const string &input, int num_nodes, int num_cols); 
    void loadGraphList(const string &input, int num_nodes); 
    
    string printAdjList();
    string printAdjMat();
    string DFS(int, int);
    string BFS(int, int);
};

#endif
// -------------------------------------------------------------
// IMPLEMENTACIÓN
// -------------------------------------------------------------

// ------------------- CONSTRUCTORES / DESTRUCTORES -------------------

Grafos::Grafos() { // Nombre de constructor corregido
    adjMatrix = NULL;
    nodes = 0;
}

Grafos::~Grafos() { // Nombre de destructor corregido
    if (adjMatrix) delete[] adjMatrix;
}

// ------------------- UTILS -------------------

void Grafos::parse_graph_input(const string &input, vector<vector<int>> &edges) {
    stringstream ss(input);
    char trash;
    int u, v;

    while (ss >> trash >> u >> trash >> v >> trash) {
        edges.push_back({u, v}); 
    }
}

bool Grafos::contains(const list<int> &L, int v) {
    return find(L.begin(), L.end(), v) != L.end();
}

string Grafos::print_visited(const list<int> &visited) {
    stringstream ss;
    ss << "visited: ";
    list<int>::const_iterator it;
    for (it = visited.begin(); it != visited.end(); ++it) {
        ss << *it << " ";
    }
    return ss.str();
}

// ------------------- CARGA DE GRAFOS -------------------

void Grafos::addEdgeAdjList(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        adjList[u].push_back(v);
        adjList[u].sort();
        
        adjList[v].push_back(u);
        adjList[v].sort();
    }
}

void Grafos::loadGraphList(const string &input, int num_nodes) {
    nodes = num_nodes;
    adjList.clear();
    adjList.resize(nodes);

    vector<vector<int>> edges;
    parse_graph_input(input, edges);

    for (const auto& edge : edges) {
        addEdgeAdjList(edge[0], edge[1]);
    }
}

void Grafos::addEdgeAdjMatrix(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        adjMatrix[u * nodes + v] = 1;
        adjMatrix[v * nodes + u] = 1;
    }
}

void Grafos::loadGraphMat(const string &input, int num_nodes, int num_cols) {
    if (adjMatrix) delete[] adjMatrix;
    nodes = num_nodes;
    
    adjMatrix = new int[nodes * nodes];

    for (int i = 0; i < nodes * nodes; i++)
        adjMatrix[i] = 0;

    vector<vector<int>> edges;
    parse_graph_input(input, edges);

    for (const auto& edge : edges) {
        addEdgeAdjMatrix(edge[0], edge[1]);
    }
}

// ------------------- IMPRESIÓN -------------------

string Grafos::printAdjListHelper() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        aux << "vertex " << i << " : ";
        list<int>::iterator it;
        for (it = adjList[i].begin(); it != adjList[i].end(); ++it)
            aux << *it << " ";
    }
    return aux.str();
}

string Grafos::printAdjList() {
    return printAdjListHelper();
}

string Grafos::printAdjMatHelper() {
    stringstream aux;
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            aux << adjMatrix[i * nodes + j] << " ";
    return aux.str();
}

string Grafos::printAdjMat() {
    return printAdjMatHelper();
}

// ------------------- DFS (ADAPTADO) -------------------

string Grafos::DFS(int start, int goal) {
    stack<int> st;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1, -1)); 
    st.push(start);
    
    string visited_str = depthHelper(start, goal, st, visited, paths);
    
    visited_str += print_path(paths, start, goal);
    return visited_str; 
}

string Grafos::depthHelper(int current, int goal, stack<int> &st,
                          list<int> &visited,
                          vector<vector<int>> &paths) { 
    
    if(current == goal)
    {
        return print_visited(visited);
    } 
    
    if( st.empty())
    {
        return print_visited(visited); 
    } 
    
    current = st.top(); 
    st.pop();
    visited.push_back(current);

    for(list<int>::iterator it = adjList[current].begin(); it != adjList[current].end(); ++it){
        int neighbor = *it;
        
        if(!contains(visited, neighbor))
        {
            st.push(neighbor);
            paths[neighbor][0] = current; 
        }
        
        return depthHelper(current, goal, st, visited, paths);
    }
    
    return depthHelper(current, goal, st, visited, paths);
}

// ------------------- RECONSTRUCCIÓN DE CAMINO (DFS - vector<vector<int>>) -------------------

string Grafos::print_path(const vector<vector<int>> &paths, int start, int goal) {
    if (paths[goal][0] == -1 && goal != start) { 
        return "path: not found";
    }

    vector<int> reverse_path;
    int node = goal;
    
    while (node != -1) { 
        reverse_path.push_back(node);
        node = paths[node][0]; 
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

// ------------------- BFS -------------------

string Grafos::BFS(int start, int goal) {
    queue<int> q;
    list<int> visited;
    vector<int> paths(nodes, -1); 

    q.push(start);
    return breadthHelper(start, goal, q, visited, paths);
}

string Grafos::breadthHelper(int start, int goal, queue<int> &q,
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

// ------------------- RECONSTRUCCIÓN DE CAMINO (BFS - vector<int>) -------------------

string Grafos::print_path(const vector<int> &paths, int start, int goal) {
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