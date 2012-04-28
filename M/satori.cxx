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
    srand(404);
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        int32_t *tab;
        uint32_t n;
        in >> n;
        tab = new int32_t[n];
        for(int32_t *i = tab, *e = tab + n; i != e; ++i)
            in >> *i;
        // QUICK SORT
        Stack<pair<uint32_t, uint32_t> > stack;
        stack.push(pair<uint32_t, uint32_t>(0, n));
        bool statePrepared = false;
        uint32_t left, right;
        while(statePrepared || !stack.isEmpty()) {
            if(!statePrepared) {
                left = stack.top().first;
                right = stack.top().second;
                stack.pop();
            }
            if(right - left < 50) {
                statePrepared = false;
                continue;
            }
            check(left < right);
            // LOMUTO
            uint32_t position = rand() % (right - left) + left;
            check(position >= left);
            check(position < right);
            const int32_t selectedValue = tab[position];
            uint32_t less = left;
            uint32_t equal = left;
            for(uint32_t iterator = left; iterator < right; ++iterator) {
                if(tab[iterator] > selectedValue) {
                    // DO NOTHING
                } else if(tab[iterator] == selectedValue) {
                    swap(tab[equal++], tab[iterator]);
                } else {
                    int32_t v=tab[iterator];
                    tab[iterator]=tab[equal];
                    tab[equal++]=tab[less];
                    tab[less++]=v;
                }
            }
#ifdef DEBUG
            // CHECK LOMUTO
            for(size_t i = left; i < less; ++i)
                check(tab[i] < selectedValue);
            for(size_t i = less; i < equal; ++i)
                check(tab[i] == selectedValue);
            for(size_t i = equal; i < right; ++i)
                check(tab[i] > selectedValue);
#endif
            if(less - left < right - equal) {
                stack.push(std::make_pair(equal, right));
                right = less;
            } else {
                stack.push(std::make_pair(left, less));
                left = equal;
            }
            statePrepared = true;
        }
        // INSERTION SORT
        for(uint32_t i=1;i<n;++i)
        {
            int32_t value=tab[i];
            int32_t position=i-1;
            while(position>=0 && tab[position]>value)
            {
                tab[position+1]=tab[position];
                --position;
            }
            tab[position+1]=value;
        }
#ifdef DEBUG
        // CHECK SORTED
        for(size_t i=1;i<n;++i)
            check(tab[i-1]<=tab[i]);
#endif
        for(int32_t *i = tab, *e = tab + n; i != e; ++i)
            out << *i << ' ';
        out << '\n';
        delete [] tab;
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

