//Maciej Poleski
#ifdef DEBUG
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
namespace
{
namespace Wrapper
{
std::ifstream in;
std::ofstream out;
}
void init(int argc, char **argv)
{
    if(argc != 3) {
        std::cerr << "Potrzeba dokładnie dwóch argumentów\n";
        std::abort();
    }
    Wrapper::in.open(argv[1]);
    Wrapper::out.open(argv[2]);
}
}
#define check(x) assert(x)
#else
#ifndef NDEBUG
#define NDEBUG
#endif
#define check(x)
#include <iostream>
namespace
{
namespace Wrapper
{
std::istream &in = std::cin;
std::ostream &out = std::cout;
}
}
#endif

#include <tr1/cstdint>

namespace
{
namespace Wrapper
{
typedef std::tr1::uint_fast64_t uint_fast64_t;
typedef std::tr1::uint_fast32_t uint_fast32_t;
typedef std::tr1::uint_fast16_t uint_fast16_t;
typedef std::tr1::uint_fast8_t uint_fast8_t;

typedef std::tr1::uint64_t uint64_t;
typedef std::tr1::uint32_t uint32_t;
typedef std::tr1::uint16_t uint16_t;
typedef std::tr1::uint8_t uint8_t;

typedef std::tr1::int_fast64_t int_fast64_t;
typedef std::tr1::int_fast32_t int_fast32_t;
typedef std::tr1::int_fast16_t int_fast16_t;
typedef std::tr1::int_fast8_t int_fast8_t;

typedef std::tr1::int64_t int64_t;
typedef std::tr1::int32_t int32_t;
typedef std::tr1::int16_t int16_t;
typedef std::tr1::int8_t int8_t;

typedef std::size_t size_t;
}

}

#include <string>
#include <algorithm>
#include <limits>
#include <locale>

namespace
{
using namespace Wrapper;

struct Edge {
    const uint16_t v;
    const bool required;
    Edge *next;

    Edge(uint16_t v, bool required, Edge *next) :
        v(v), required(required), next(next) {}

    ~Edge() {
        for(Edge *i = next; i;) {
            Edge *next = i->next;
            i->next=NULL;
            delete i;
            i = next;
        }
    }
} __attribute__((packed));

struct Node {
    bool enabled;
    bool visited;

    Edge *edges;

    Node() : enabled(false), visited(false), edges(NULL) {}

    ~Node() {
        delete edges;
    }
} __attribute__((packed));

static Node *G;

static bool travelsar(uint16_t v)
{
    G[v].visited = true;
    for(Edge *i = G[v].edges; i; i = i->next) {
        if(i->required) {
            if(G[i->v].visited == false) {
                G[i->v].enabled = !G[v].enabled;
                if(!travelsar(i->v)) {
                    return false;
                }
            } else {
                if(G[i->v].enabled == G[v].enabled) {
                    return false;
                }
            }
        } else {
            if(G[i->v].visited == false) {
                G[i->v].enabled = G[v].enabled;
                if(!travelsar(i->v)) {
                    return false;
                }
            } else {
                if(G[i->v].enabled != G[v].enabled) {
                    return false;
                }
            }
        }
    }
    return true;
}

inline static void solution()
{
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        uint_fast16_t n;
        uint_fast32_t m;
        in >> n >> m;
        G = new Node[n + 1];
        for(size_t i = 0; i < m; ++i) {
            uint16_t a, b;
            std::string state;
            in >> a >> b >> state;
            G[a].edges = new Edge(b, state[1] == 'N', G[a].edges);
            G[b].edges = new Edge(a, state[1] == 'N', G[b].edges);
        }
        if(travelsar(1)) {
            for(size_t i = 1; i <= n; ++i) {
                if(G[i].enabled) {
                    out << i << ' ';
                }
            }
            out << '\n';
        } else {
            out << "NIE\n";
        }
        delete [] G;
    }
}

} // namespace

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);
#ifdef DEBUG
    init(argc, argv);
#else
    (void)argc;
    (void)argv;
#endif
    solution();
    return 0;
}

