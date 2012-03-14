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

Wrapper::uint32_t *INORDER = 0;
Wrapper::uint32_t *PREORDER = 0;
Wrapper::uint32_t *POSTORDER = 0;

inline static void solution()
{
    using namespace Wrapper;
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        std::tr1::uint_fast32_t n;
        in >> n;
        while(n--) {
            std::string order;
            bool havePre = false;
            bool havePost = false;
            bool haveIn = false;

            in >> order;
            if(order[1] == 'R') {
                havePre = true;
                delete [] PREORDER;
                PREORDER = new Wrapper::uint32_t[n];
                for(Wrapper::uint32_t *i = PREORDER, *e = PREORDER + n; i != e; ++i) {
                    in >> *i;
                }
            } else if(order[1] == 'O') {
                havePost = true;
                delete [] POSTORDER;
                POSTORDER = new Wrapper::uint32_t[n];
                for(Wrapper::uint32_t *i = POSTORDER, *e = POSTORDER + n; i != e; ++i) {
                    in >> *i;
                }
            } else {
                check(order[1] == 'N');
                haveIn = true;
                delete [] INORDER;
                INORDER = new Wrapper::uint32_t[n];
                for(Wrapper::uint32_t *i = INORDER, *e = INORDER + n; i != e; ++i) {
                    in >> *i;
                }
            }
            if(!havePre)
	    {
		// make preorder
	    }
	    else if(!havePost)
	    {
		// make postorder
	    }
	    else
	    {
		check(!haveIn);
		// make inorder
	    }
        }
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
