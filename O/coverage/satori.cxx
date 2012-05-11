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
        if(size() * 4 < _arraySize) {
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

/**
 * Wymagania:
 * DefaultConstructible<T>
 * CopyConstructible<T>
 * CopyAssignable<T>
 */
template<typename T, typename Compare = std::less<T> >
class Heap
{
public:
    Heap(Compare cmp = Compare()) : _tree(NULL), _size(0), _capacity(0), _cmp(cmp) {}
    Heap(std::size_t capacity, Compare cmp = Compare()) :
        _tree(new T[capacity]), _size(0), _capacity(capacity), _cmp(cmp) {}
    ~Heap() {
        delete [] _tree;
    }

    void push(const T &o);
    T top() const {
        return _tree[0];
    }
    T pop();
    bool isEmpty() const {
        return _size == 0;
    }

private:
    void upheap(std::size_t index);
    void downheap(std::size_t index);
    void resize(std::size_t newCapacity);

private:
    T *_tree;
    std::size_t _size;
    std::size_t _capacity;
    Compare _cmp;
};

template<typename T, typename Compare>
void Heap<T, Compare>::push(const T &o)
{
    if(_capacity == 0)
        resize(1);
    check(_tree != NULL);
    if(_size == _capacity)
        resize(_capacity * 2);
    check(_size < _capacity);
    _tree[_size] = o;
    ++_size;
    upheap(_size - 1);
}

template<typename T, typename Compare>
T Heap<T, Compare>::pop()
{
    T result = top();
    --_size;
    if(_size != 0) {
        _tree[0] = _tree[_size];
        downheap(0);
    }
    //if(_size * 4 < _capacity) {
    //    resize(_capacity / 2);
    //}
    return result;
}

template<typename T, typename Compare>
void Heap<T, Compare>::resize(std::size_t newCapacity)
{
    T *newTree = new T[newCapacity];
    for(std::size_t i = 0; i < _size; ++i) {
        newTree[i] = _tree[i];
    }
    delete [] _tree;
    _capacity = newCapacity;
    _tree = newTree;
}

template<typename T, typename Compare>
void Heap<T, Compare>::upheap(std::size_t index)
{
    if(index == 0) {
        return;
    }
    if(!_cmp(_tree[index], _tree[(index - 1) / 2])) {
        return;
    }
    T temp = _tree[index];
    while(index > 0 && _cmp(temp, _tree[(index - 1) / 2])) {
        _tree[index] = _tree[(index - 1) / 2];
        index = (index - 1) / 2;
    }
    _tree[index] = temp;
}

template<typename T, typename Compare>
void Heap<T, Compare>::downheap(std::size_t index)
{
    if(index >= _size / 2) {
        return;
    }
    T temp = _tree[index];
    while(index < _size / 2) {
        std::size_t selectedIndex = index * 2 + 1;
        if(selectedIndex + 1 < _size &&
                _cmp(_tree[selectedIndex + 1], _tree[selectedIndex])) {
            ++selectedIndex;
        }
        if(_cmp(temp, _tree[selectedIndex])) {
            break;
        } else {
            _tree[index] = _tree[selectedIndex];
            index = selectedIndex;
        }
    }
    _tree[index] = temp;
}

const size_t maxSize = 2500;

uint32_t H[maxSize + 2][maxSize + 2];
bool visited[maxSize + 2][maxSize + 2];
uint_fast16_t n, m;
uint32_t maxSolution;
uint_fast16_t k, l, x, y;

struct Comparator {
    bool operator()(const std::pair<uint16_t, uint16_t> &lhs,
                    const std::pair<uint16_t, uint16_t> &rhs) const {
        return H[lhs.first][lhs.second] < H[rhs.first][rhs.second];
    }
};

inline static void solution()
{
    using std::pair;
    using std::swap;
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        in >> n >> m;
        for(size_t i = 1; i <= n; ++i) {
            H[i][0] = H[i][m + 1] = std::numeric_limits< uint32_t >::max();
        }
        for(size_t i = 1; i <= m; ++i) {
            H[0][i] = H[n + 1][i] = std::numeric_limits< uint32_t >::max();
        }
        for(size_t i = 1; i <= n; ++i) {
            for(size_t j = 1; j <= m; ++j) {
                in >> H[i][j];
            }
        }
        for(size_t i = 1; i <= n; ++i) {
            for(size_t j = 1; j <= m; ++j) {
                visited[i][j] = false;
            }
        }
        maxSolution = 0;
        in >> k >> l >> x >> y;
        Heap<std::pair<uint16_t, uint16_t>, Comparator> heap((n+2)*(n+2));
        heap.push(std::pair<uint16_t, uint16_t>(k, l));
        visited[k][l]=true;
        while(!heap.isEmpty()) {
            std::pair<uint16_t, uint16_t> coord = heap.pop();
            maxSolution = std::max(maxSolution, H[coord.first][coord.second]);
            if(coord.first == x && coord.second == y) {
                break;
            }
            if(!visited[coord.first - 1][coord.second]) {
                heap.push(std::make_pair(coord.first - 1, coord.second));
                visited[coord.first-1][coord.second]=true;
            }
            if(!visited[coord.first + 1][coord.second]) {
                heap.push(std::make_pair(coord.first + 1, coord.second));
                visited[coord.first+1][coord.second]=true;
            }
            if(!visited[coord.first][coord.second - 1]) {
                heap.push(std::make_pair(coord.first, coord.second - 1));
                visited[coord.first][coord.second-1]=true;
            }
            if(!visited[coord.first][coord.second + 1]) {
                heap.push(std::make_pair(coord.first, coord.second + 1));
                visited[coord.first][coord.second+1]=true;
            }
        }
        out << maxSolution << '\n';
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


