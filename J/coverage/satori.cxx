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

static uint_fast32_t n, m;

struct QueueEntry {
    uint32_t vertex;
    bool nextIterationIsRequired;

    QueueEntry() {}
    QueueEntry(uint32_t vertex, bool nextIterationIsRequired) : vertex(vertex),
        nextIterationIsRequired(nextIterationIsRequired) {}
};

struct Edge {
    uint32_t value;
    bool isSlow;
    Edge *next;

    Edge(uint32_t value, bool isSlow, Edge *next) : value(value), isSlow(isSlow),
        next(next) {}
};

struct Vertex {
    Edge *edges;
    int32_t distance;

    Vertex() : edges(NULL), distance(-1) {}

    ~Vertex() {
        for(Edge *i = edges; i;) {
            Edge *next = i->next;
            i->next = NULL;
            delete i;
            i = next;
        }
    }
};

static Vertex *G = NULL;
static QueueEntry *queue, *queueBegin, *queueEnd = NULL;

static inline bool tryRelax(uint_fast32_t from, const Edge &edge)
{
    if(G[edge.value].distance == -1) {
        G[edge.value].distance = G[from].distance + (edge.isSlow ? 2 : 1);
        return true;
    } else if(G[edge.value].distance > G[from].distance + (edge.isSlow ? 2 : 1)) {
        G[edge.value].distance = G[from].distance + (edge.isSlow ? 2 : 1);
        return true;
    } else {
        return false;
    }
}

inline static void solution()
{
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        in >> n >> m;
        delete [] queue;
        delete [] G;
        queue = queueBegin = queueEnd = new QueueEntry[std::max(n, m)];
        QueueEntry *endOfQueue = queue + std::max(n, m);
        G = new Vertex[n + 1];
        for(size_t i = 0; i < m; ++i) {
            uint32_t a, b;
            char c;
            in >> a >> b;
            in.ignore(1);
            c = in.get();
            G[a].edges = new Edge(b, c == '#', G[a].edges);
            G[b].edges = new Edge(a, c == '#', G[b].edges);
        }
        G[1].distance = 0;
        *queueEnd++ = QueueEntry(1, false);
        while(queueBegin != queueEnd) {
            QueueEntry entry = *queueBegin++;
            if(queueBegin == endOfQueue)
                queueBegin = queue;
            if(entry.nextIterationIsRequired) {
                *queueEnd++ = QueueEntry(entry.vertex, false);
                if(queueEnd == endOfQueue)
                    queueEnd = queue;
                continue;
            } else {
                for(Edge *i = G[entry.vertex].edges; i; i = i->next) {
                    if(tryRelax(entry.vertex, *i)) {
                        *queueEnd++ = QueueEntry(i->value, i->isSlow);
                        if(queueEnd == endOfQueue)
                            queueEnd = queue;
                    }
                }
            }
        }
        for(size_t i = 1; i <= n; ++i)
            if(G[i].distance != -1)
                out << G[i].distance << '\n';
            else
                out << "!\n";
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

