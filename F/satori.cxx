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

typedef std::tr1::uint_fast64_t uint_fast64_t;
typedef std::tr1::uint_fast32_t uint_fast32_t;
typedef std::tr1::uint_fast16_t uint_fast16_t;
typedef std::tr1::uint_fast8_t uint_fast8_t;

typedef std::tr1::uint64_t uint64_t;
typedef std::tr1::uint32_t uint32_t;
typedef std::tr1::uint16_t uint16_t;
typedef std::tr1::uint8_t uint8_t;

}
#endif

#include <tr1/cstdint>
#include <string>
#include <algorithm>

struct Node
{
    Wrapper::uint32_t left;
    Wrapper::uint32_t right;
};

Node *T=0;

inline static void solution()
{
    using namespace Wrapper;
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        std::tr1::uint_fast32_t n,r;
        in >> n>>r;
        delete []T;
	T=new Node[n+1];
	
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
