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
#include <cstring>

namespace
{
using namespace Wrapper;

struct Node {
    uint32_t edges[4];
};

static uint8_t *nextEdge = NULL;

struct Edge {
    uint32_t a, b;
    uint16_t s;
    uint16_t length;

    Edge() {}
    Edge(uint32_t a, uint32_t b, uint16_t length, uint16_t s) :
        a(a), b(b), s(s), length(length) {}
};

static bool *edgeVisited = NULL;
static Node *G = NULL;
static Edge *E = NULL;

static uint32_t *path = NULL;
static uint32_t *pathIterator;
static uint32_t *node = NULL;
static uint32_t *nodeIterator;

static void travel(uint32_t v, uint32_t e)
{
    check(v == E[e].a || v == E[e].b);
    check(nextEdge[v] <= 4);
    edgeVisited[e] = true;
    for(;;) {
        if(nextEdge[v] == 4) {
            break;
        }
        while(nextEdge[v] < 4 && edgeVisited[G[v].edges[nextEdge[v]++]]);
        if(edgeVisited[G[v].edges[nextEdge[v] - 1]]) {
            break;
        }
        uint32_t d = E[G[v].edges[nextEdge[v] - 1]].a == v ?
                     E[G[v].edges[nextEdge[v] - 1]].b :
                     E[G[v].edges[nextEdge[v] - 1]].a;
        travel(d, G[v].edges[nextEdge[v] - 1]);
    }
    *pathIterator++ = e;
    *nodeIterator++ = (E[e].a == v) ? (E[e].b) : (E[e].a);
}

inline static void solution()
{
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        uint32_t n;
        in >> n;
        delete [] nextEdge;
        nextEdge = new uint8_t[n + 1];
        memset(nextEdge, 0, (n + 1)*sizeof(uint8_t));
        delete [] edgeVisited;
        edgeVisited = new bool[n * 2 + 1];
        memset(edgeVisited, 0, (n * 2 + 1)*sizeof(bool));
        delete [] G;
        delete [] E;
        G = new Node[n + 1];
        E = new Edge[2 * n + 1];
        uint32_t length = 0;
        uint32_t value = 0;
        delete [] path;
        path = pathIterator = new uint32_t[2 * n];
        delete [] node;
        node = nodeIterator = new uint32_t[2 * n];
        for(size_t i = 1; i <= 2 * n; ++i) {
            uint32_t a, b;
            uint16_t l, s;
            in >> a >> b >> l >> s;
            length += l;
            value += s;
            E[i] = Edge(a, b, l, s);
            G[a].edges[nextEdge[a]++] = i;
            G[b].edges[nextEdge[b]++] = i;
        }
        memset(nextEdge, 0, (n + 1)*sizeof(uint8_t));
        if(length <= value) {
            out << "TAK\n";
            travel(E[1].a, 1);
            int32_t state = 0;
            int32_t minState = std::numeric_limits< int32_t>::max();
            uint32_t selectedState = 0;
            for(size_t i = 1; i <= 2 * n; ++i) {
                int32_t newState = state + E[path[i - 1]].s - E[path[i - 1]].length / 2 -
                                   E[path[i % (2 * n)]].length / 2;
                if(newState < minState) {
                    minState = newState;
                    selectedState = i;
                }
                state = newState;
            }
            selectedState = selectedState % (2 * n);
            out << pathIterator - path << '\n';
            out << path[selectedState] << ' ' << node[selectedState] << '\n';
            uint32_t count = pathIterator - path - 1;
            while(count > 0) {
                selectedState = (selectedState + 1) % (2 * n);
                out << path[selectedState] << '\n';
                --count;
            }
        } else {
            out << "NIE\n";
        }
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

