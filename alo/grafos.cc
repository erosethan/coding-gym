#include <bits/stdc++.h>
using namespace std;

struct Arista {
  bool operator<(const Arista& otro) const {
    return costo > otro.costo;
  }

  int nodo, costo;
}

struct Grafo {
  Grafo(int n) {
    tamano = n;
    representante.resize(n);
    for (int i = 0; i < n; ++i) {
      representante[i] = i;
    }
    tamano_componente.resize(n, 1);
    lista_adyacencia.resize(n);
  }

  int Find(int u) {
    if (representante[u] == u) return u;
    return representante[u] = Find(representante[u]);
  }

  int Union(int u, int v) {
    int representante_u = Find(u);
    int representante_v = Find(v);

    if (representante_u != representante_v) {
      if (tamano_componente[representante_u] < tamano_componente[representante_v]) {
        representante[representante_u] = representante_v;
        tamano_componente[representante_v] += tamano_componente[representante_u];
      } else {
        representante[representante_v] = representante_u;
        tamano_componente[representante_u] += tamano_componente[representante_v];
      }
    }
  }

  void AgregarArista(int u, int v, int costo) {
    if (representante[u] != representante[v]){
      lista_adyacencia[u].push_back({v, costo});
      lista_adyacencia[v].push_back({u, costo});
    }
  }
  
  int tamano;
  vector<int> representante;
  vector<int> tamanos_componente;
  vector<vector<Arista>> lista_adyacencia;
};

int main() {
  int n, m;
  cin >> n >> m;

	Grafo grafo(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    grafo.AgregarArista(u - 1, v - 1);
  }
}