#include <bits/stdc++.h>
using namespace std;

// Una posicion en el mapa de dos dimensiones.
struct Posicion {
  // Este operador nos permite efectuar movimientos en el mapa.
  Posicion operator+(const Posicion& otro) const {
    return {fila + otro.fila, columna + otro.columna};
  }

  int fila;
  int columna;
};

const int kInf = 1e9;

// Los movimientos permitidos en el mapa:
//   - Abajo, arriba, derecha, e izquierda, respectivamente.
const vector<Posicion> kMovimientos = {{ 0,  1},
                                       { 0, -1},
                                       { 1,  0},
                                       {-1,  0}};

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  int n, s;
  cin >> n >> s;

  Posicion inicio;
  vector<string> mapa(n);

  vector<vector<int>> tiempo_abejas(n, vector<int>(n, kInf));
  queue<Posicion> abejas;

  for (int i = 0; i < n; ++i) {
    // Leemos una fila entera del mapa.
    cin >> mapa[i];

    // Buscamos la posicion inicial de Mecho.
    for (int j = 0; j < n; ++j) {
      switch (mapa[i][j]) {
        case 'H':
          tiempo_abejas[i][j] = 0;
          abejas.push({i, j});
          break;
        case 'M':
          inicio = {i, j};
      }
    }
  }

  // BFS para saber cuando llegan las abejas a cada celda.
  while (!abejas.empty()) {
    Posicion actual = abejas.front();
    abejas.pop();

    for (const Posicion& movimiento : kMovimientos) {
      Posicion siguiente = actual + movimiento;

      // Verificamos que la siguiente celda esta dentro del mapa.
      if (siguiente.fila >= 0 && siguiente.fila < n &&
          siguiente.columna >= 0 && siguiente.columna < n &&
          // Despues, que no hay un arbol o la casa de Mecho.
          mapa[siguiente.fila][siguiente.columna] != 'D' &&
          mapa[siguiente.fila][siguiente.columna] != 'T' &&
          // Finalmente, que la siguiente celda no ha sido visitada.
          tiempo_abejas[siguiente.fila][siguiente.columna] == kInf) {
        tiempo_abejas[siguiente.fila][siguiente.columna] =
            tiempo_abejas[actual.fila][actual.columna] + 1;
        abejas.push(siguiente);
      }
    }
  }

  // Busqueda binaria para saber cuanto tiempo podemos comer miel.
  // Usamos el tiempo que se tarden las abejas en llegar a la posicion inicial
  // de Mecho como limite superior, ya que ni siquiera podra moverse.
  int l = 0, r = tiempo_abejas[inicio.fila][inicio.columna];
  while (l < r) {
    // El tiempo de espera que vamos a probar.
    int m = (l + r) >> 1;
    
    // BFS para saber si podemos llegar a la salida esperando m minutos.
    vector<vector<int>> tiempo_mecho(n, vector<int>(n, kInf));
    tiempo_mecho[inicio.fila][inicio.columna] = 0;
    queue<Posicion> q;
    q.push(inicio);

    bool llego_a_casa = false;
    while (!q.empty()) {
      Posicion actual = q.front();
      q.pop();

      if (mapa[actual.fila][actual.columna] == 'D') {
        llego_a_casa = true;
        break;
      }

      for (const Posicion& movimiento : kMovimientos) {
        Posicion siguiente = actual + movimiento;

        // Verificamos que la siguiente celda esta dentro del mapa.
        if (siguiente.fila >= 0 && siguiente.fila < n &&
            siguiente.columna >= 0 && siguiente.columna < n &&
            // Despues, que no hay un arbol.
            mapa[siguiente.fila][siguiente.columna] != 'T' &&
            // Despues, que las abejas no alcancen a Mecho.
            (tiempo_abejas[siguiente.fila][siguiente.columna] >
             (tiempo_mecho[actual.fila][actual.columna] + 1) / s + m) &&
            // Finalmente, que la siguiente celda no ha sido visitada.
            tiempo_mecho[siguiente.fila][siguiente.columna] == kInf) {
          tiempo_mecho[siguiente.fila][siguiente.columna] =
              tiempo_mecho[actual.fila][actual.columna] + 1;
          q.push(siguiente);
        }
      }
    }

    if (llego_a_casa) {
      l = m + 1;
    } else {
      r = m;
    }
  }

  // Obtuvimos el primer minuto que Mecho NO puede llegar a casa.
  // Nota que, convenientemente, si nunca puede llegar, imprime "-1".
  cout << l - 1 << "\n";
  return 0;
}
