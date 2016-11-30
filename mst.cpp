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
#include <climits>
#include <iomanip>
using namespace std;

typedef int Vertice;

template<class T>
class Pacientes {
private:
	Vertice valor;
	Vertice predecessor;
	vector<Vertice> adjacente;
	vector<float> peso;

public:
	void bolha();

	bool estaOrdenado();

	Pacientes() {
	}
	;

	Pacientes(Vertice valor) :
		valor(valor) {
	}

	~Pacientes() {
		adjacente.~vector();
		peso.~vector();
	}

	Vertice getVertice() {
		return valor;
	}

	void setVertice(Vertice valor) {
		this->valor = valor;
	}

	Vertice getPredecessor() {
		return predecessor;
	}

	void setPredecessor(Vertice predecessor) {
		this->predecessor = predecessor;
	}

	vector<T> getAdjacente() {
		return adjacente;
	}

	void setAdjacente(T v) {
		this->adjacente.push_back(v);
	}

	vector<float> getPeso() {
		return peso;
	}

	void setPeso(T p) {
		this->peso.push_back(p);
	}

};

template<class T>
bool Pacientes<T>::estaOrdenado() {
	bool ordenado = true;
	for (size_t i = 0; i < adjacente.size() - 1; ++i) {
		if (adjacente[i] >= adjacente[i + 1]) {
			ordenado = false;
			break;
		}
	}
	return ordenado;
}

template<class T>
void Pacientes<T>::bolha() {
	for (int i = adjacente.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (adjacente[j] > adjacente[j + 1]) {
				Vertice aux = adjacente[j];
				adjacente[j] = adjacente[j + 1];
				adjacente[j + 1] = aux;
				float aux2 = peso[j];
				peso[j] = peso[j + 1];
				peso[j + 1] = aux2;
			}
		}
	}
}

template<class T>
class GrafoDeTransmissao {
private:
	Pacientes<T> *adj;
	int ordem, tam;
	float soma;

public:
	GrafoDeTransmissao(int);
	void iniciar(int);
	void preenche();
	void insere(Vertice, Vertice, float);
	void destroy();

	~GrafoDeTransmissao() {
		delete adj;
		soma = 0.0;
	}

	Pacientes<T>* getAdj() {
		return adj;
	}
	void setAdj(Pacientes<T>* adj) {
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
	float getAcum() {
		return soma;
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
	adj = new Pacientes<T> [ordem + 1];
}

template<class T>
void GrafoDeTransmissao<T>::preenche() {
	for (int i = 1; i <= ordem; i++) {
		Pacientes<int> p(i);
		adj[i] = p;
	}
}

template<class T>
void GrafoDeTransmissao<T>::insere(Vertice v1, Vertice v2, float peso) {
	adj[v1].setAdjacente(v2);
	adj[v1].setPeso(peso);
	adj[v2].setAdjacente(v1);
	adj[v2].setPeso(peso);
}

class Processamento {

public:
	Processamento() {
	}
	;

	int Peso();
};



int Processamento::Peso() {
	int pacientes, setas, v1, v2;
	float peso, peso_mst;

	cin >> pacientes;
	cin >> setas;

	GrafoDeTransmissao<int> gt(pacientes);

	for (int i = 0; i < setas; ++i) {
		cin >> v1;
		cin >> v2;
		gt.insere(v1, v2, peso);
	}

	return peso_mst;
}

int main() {

	return 0;
}
