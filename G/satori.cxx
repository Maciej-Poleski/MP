//Maciej Poleski
#ifdef DEBUG
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
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
#define check(x) assert(x)
#else
#ifndef NDEBUG
#define NDEBUG
#endif
#define check(x)
#include <iostream>
namespace Wrapper
{
std::istream &in = std::cin;
std::ostream &out = std::cout;
}
#endif

#include <tr1/cstdint>

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
}

#include <string>
#include <algorithm>

inline static void solution()
{
    using namespace Wrapper;
    std::tr1::uint_fast32_t z;
    in >> z;
    struct Node {
        uint32_t left;
        uint32_t right;
    };
    Node *T = 0;
    while(z--) {
        std::tr1::uint_fast32_t n, r;
        in >> n >> r;
        delete []T;
        T = new Node[n + 1];
        for(Node *i = T + 1, *e = T + n + 1; i != e; ++i) {
            in >> i->left >> i->right;
        }
        uint32_t p = -1;
        uint32_t c = static_cast<uint32_t>(r);
        uint32_t l = p;
        while(c != -1) {
            out << c << ' ';
            do {
                l = c;
                // Rotate left
                uint32_t t = T[c].left;
                T[c].left = T[c].right;
                T[c].right = p;
                p = c;
                c = t;
                if(c == 0) {
                    c = p;
                    p = 0;
                }
            } while(c == l);
        }
        out << '\n';
    }
}

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);
#ifdef DEBUG
    init(argc, argv);
#endif
    solution();
    return 0;
}
