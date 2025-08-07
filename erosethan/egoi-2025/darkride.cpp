#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;

  int log_n = 0;
  while (1 << ++log_n < n) {}

  auto ScreamParity = []() {
    int screams;
    cin >> screams;
    return screams & 1;
  };

  int a;
  vector<bool> parity(log_n);

  for (int i = 0; i < log_n; ++i) {
    string query = "? ";
    for (int j = 0; j < n; ++j) query += (j & 1 << i) ? '1' : '0';
    cout << query << endl;

    if (ScreamParity()) {
      parity[i] = 1;
      a = 1 << i;
    }
  }

  for (int i = 0; i < log_n; ++i) {
    int s = a | 1 << i;

    string query = "? ";
    for (int j = 0; j < n; ++j) query += ((j & s) == s) ? '1' : '0';
    cout << query << endl;

    if (ScreamParity()) a = s;
  }

  int b = a;
  for (int i = 0; i < log_n; ++i) if (parity[i]) b ^= 1 << i;
  cout << "! " << a << ' ' << b << endl;
}
