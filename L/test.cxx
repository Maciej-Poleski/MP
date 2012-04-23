#include <iostream>
#include <fstream>
#include <cstdint>
#include <limits>

using namespace std;

uint32_t *edgeLength;
uint32_t *edgeS;
bool *edgeVisited;
uint32_t n;

struct Edge {
    uint32_t a, b;
};

Edge *E;

int main(int argc, char **argv)
{
    if(argc != 3) {
        std::cerr << "Potrzeba dokładnie dwóch argumentów: <wejście> <wyjście>\n";
        std::abort();
    }
    ifstream in(argv[1]);
    ifstream out(argv[2]);
    uint32_t z;
    in >> z;
    while(z--) {
        in >> n;
        edgeLength = new uint32_t[n * 2 + 1];
        edgeS = new uint32_t[n * 2 + 1];
        edgeVisited = new bool[n * 2 + 1];
        E = new Edge[2 * n + 1];
        for(size_t i = 1; i <= 2 * n; ++i) {
            edgeVisited[i] = false;
        }
        for(size_t i = 1; i <= 2 * n; ++i) {
            uint32_t a, b, l, s;
            in >> a >> b >> l >> s;
            edgeLength[i] = l;
            edgeS[i] = s;
            E[i] = {a, b};
        }
        string ans;
        out >> ans;
        if(ans == "TAK") {
            uint32_t c;
            out >> c;
            if(c != 2 * n) {
                cout << "Cykl jest nieprawidłowej długości, oczekiwano " << 2 * n << " a otrzymano " << c << '\n';
            }
            int32_t state = 0;
            uint32_t e;
            uint32_t first;
            out >> e;
            first = e;
            uint32_t s;
            out >> s;
            if((s != E[e].a) && (s != E[e].b)) {
                cout << "Krawędź " << e << " nie prowadzi do wierzchołka " << s << '\n';
            }
            edgeVisited[e] = true;
            for(size_t i = 1; i < c; ++i) {
                uint32_t en;
                out >> en;
                if(en < 1 || en > 2 * n) {
                    cout << en << " nie jest poprawną krawędzią\n";
                }
                if(edgeVisited[en]) {
                    cout << "Krawędź " << en << " jest powtórnie odwiedzona\n";
                }
                edgeVisited[en] = true;
                if((E[e].a != E[en].a) && (E[e].a != E[en].b) && (E[e].b != E[en].a) && (E[e].b != E[en].b)) {
                    cout << "Wykryto teleportacje z krawędzi " << e << " do krawędzi " << en << '\n';
                }
                if(i == 1 && (E[en].a != s) && (E[en].b != s)) {
                    cout << "Krawędź " << e << " nie prowadzi od wierzchołka " << s << '\n';
                }
                state = state + edgeS[e] - edgeLength[e] / 2 - edgeLength[en] / 2;
                if(state < 0) {
                    cout << "Błąd podczas przechodzenia z " << e << " do " << en << ": stan " << state << "\n";
                } else {
                    //cout << "Przejście z " << e << " do " << en << ": stan " << state << "\n";
                }
                e = en;
            }
            state = state + edgeS[e] - edgeLength[e] / 2 - edgeLength[first] / 2;
            if(state < 0) {
                cout << "Błąd podczas przechodzenia z " << e << " do " << first << ": stan " << state << "\n";
            } else {
                //cout << "Przejście z " << e << " do " << first << ": stan " << state << "\n";
            }
            cout << "Zestaw gotowy\n";
        } else {
            cout << ans << ": odpowiedź nie nie jest testowana\n";
        }
        delete [] edgeLength;
        delete [] edgeS;
        delete [] edgeVisited;
        delete [] E;
    }
    return 0;
}
