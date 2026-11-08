#include <bits/stdc++.h>
using namespace std;
int main() {
  string f;
  auto ok = [&] {
    if (!f.contains(".txt"))
      f += ".txt";
    return filesystem::exists(f) ||
           (cerr << "File non trovato: '" << f << "'\n", false);
  };
  do
    cout << "Inserisci nome file da ordinare: ";
  while (cin >> f && !ok());
  ifstream in(f);
  vector<array<string, 3>> tv;
  for (string l; getline(in, l);) {
    stringstream s(l);
    array<string, 3> t;
    for (auto &x : t)
      getline(s, x, ',');
    tv.push_back(t);
  }
  vector<int> sz;
  cout << "Inserisci dimensione (0 per fermarsi): \n";
  for (int i; cout << "Inserisci dimensione: ", cin >> i && i;)
    if (ranges::find(sz, i) == sz.end())
      sz.push_back(i);
  if (sz.empty())
    return cerr << "Nessun dato e' stato inserito, chiusura del programma.\n",
           1;
  auto size = [](const string &m) {
    for (size_t p : {0, 2})
      if (m.size() > p && isdigit(m[p]))
        return stoi(m.substr(p, 2));
    return -1;
  };
  ofstream o(f.substr(0, f.size() - 4) + "_ordinato.txt");
  for (int s : sz) {
    o << "\t\t\t\t\t" << s << " POLLICI\n";
    bool hit = 0;
    for (auto &[e, b, m] : tv)
      if (size(m) == s)
        o << "Marca: " << (ranges::transform(b, b.begin(), ::toupper), b)
          << ", EAN: " << e << ", Modello: " << m << "\n",
            hit = 1;
    o << (hit ? "\n" : "\t\t\t**NESSUN MODELLO TROVATO**\n\n");
  }
  cout << "File di testo ordinato creato.\n";
}
