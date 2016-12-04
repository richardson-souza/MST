#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <climits>
#include <iomanip>
using namespace std;

typedef int Vertice;
const float INFINITO = LONG_MAX;

template<class T>
class MST{
public:
	MST(){
	};

	int extraiMinimo(vector<float>, vector<int>, int);
	float pesoMST(vector<int>, vector<vector<float> >, int);
	float prim(vector<vector<float> >, int, int);
};

template<class T>
int MST<T>::extraiMinimo(vector<float> chaves, vector<int> vertices, int ordem)
{
   float valor_minimo = LONG_MAX;
   int indice_minimo;

   for (int i = 0; i < ordem; i++){
     if (vertices[i] == 0 && chaves[i] < valor_minimo){
         valor_minimo = chaves[i];
         indice_minimo = i;
     }
   }
   return indice_minimo;
}

template<class T>
float MST<T>::pesoMST(vector<int> arvore, vector<vector<float> > grafo, int ordem)
{
   float peso = 0.0;
   int indice = 0;
   for (int i = 0; i < ordem; i++){
	   indice = arvore[i];
	   if(indice != -1){
		   peso+=grafo[i][indice];
	   }
   }

   return peso;
}

template<class T>
float MST<T>::prim(vector<vector<float> > grafo, int ordem, int raiz)
{
     vector<int> arvore(ordem);
     vector<float> chaves(ordem);
     vector<int> vertices(ordem);
     float peso = 0.0;

     for (int i = 0; i < ordem; i++)
     {
        chaves[i] = INFINITO;
        vertices[i] = 0;
     }

     chaves[raiz] = 0.0;
     arvore[raiz] = -1;

     for (int j = 0; j < ordem; j++)
     {
        int u = extraiMinimo(chaves, vertices, ordem);
        vertices[u] = 1;

        for (int k = 0; k < ordem; k++)
        {
          if (grafo[u][k] && vertices[k] == 0 && grafo[u][k] < chaves[k]){
             arvore[k] = u;
             chaves[k] = grafo[u][k];
          }
        }
     }

     peso = pesoMST(arvore, grafo, ordem);

     return peso;
}

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
void GrafoDeTransmissao<T>::insere(Vertice v1, Vertice v2, float peso) {
	adj[v1][v2] = peso;
	adj[v2][v1] = peso;
}

class Processamento{
public:
	int ordem, tamanho, v1, v2, raiz;
	float peso, resultado;

	Processamento(){
	};

	void Resultado(){
		cin >> ordem;
		cin >> tamanho;

		GrafoDeTransmissao<float> grafotransmissao(ordem);
		MST<float> mst;

		for (int i = 0; i < tamanho; ++i) {
	    	cin >> v1;
	    	cin >> v2;
	    	cin >> peso;
	    	grafotransmissao.insere(v1,v2,peso);
		}

		cin >> raiz;

		resultado = mst.prim(grafotransmissao.getAdj(), ordem, raiz);

		cout.precision(2);
		cout << fixed << resultado;
	}
};

int main() {

	Processamento processamento;

	processamento.Resultado();

	return 0;
}
