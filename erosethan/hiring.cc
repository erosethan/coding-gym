#include <bits/stdc++.h>
using namespace std;

struct Fraccion {
  Fraccion operator*(long long k) const {
    return {numerador * k, denominador};
  }

  bool operator<(const Fraccion& otro) const {
    return numerador * otro.denominador < otro.numerador * denominador;
  }

  bool operator>(long long k) const {
    return numerador > k * denominador;
  }

  long long numerador;
  long long denominador;
};

struct Candidato {
  long long Calificacion() const {
    return proporcion.denominador;
  }

  bool operator<(const Candidato& otro) const {
    return proporcion < otro.proporcion;
  }

  int indice;
  Fraccion proporcion;
};

struct ComparaPorCalificacion {
  bool operator()(const Candidato& lhs, const Candidato& rhs) const {
    return lhs.Calificacion() < rhs.Calificacion();
  }
};

struct ConjuntoCandidatos {
  bool operator<(const ConjuntoCandidatos& otro) const {
    return (numero_trabajadores != otro.numero_trabajadores)
        // Si los dos conjuntos tienen un diferente numero de candidatos, consideramos
        // "menor", en otras palabras menos deseable, el que tenga menos candidatos.
        ? numero_trabajadores < otro.numero_trabajadores
        // Si tienen el mismo numero de candidatos, consideramos que este conjunto
        // es menos deseable si tiene un mayor costo de contratacion.
        : otro.costo_contratacion < costo_contratacion;
  }

  int indice{0};
  int numero_trabajadores{0};
  Fraccion costo_contratacion;
};

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  int n;
  long long w;
  cin >> n >> w;

  vector<Candidato> candidatos;
  for (int i = 0; i < n; ++i) {
    Fraccion proporcion;

    // El numerador es el salario minimo.
    cin >> proporcion.numerador;
    // El denominador es el nivel de calificacion.
    cin >> proporcion.denominador;

    candidatos.push_back({i + 1, proporcion});
  }

  // Ordenar por menor proporcion.
  sort(candidatos.begin(), candidatos.end());

  long long calificacion_total = 0;
  ConjuntoCandidatos mejor_conjunto;
  priority_queue<Candidato, vector<Candidato>, ComparaPorCalificacion> pq;

  for (int i = 0; i < n; ++i) {
    calificacion_total += candidatos[i].Calificacion();
    pq.push(candidatos[i]);

    // Mientras el costo de contratacion sea mayor que el presupuesto, eliminamos al
    // candidato con mayor calificacion, ya que infla el costo de contratacion.
    while (!pq.empty() && candidatos[i].proporcion * calificacion_total > w) {
      calificacion_total -= pq.top().Calificacion();
      pq.pop();
    }

    ConjuntoCandidatos actual;
    actual.indice = i + 1;
    actual.numero_trabajadores = pq.size();
    actual.costo_contratacion = candidatos[i].proporcion * calificacion_total;

    // Vease el operador de comparacion en `ConjuntoContratacion`.
    mejor_conjunto = max(actual, mejor_conjunto);
  }

  cout << mejor_conjunto.numero_trabajadores << "\n";

  // Para reconstruir la respuesta, volvemos a meter a los candidatos que habia
  // antes del indice donde determinamos era la mejor seleccion de candidatos.
  pq = priority_queue<Candidato, vector<Candidato>, ComparaPorCalificacion>();
  for (int i = 0; i < mejor_conjunto.indice; ++i) {
    pq.push(candidatos[i]);
  }

  // Sabemos cuantos candidatos eran el maximo, asi que eliminamos candidatos de
  // la cola de prioridad mientras sean mas que los maximos determinados.
  while (pq.size() > mejor_conjunto.numero_trabajadores) {
    pq.pop();
  }

  // Finalmente, imprimimos los candidatos que fueron seleccionados.
  while (!pq.empty()) {
    cout << pq.top().indice << "\n";
    pq.pop();
  }
  return 0;
}
