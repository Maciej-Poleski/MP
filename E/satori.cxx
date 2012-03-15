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

static Wrapper::uint32_t *INORDER = 0;
static Wrapper::uint32_t *PREORDER = 0;
static Wrapper::uint32_t *POSTORDER = 0;
static Wrapper::uint32_t *inPtr = 0;

static inline void makePostorder(const Wrapper::uint32_t preBegin,
                                 const Wrapper::uint32_t inBegin,
                                 const Wrapper::uint32_t length)
{
    if(length == 1)
        Wrapper::out << INORDER[inBegin] << ' ';
    else if(length > 1) {
        Wrapper::uint32_t p;
        for(Wrapper::uint32_t i = 0;; ++i) {
            if((i % 2) == 1 && INORDER[inBegin + length - 1 - (i / 2)] == PREORDER[preBegin]) {
                p = inBegin + length - 1 - (i / 2);
                break;
            } else if((i % 2) == 0 && INORDER[inBegin + (i / 2)] == PREORDER[preBegin]) {
                p = inBegin + (i / 2);
                break;
            }
        }
        Wrapper::uint32_t leftLength = p - inBegin;
        makePostorder(preBegin + 1, inBegin, leftLength);
        makePostorder(preBegin + 1 + leftLength, inBegin + leftLength + 1, length - 1 - leftLength);
        Wrapper::out << INORDER[p] << ' ';
    }
}

static inline void makePreorder(const Wrapper::uint32_t postBegin,
                                const Wrapper::uint32_t inBegin,
                                const Wrapper::uint32_t length)
{
    if(length == 1)
        Wrapper::out << INORDER[inBegin] << ' ';
    else if(length > 1) {
        Wrapper::uint32_t p;
        for(Wrapper::uint32_t i = 0;; ++i) {
            if((i % 2) == 1 && INORDER[inBegin + length - 1 - (i / 2)] == POSTORDER[postBegin + length - 1]) {
                p = inBegin + length - 1 - (i / 2);
                break;
            } else if((i % 2) == 0 && INORDER[inBegin + (i / 2)] == POSTORDER[postBegin + length - 1]) {
                p = inBegin + (i / 2);
                break;
            }
        }
        Wrapper::uint32_t leftLength = p - inBegin;
        Wrapper::out << INORDER[p] << ' ';
        makePreorder(postBegin, inBegin, leftLength);
        makePreorder(postBegin + leftLength, inBegin + leftLength + 1, length - 1 - leftLength);
    }
}

static inline bool makeInorder(const Wrapper::uint32_t preBegin,
                               const Wrapper::uint32_t postBegin,
                               const Wrapper::uint32_t length)
{
    if(length == 0)
        return true;
    else if(length == 1) {
        *inPtr++ = PREORDER[preBegin];
        return true;
    } else {
        check(PREORDER[preBegin]==POSTORDER[postBegin+length-1]);
        if(PREORDER[preBegin + 1] == POSTORDER[postBegin + length - 1 - 1])
            return false;
        Wrapper::uint32_t p;
        for(Wrapper::uint32_t i = 0;; ++i) {
            if((i % 2) == 1 && POSTORDER[postBegin + length - 1 - 1 - 1 - (i / 2)] == PREORDER[preBegin + 1]) {
                p = postBegin + length - 1 - 1 - 1 - (i / 2);
                break;
            } else if((i % 2) == 0 && POSTORDER[postBegin + (i / 2)] == PREORDER[preBegin + 1]) {
                p = postBegin + (i / 2);
                break;
            }
        }
        Wrapper::uint32_t leftLength = p - postBegin+1;
        if(!makeInorder(preBegin + 1, postBegin, leftLength))
            return false;
        *inPtr++ = PREORDER[preBegin];
        return makeInorder(preBegin + 1 + leftLength, postBegin + leftLength, length - 1 - leftLength);
    }
}

inline static void solution()
{
    using namespace Wrapper;
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        std::tr1::uint_fast32_t n;
        in >> n;
        bool havePre = false;
        bool havePost = false;
        bool haveIn = false;
        for(std::tr1::uint_fast8_t q = 0; q < 2; ++q) {
            std::string order;
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
        }
        if(!havePre) {
            makePreorder(0, 0, n);
            out << '\n';
        } else if(!havePost) {
            makePostorder(0, 0, n);
            out << '\n';
        } else {
            check(!haveIn);
            delete [] INORDER;
            inPtr = INORDER = new Wrapper::uint32_t[n];
            if(makeInorder(0, 0, n)) {
                for(uint32_t *i = INORDER; i != inPtr; ++i)
                    out << *i << ' ';
                out << '\n';
            } else
                out << "ERROR\n";
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
