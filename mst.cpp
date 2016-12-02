//============================================================================
// Name        : MST.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <climits>
#include <iomanip>
using namespace std;

typedef int Vertice;


//-----------------------

int extraiMinimo(vector<float> key, vector<bool> mstSet, int ordem)
{
   // Initialize min value
   int min = INT_MAX, min_index;

   for (int v = 0; v < ordem; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;

   return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void printMST(vector<int> parent, vector<vector<float> > grafo, int ordem)
{
   printf("Edge   Weight\n");
   float acumulador = 0.0;
   for (int i = 1; i < ordem; i++){
      cout << parent[i] << " - " << i << " " << grafo[i][parent[i]] << endl;
   	  acumulador+=grafo[i][parent[i]];
   }
   cout << endl << "Total = " << acumulador << endl;
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(vector<vector<float> > grafo, int ordem, int raiz)
{
     vector<int> parent(ordem); // Array to store constructed MST
     vector<float> key(ordem);   // Key values used to pick minimum weight edge in cut
     vector <bool> mstSet(ordem);  // To represent set of vertices not yet included in MST

     // Initialize all keys as INFINITE
     for (int i = 0; i < ordem; i++)
        key[i] = INT_MAX, mstSet[i] = false;

     // Always include first 1st vertex in MST.
     key[0] = 0.0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = 0; // First node is always root of MST

     // The MST will have V vertices
     for (int count = 0; count < ordem-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = extraiMinimo(key, mstSet, ordem);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < ordem; v++)

           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (grafo[u][v] && mstSet[v] == false && grafo[u][v] < key[v])
             parent[v]  = u, key[v] = grafo[u][v];
     }

     // print the constructed MST
     printMST(parent, grafo, ordem);
}

//--------------------------------




template<class T>
class GrafoDeTransmissao {
private:
	vector<vector<T> > adj;
	int ordem, tam;

public:
	GrafoDeTransmissao(int);
	void iniciar(int);
	void preenche();
	void insere(Vertice, Vertice, float);
	void destroy();
	void mostra();

	vector<vector<T> > getAdj() {
		return adj;
	}
	void setAdj(vector<vector<T> > adj) {
		this->adj = adj;
	}
	int getOrdem() {
		return ordem;
	}
	void setOrdem(int n) {
		this->ordem = ordem;
	}
	int getTam() {
		return tam;
	}
	void setTam(int tam) {
		this->tam = tam;
	}
};

template<class T>
GrafoDeTransmissao<T>::GrafoDeTransmissao(int ordem) {
	iniciar(ordem);
	preenche();
}

template<class T>
void GrafoDeTransmissao<T>::iniciar(int ordem) {
	this->ordem = ordem;
	for(int i = 0; i < ordem; i++){
	    vector<T> aux(ordem);
	    adj.push_back(aux);
	}
}

template<class T>
void GrafoDeTransmissao<T>::preenche() {
	for (int i = 0; i < ordem; i++) {
	    for(int j = 0; j < ordem; j++){
		    adj[i][j] = 0.0;
		}
	}
}

template<class T>
void GrafoDeTransmissao<T>::mostra() {
    for (int i = 0; i < ordem; i++) {
	    for(int j = 0; j < ordem; j++){
	        cout.precision(2);
		    cout << fixed << adj[i][j] << "   ";
		}
		cout << endl;
	}
}

template<class T>
void GrafoDeTransmissao<T>::insere(Vertice v1, Vertice v2, float peso) {
	adj[v1][v2] = peso;
	adj[v2][v1] = peso;
}

int main() {
    int ordem, tamanho, v1, v2, raiz;
    float peso;
    cin >> ordem;
    cin >> tamanho;

    GrafoDeTransmissao<float> gt(ordem);

    gt.mostra();
    for (int i = 0; i < tamanho; ++i) {
    	cin >> v1;
    	cin >> v2;
    	cin >> peso;
    	gt.insere(v1,v2,peso);
	}

    cin >> raiz;

    gt.mostra();

    primMST(gt.getAdj(), ordem, raiz);

	return 0;
}
