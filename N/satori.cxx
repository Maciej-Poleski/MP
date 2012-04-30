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
#include <utility>
#include <cstdlib>

namespace
{
using namespace Wrapper;

template<typename T>
class Stack
{
public:
    Stack() : _arraySize(0) {}
    Stack(uint32_t size) : _arraySize(size) {
        if(size != 0) {
            _array = _top = new T[size];
        }
    }

    ~Stack() {
        if(_arraySize != 0)
            delete [] _array;
    }

    void push(T o) {
        if(_arraySize == 0)
            resize(1);
        else if(size() == _arraySize)
            resize(_arraySize * 2);
        *_top++ = o;
    }

    T pop() {
        T result = *--_top;
        if(size() * 2 < _arraySize) {
            try {
                resize(_arraySize / 2);
            } catch(std::bad_alloc) {
                // ignore
            }
        }
        return result;
    }
    T &top() {
        return *(_top - 1);
    }
    bool isEmpty() const {
        return (_arraySize == 0) || (_array == _top);
    }
    void clear() {
        if(_arraySize != 0) {
            _arraySize = 0;
            delete [] _array;
        }
    }
    uint32_t size() const {
        return _arraySize == 0 ? 0 : _top - _array;
    }

private:
    uint32_t _arraySize;
    T *_array;
    T *_top;

private:
    void resize(uint32_t newArraySize);
};

template<typename T>
void Stack<T>::resize(uint32_t newArraySize)
{
    if(newArraySize == 0) {
        this->clear();
    } else {
        T *newArray = new T[newArraySize];
        T *i = newArray;
        if(this->_arraySize != 0) {
            for(T *iterator = this->_array; iterator != this->_top; ++iterator) {
                *i++ = *iterator;
            }
            delete [] this->_array;
        }
        this->_array = newArray;
        this->_top = i;
        this->_arraySize = newArraySize;
    }
}

inline static void solution()
{
    using std::pair;
    using std::swap;
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        uint32_t *tab, *tmp;
        uint32_t n, k;
        in >> n >> k;
        tab = new uint32_t[n];
        for(uint32_t *i = tab, *e = tab + n; i != e; ++i)
            in >> *i;
        tmp = new uint32_t[n];
        uint64_t inversionCount = 0;
        uint32_t leftLength = 1;
        uint32_t rightLength = 1;
        while(leftLength < n) {
            uint32_t resultIterator = 0;
            while(resultIterator < n) {
                uint32_t leftIterator = resultIterator;
                uint32_t rightIterator = leftIterator + leftLength;
                uint32_t possibleInversionPoint = leftIterator;
                uint32_t leftEndMark = std::min(rightIterator, n);
                uint32_t rightEndMark = std::min(rightIterator + rightLength, n);
#ifdef DEBUG
                uint32_t sortedBegin = resultIterator;
                uint32_t leftBegin = leftIterator;
                uint32_t rightBegin = rightIterator;
                uint32_t leftEnd = leftEndMark;
                uint32_t rightEnd = rightEndMark;
                uint32_t sortedEnd = rightEndMark;
#endif
                while(leftIterator < leftEndMark || rightIterator < rightEndMark) {
                    if(rightIterator >= rightEndMark) {
                        while(leftIterator < leftEndMark)
                            tmp[resultIterator++] = tab[leftIterator++];
                    } else {
                        // at least one to merge
                        // find place in left part
                        while(possibleInversionPoint < leftEndMark && tab[possibleInversionPoint] +k >= tab[rightIterator])
                            ++possibleInversionPoint;
                        check(possibleInversionPoint <= leftEndMark);
                        inversionCount += leftEndMark - possibleInversionPoint;
                        // merge left part + right one
                        check(leftIterator <= leftEndMark);
                        while(leftIterator < leftEndMark && tab[leftIterator] >= tab[rightIterator])
                            tmp[resultIterator++] = tab[leftIterator++];
                        check(leftIterator <= leftEndMark);
                        tmp[resultIterator++] = tab[rightIterator++];
                    }
                }
#ifdef DEBUG
                for(size_t i = leftBegin + 1; i < leftEnd; ++i) {
                    check(tab[i - 1] >= tab[i]);
                }
                for(size_t i = rightBegin + 1; i < rightEnd; ++i) {
                    check(tab[i - 1] >= tab[i]);
                }
                for(size_t i = sortedBegin + 1; i < sortedEnd; ++i) {
                    check(tmp[i - 1] >= tmp[i]);
                }
#endif
            }
            swap(tmp, tab);
            leftLength *= 2;
            rightLength *= 2;
        }
        out<<inversionCount<<'\n';
        delete [] tab;
        delete [] tmp;
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

