// ID 205925290
// ID 207041443

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

#define V 1000//num of vertex
#define Num_graph 500//num of graphs
#define Thresholed1  0.0069//Thresholed1 = Thresholed3 = (ln(V)/V) = 0.0069
#define Thresholed2  0.1175//Thresholed2 = root(2*ln(V)/V) = 0.1175

class Graph* build_random_graph(double p);
void destroy_graph(Graph** graph);
bool Is_Isolated(Graph** graph);
bool connectivity(Graph** graph);
int diameter(Graph** graph);
void simulation1();
void simulation2();

class Graph {
public:
	Graph(double p) {//graph operator
		this->p = p;
		this->adj = new vector<int>[V];
	}
	~Graph() {//graph distractor
		delete[] adj;
		adj = NULL;
	}
	void addEdge(int u, int v) {//creatinr thr eage bitween vertex u&v -> undirected graph
		double num = ((double)(rand()) / RAND_MAX);//determination by a random number if the egde exists or not
		if (num > p) {//if the random number is bigger from the propability the edge won't exists
			return;
		}
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	bool is_empty(int v) {
		if (adj[v].empty()) {//check if the vertex is isolated by empty() function - check if the vector container is empty
			return 1;//the graph has at least 1 isolated vertex
		}
		return 0;//the graph has no isolated vertex
	}
	int BFS(int u)//runing with BFS alogorithm from a vertex in the graph
	{
		int diameter = 0;
		queue<int> queue;
		bool visited[V] = { 0 };//a bool array to save true if the vertex has been visited
		int diam[V] = { 0 };// array to count the diameter from the vertex u to all the other
		queue.push(u);//pushing u from the queue
		visited[u] = true;//marking u as visited
		while (!queue.empty()) {//while the queue is not empty we will run on the vertex
			int curr_node = queue.front();//taking the first vertex in the queue = curr_node
			queue.pop();//removing the next element > curr_node
			//enqueue all adjacent of curr_node and mark them visited 
			for (auto i = adj[curr_node].begin(); i != adj[curr_node].end(); i++) {//runing on every vertex connected to curr_node with an edge87
				if (!visited[*i]) {//if a vertex is not mark as visited 
					queue.push(*i);//pushing the vertex from the queue
					visited[*i] = true;//marking the vertex as visited
					diam[*i] = diam[curr_node] + 1;//counting the diameter
					diameter = max(diameter, diam[*i]);//the max number between the variables is saved in diameter
				}
			}
		}
		return diameter;//returning the max diameter of the graph
	}
private:
	double p;//propability of the graph edges 
	vector<int>* adj;//vertex as vector called adj
};

void main()
{
	time_t t;
	srand((unsigned)time(0));
	simulation1();
	simulation2();
}

class Graph* build_random_graph(double p) {//biulding a random graph
	int i, j;
	class Graph* graph = new Graph(p);
	for (i = 0; i < V - 1; i++) {
		for (j = i + 1; j < V; j++) {
			graph->addEdge(i, j);
		}
	}
	return graph;
}

bool Is_Isolated(Graph** graph) {
	for (int v = 0; v < V; ++v)//for each head/vertex
	{
		if ((*graph)->is_empty(v)) {//check if the vertex is isolated by empty() function - check if the vector container is empty
			return 1;//the graph has at least 1 isolated vertex
		}
	}
	return 0;//if the vector is not empty the graph has no isolated vertex
}

bool connectivity(Graph** graph) {
	for (int v = 0; v < V; ++v)//for each head/vertex
	{
		if ((*graph)->is_empty(v)) {
			return 0;//the graph is not connective
		}
	}
	if ((*graph)->BFS(0) == 0) {
		return 0; //the graph is not connective
	}
	else {
		return 1;//the graph is connective
	}
}

int diameter(Graph** graph) {
	int diam = 0, max_diam = 0;
	if (!connectivity(graph)) {//check if the vertex is isolated by empty() function - check if the vector container is empty
		return 0;//the diam of the graph is infinity, we will mark it as 0
	}
	else {
		for (int i = 0; i < V; i++) {//running BFS from each vertex to find the max diam
			diam = (*graph)->BFS(i);
			max_diam = max(max_diam, diam);
		}
		return max_diam;//the diam of the graph
	}
}

//simulation for connectivity and isolation
void simulation1() {
	ofstream file_connective;
	file_connective.open("connective_test.csv", fstream::app);
	ofstream file_isolated;
	file_isolated.open("isolated_test.csv", fstream::app);
	//Thresholed1 = Thresholed3 = 0.0069
	//propabillity array around the Thresholed1 value - 5 smaller and 5 bigger
	double p[10] = { 0.00685,0.00686,0.00687,0.00688,0.00689,0.00691,0.00692,0.00693,0.00694,0.00695 };
	double connective[10] = { 0 };
	double isolated[10] = { 0 };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < Num_graph; j++) {
			Graph* graph = build_random_graph(p[i]);//biulding a random graph
			if (Is_Isolated(&graph) == true) {
				isolated[i]++;
			}
			if (connectivity(&graph) == true) {
				connective[i]++;
			}
			graph->~Graph();
			destroy_graph(&graph);
		}
		connective[i] = connective[i] / Num_graph;
		file_connective << p[i] << "," << connective[i] << endl;
		isolated[i] = isolated[i] / Num_graph;
		file_isolated << p[i] << "," << isolated[i] << endl;
	}
	file_connective.close();
	file_isolated.close();
}

//simulation for diameter
void simulation2() {
	ofstream file_diameter;
	file_diameter.open("diameter_test.csv", fstream::app);
	//Thresholed2 = 0.1175
	int diam = 0;//diameter of the graph
	//propabillity array around the Thresholed1 value - 5 smaller and 5 bigger
	double p[10] = { 0.112,0.113,0.114,0.115,0.116,0.118,0.119,0.12,0.121,0.122 };
	double p_diam[10] = { 0 };//array of results for the propability around the Thresholed1 
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < Num_graph; j++) {
			Graph* graph = build_random_graph(p[i]);//biulding a random graph
			diam = diameter(&graph);//therefor the diameter=infinity
			if (diam <= 2)
			{
				p_diam[i]++;
			}
			graph->~Graph();
			destroy_graph(&graph);
		}
		p_diam[i] = p_diam[i] / Num_graph;
		file_diameter << p[i] << "," << p_diam[i] << endl;
	}
	file_diameter.close();
}

void destroy_graph(Graph** graph) {
	delete (*graph);
	(*graph) = NULL;
}