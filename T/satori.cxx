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
#include <tr1/random>
#include <algorithm>

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
    if(_size * 4 < _capacity) {
        resize(_capacity / 2);
    }
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


/**
 * Wymagania:
 * DefaultConstructible<T>
 * CopyConstructible<T>
 * CopyAssignable<T>
 * LessThanComparable<T>
 *
 * SizeType musi być typem całkowito liczbowym zdolnym do indeksowania całej
 * struktury.
 */
template<typename T, typename SizeType>
class MinMaxHeap
{
public:
    MinMaxHeap() : _minTree(NULL), _maxTree(NULL), _size(0), _capacity(0) {}
    MinMaxHeap(std::size_t capacity) :
        _minTree(new Node[capacity]), _maxTree(new Node[capacity]), _size(0), _capacity(capacity) {}
    ~MinMaxHeap() {
        delete [] _minTree;
        delete [] _maxTree;
    }

    void push(const T &o);
    T min() const {
        return _minTree[0].value;
    }
    T max() const {
        return _maxTree[0].value;
    }
    T popMin();
    T popMax();
    bool isEmpty() const {
        return _size == 0;
    }
    std::size_t size() const {
        return _size;
    }
    void clean();

private:
    void upheap(std::size_t index);
    void downheap(std::size_t index);
    void resize(std::size_t newCapacity);
    void upheapMin(std::size_t index);
    void upheapMax(std::size_t index);
    void downheapMin(std::size_t index);
    void downheapMax(std::size_t index);
    void fixLinkFromMinSide(std::size_t index) {
        _maxTree[_minTree[index].link].link = index;
    }
    void fixLinkFromMaxSide(std::size_t index) {
        _minTree[_maxTree[index].link].link = index;
    }
    void moveMinNode(std::size_t to, std::size_t from) {
        _minTree[to] = _minTree[from];
        fixLinkFromMinSide(to);
    }
    void moveMaxNode(std::size_t to, std::size_t from) {
        _maxTree[to] = _maxTree[from];
        fixLinkFromMaxSide(to);
    }

    void checkHeap() {
#ifdef DEBUG
        using namespace std::rel_ops;
        for(size_t i = 1; i < _size; ++i)
            check(_minTree[(i - 1) / 2] <= _minTree[i]);
        for(size_t i = 1; i < _size; ++i)
            check(_maxTree[(i - 1) / 2] >= _maxTree[i]);
        for(size_t i = 0; i < _size; ++i) {
            check(_minTree[i].value == _maxTree[_minTree[i].link].value);
            check(_maxTree[i].value == _minTree[_maxTree[i].link].value);
        }
        for(size_t i = 0; i < _size; ++i) {
            check(i == _maxTree[_minTree[i].link].link);
            check(i == _minTree[_maxTree[i].link].link);
        }
#endif
    }

private:
    struct Node {
        T value;
        SizeType link;  // Dowiązanie - indeks w tablicy drugiego kopca

        Node() {}
        Node(const T &value, SizeType link) : value(value), link(link) {}

        bool operator<(const Node &o) const {
            return value < o.value;
        }
    };

    Node *_minTree;
    Node *_maxTree;
    std::size_t _size;
    std::size_t _capacity;
};

template<typename T, typename SizeType>
void MinMaxHeap<T, SizeType>::clean()
{
    delete [] _maxTree;
    delete [] _minTree;
    _maxTree = _minTree = NULL;
    _size = _capacity = 0;
}

template<typename T, typename SizeType>
void MinMaxHeap<T, SizeType>::push(const T &o)
{
    if(_capacity == 0)
        resize(1);
    check(_minTree != NULL);
    check(_maxTree != NULL);
    if(_size == _capacity)
        resize(_capacity * 2);
    check(_size < _capacity);
    _minTree[_size] = Node(o, _size);
    _maxTree[_size] = Node(o, _size);
    ++_size;
    upheapMin(_size - 1);
    upheapMax(_size - 1);
    checkHeap();
}

template<typename T, typename SizeType>
T MinMaxHeap<T, SizeType>::popMin()
{
    using namespace std::rel_ops;
    Node result = _minTree[0];
    --_size;
    if(_size != 0) {
        moveMinNode(0, _size);
        downheapMin(0);
        if(result.link < _size) {
            if(_maxTree[result.link] < _maxTree[_size]) {
                moveMaxNode(result.link, _size);
                upheapMax(result.link);
            } else if(_maxTree[result.link] > _maxTree[_size]) {
                moveMaxNode(result.link, _size);
                downheapMax(result.link);
            } else {
                moveMaxNode(result.link, _size);
            }
        }
    }
    if(_size * 4 < _capacity) {
        resize(_capacity / 2);
    }
    checkHeap();
    return result.value;
}

template<typename T, typename SizeType>
T MinMaxHeap<T, SizeType>::popMax()
{
    using namespace std::rel_ops;
    Node result = _maxTree[0];
    --_size;
    if(_size != 0) {
        moveMaxNode(0, _size);
        downheapMax(0);
        if(result.link < _size) {
            if(_minTree[result.link] < _minTree[_size]) {
                moveMinNode(result.link, _size);
                downheapMin(result.link);
            } else if(_minTree[result.link] > _minTree[_size]) {
                moveMinNode(result.link, _size);
                upheapMin(result.link);
            } else {
                moveMinNode(result.link, _size);
            }
        }
    }
    if(_size * 4 < _capacity) {
        resize(_capacity / 2);
    }
    checkHeap();
    return result.value;
}

template<typename T, typename SizeType>
void MinMaxHeap<T, SizeType>::resize(std::size_t newCapacity)
{
    {
        Node *newMinTree = new Node[newCapacity];
        for(std::size_t i = 0; i < _size; ++i) {
            newMinTree[i] = _minTree[i];
        }
        delete [] _minTree;
        _minTree = newMinTree;
    }
    {
        Node *newMaxTree = new Node[newCapacity];
        for(std::size_t i = 0; i < _size; ++i) {
            newMaxTree[i] = _maxTree[i];
        }
        delete [] _maxTree;
        _maxTree = newMaxTree;
    }
    _capacity = newCapacity;
    checkHeap();
}

template<typename T, typename SizeType>
void MinMaxHeap<T, SizeType>::upheapMin(std::size_t index)
{
    if(index == 0) {
        return;
    }
    if(!(_minTree[index] < _minTree[(index - 1) / 2])) {
        return;
    }
    Node temp = _minTree[index];
    while(index > 0 && (temp < _minTree[(index - 1) / 2])) {
        moveMinNode(index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
    _minTree[index] = temp;
    fixLinkFromMinSide(index);
}

template<typename T, typename SizeType>
void MinMaxHeap<T, SizeType>::upheapMax(std::size_t index)
{
    using namespace std::rel_ops;
    if(index == 0) {
        return;
    }
    if(!(_maxTree[index] > _maxTree[(index - 1) / 2])) {
        return;
    }
    Node temp = _maxTree[index];
    while(index > 0 && (temp > _maxTree[(index - 1) / 2])) {
        moveMaxNode(index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
    _maxTree[index] = temp;
    fixLinkFromMaxSide(index);
}

template<typename T, typename SizeType>
void MinMaxHeap<T, SizeType>::downheapMin(std::size_t index)
{
    if(index >= _size / 2) {
        return;
    }
    Node temp = _minTree[index];
    while(index < _size / 2) {
        std::size_t selectedIndex = index * 2 + 1;
        if(selectedIndex + 1 < _size &&
                (_minTree[selectedIndex + 1] < _minTree[selectedIndex])) {
            ++selectedIndex;
        }
        if(temp < _minTree[selectedIndex]) {
            break;
        } else {
            moveMinNode(index, selectedIndex);
            index = selectedIndex;
        }
    }
    _minTree[index] = temp;
    fixLinkFromMinSide(index);
}

template<typename T, typename SizeType>
void MinMaxHeap<T, SizeType>::downheapMax(std::size_t index)
{
    using namespace std::rel_ops;
    if(index >= _size / 2) {
        return;
    }
    Node temp = _maxTree[index];
    while(index < _size / 2) {
        std::size_t selectedIndex = index * 2 + 1;
        if(selectedIndex + 1 < _size &&
                (_maxTree[selectedIndex + 1] > _maxTree[selectedIndex])) {
            ++selectedIndex;
        }
        if(temp > _maxTree[selectedIndex]) {
            break;
        } else {
            moveMaxNode(index, selectedIndex);
            index = selectedIndex;
        }
    }
    _maxTree[index] = temp;
    fixLinkFromMaxSide(index);
}

/**
 * Sortowanie przez wstawianie
 *
 * Wymagania:
 * LessThanComparable<T>
 * CopyConstructible<T>
 * CopyAssignable<T>
 */
template<typename T>
void insertionSort(T *tab, std::size_t length)
{
    using namespace std::rel_ops;
    for(std::size_t i = 1; i < length; ++i) {
        T value = tab[i];
        int_fast32_t position = i - 1;
        while(position >= 0 && tab[position] > value) {
            tab[position + 1] = tab[position];
            --position;
        }
        tab[position + 1] = value;
    }
}

/**
 * Wymagania:
 * LessThanComparable<T>
 * CopyConstructible<T>
 * CopyAssignable<T>
 * DefaultConstructible<T>
 *
 * Nie należy używać tej funkcji. Zamiast niej zastosować std::nth_element.
 */
template<typename T>
T kthElement(T *tab, uint32_t length, uint32_t element)
{
    using std::swap;
    using namespace std::rel_ops;
    check(element < length);
    if(length < 50) {
        insertionSort(tab, length);
        return tab[element];
    }
    // Select pivot
    for(uint32_t i = 0; i + 5 <= length; i += 5)
        insertionSort(tab + i, 5);
    T selectedValue;
    {
        uint32_t i = 0;
        for(uint32_t m = 2; m + 3 <= length; m += 5)
            swap(tab[i++], tab[m]);

        selectedValue = kthElement(tab, i, i / 2);
    }
    // LOMUTO
    uint32_t less = 0;
    uint32_t equal = 0;
    for(uint32_t iterator = 0; iterator < length; ++iterator) {
        if(tab[iterator] > selectedValue) {
            // DO NOTHING
        } else if(tab[iterator] == selectedValue) {
            swap(tab[equal++], tab[iterator]);
        } else {
            T v = tab[iterator];
            tab[iterator] = tab[equal];
            tab[equal++] = tab[less];
            tab[less++] = v;
        }
    }
    if(element < less) {
        return kthElement(tab, less, element);
    } else if(element < equal) {
        return selectedValue;
    } else {
        return kthElement(tab + equal, length - equal, element - equal);
    }
}

struct Node {
    uint32_t value;
    uint32_t busy;

    Node() : value(0), busy(0) {}
};

static uint32_t nextpow2(uint32_t v) __attribute__((const));
static uint32_t nextpow2(uint32_t v)
{
    uint32_t r = 1;
    while(r < v)
        r *= 2;
    return r;
}

class SumTree
{
public:
    SumTree(std::size_t size) :
        _size(nextpow2(size)), _tree(new Node[_size * 2]) {}

    ~SumTree() {
        delete [] _tree;
    }

    void add(uint32_t index, uint32_t v);
    uint32_t del(uint32_t index);
    uint32_t sum(uint32_t a, uint32_t b);
    uint32_t ave(uint32_t a, uint32_t b);
    uint32_t nxt(uint32_t index);
    uint32_t value(uint32_t index) {
        return _tree[index + _size].value;
    }
    uint32_t size() const {
        return _size;
    }

private:
    std::size_t _size;
    Node *_tree;
};

void SumTree::add(uint32_t index, uint32_t v)
{
    uint32_t busy = _tree[_size + index].busy == 0;
    for(size_t i = index + _size; i > 0; i /= 2) {
        _tree[i].value += v;
        _tree[i].busy += busy;
    }
}

uint32_t SumTree::del(uint32_t index)
{
    uint32_t result = _tree[_size + index].value;
    uint32_t busy = _tree[_size + index].busy;
    check((result == 0) == (busy == 0));
    for(size_t i = index + _size; i > 0; i /= 2) {
        _tree[i].value -= result;
        _tree[i].busy -= busy;
    }
    return result;
}

uint32_t SumTree::sum(uint32_t a, uint32_t b)
{
    if(a == 0 && b == _size - 1)
        return _tree[1].value;
    uint_fast32_t left = a + _size;
    uint_fast32_t right = b + _size;
    uint32_t result = 0;
    uint_fast8_t height = 0;
    uint_fast32_t i = left;
    while(true) {
        if(left > right)
            break;
        while((i << height) < left || (((i + 1) << height) - 1) > right) {
            i *= 2;
            --height;
        }
        while((((i / 2) << (height + 1)) >= left) &&
                (((i / 2 + 1) << (height + 1)) - 1 <= right)) {
            i /= 2;
            ++height;
        }
        result += _tree[i].value;
        left = (i + 1) << height;
        ++i;
    }
    return result;
}

uint32_t SumTree::ave(uint32_t a, uint32_t b)
{
    if(a == 0 && b == _size - 1) {
        return (_tree[1].busy != 0)
               ? static_cast<uint32_t>(
                   static_cast<double>(_tree[1].value) / _tree[1].busy + .5)
               : 0;
    }
    uint_fast32_t left = a + _size;
    uint_fast32_t right = b + _size;
    uint32_t result = 0;
    uint32_t busy = 0;
    uint_fast8_t height = 0;
    uint_fast32_t i = left;
    while(true) {
        if(left > right)
            break;
        while((i << height) < left || (((i + 1) << height) - 1) > right) {
            i *= 2;
            --height;
        }
        while((((i / 2) << (height + 1)) >= left) &&
                (((i / 2 + 1) << (height + 1)) - 1 <= right)) {
            i /= 2;
            ++height;
        }
        result += _tree[i].value;
        busy += _tree[i].busy;
        left = (i + 1) << height;
        ++i;
    }
    if(busy == 0)
        return 0;
    return static_cast<uint32_t>(static_cast<double>(result) / busy + .5);
}

uint32_t SumTree::nxt(uint32_t index)
{
    if(index >= _size - 1)
        return _size;
    uint_fast32_t i = index + _size + 1;
    if(_tree[i].busy != 0)
        return i - _size;
    while(true) {
        if(i == 0)
            return _size;
        if((i & 1) == 1)
            i /= 2;
        else {
            if(_tree[i].busy == _tree[i / 2].busy) {
                i /= 2;
            } else {
                ++i;
                break;
            }
        }
    }
    while(true) {
        if(i >= _size)
            break;
        if(_tree[i * 2].busy != 0)
            i *= 2;
        else
            i = i * 2 + 1;
    }
    return i - _size;
}

struct Event {
    int32_t x, y1, y2;
    uint8_t p;

    Event() = default;
    Event(int32_t x, int32_t y1, int32_t y2, uint8_t p) :
        x(x), y1(y1), y2(y2), p(p) {}
};

bool operator<(const Event &lhs, const Event &rhs)
{
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.p < rhs.p));
}

class IntTree
{
public:
    class Builder;
    friend class Builder;
    ~IntTree();
    void add(int32_t a, int32_t b);
    void sub(int32_t a, int32_t b);
    uint32_t get(int32_t);

private:
    IntTree(int32_t *mapping, uint32_t mappingLength);

private:
    int32_t *_mapping;
    size_t _mappingSize;
    uint32_t *_tree;
    size_t _treeSize;
    uint32_t *_auxCoverage;
};

class IntTree::Builder
{
public:
    Builder(size_t size) : _mapping(new int32_t[size]), _size(0) {}
    ~Builder() {
        delete [] _mapping;
    }
    Builder(const Builder &) = delete;
    Builder &operator=(const Builder &) = delete;

    void insertPoint(int32_t p) {
        _mapping[_size++] = p;
    }
    IntTree build();

private:
    int32_t *_mapping;
    size_t _size;
};

IntTree IntTree::Builder::build()
{
    std::sort(_mapping, _mapping + _size);
    _size = std::unique(_mapping, _mapping + _size) - _mapping;
    int32_t *mapping = new int32_t[_size];
    memcpy(mapping, _mapping, _size * sizeof(int32_t));
    delete [] _mapping;
    _mapping = NULL;
    return IntTree(mapping, _size);
}

IntTree::IntTree(int32_t *mapping, uint32_t mappingLength) :
    _mapping(mapping), _mappingSize(mappingLength),
    _tree(new uint32_t[nextpow2(mappingLength - 1) * 2]),
    _treeSize(nextpow2(mappingLength - 1)),
    _auxCoverage(new uint32_t[mappingLength])
{
    memset(_tree, 0, _treeSize * 2 * sizeof(uint32_t));
    memset(_auxCoverage, 0, mappingLength * sizeof(uint32_t));
}

IntTree::~IntTree()
{
    delete [] _mapping;
    delete [] _tree;
    delete [] _auxCoverage;
}

void IntTree::add(int32_t x, int32_t y)
{
    size_t a = std::lower_bound(_mapping, _mapping + _mappingSize, x) - _mapping;
    size_t b = std::lower_bound(_mapping, _mapping + _mappingSize, y) - _mapping;

    ++_auxCoverage[b];
    if(b == 0)
        return;
    --b;

    if(a == 0 && b == _treeSize - 1) {
        ++_tree[1];
        return;
    }
    uint_fast32_t left = a + _treeSize;
    uint_fast32_t right = b + _treeSize;
    uint_fast8_t height = 0;
    uint_fast32_t i = left;
    while(true) {
        if(left > right)
            break;
        while((i << height) < left || (((i + 1) << height) - 1) > right) {
            i *= 2;
            --height;
        }
        while((((i / 2) << (height + 1)) >= left) &&
                (((i / 2 + 1) << (height + 1)) - 1 <= right)) {
            i /= 2;
            ++height;
        }
        ++_tree[i];
        left = (i + 1) << height;
        ++i;
    }
}

void IntTree::sub(int32_t x, int32_t y)
{
    size_t a = std::lower_bound(_mapping, _mapping + _mappingSize, x) - _mapping;
    size_t b = std::lower_bound(_mapping, _mapping + _mappingSize, y) - _mapping;

    --_auxCoverage[b];
    if(b == 0)
        return;
    --b;

    if(a == 0 && b == _treeSize - 1) {
        --_tree[1];
        return;
    }
    uint_fast32_t left = a + _treeSize;
    uint_fast32_t right = b + _treeSize;
    uint_fast8_t height = 0;
    uint_fast32_t i = left;
    while(true) {
        if(left > right)
            break;
        while((i << height) < left || (((i + 1) << height) - 1) > right) {
            i *= 2;
            --height;
        }
        while((((i / 2) << (height + 1)) >= left) &&
                (((i / 2 + 1) << (height + 1)) - 1 <= right)) {
            i /= 2;
            ++height;
        }
        --_tree[i];
        left = (i + 1) << height;
        ++i;
    }
}

uint32_t IntTree::get(int32_t i)
{
    if(i < _mapping[0] || i > _mapping[_mappingSize - 1])
        return 0;
    size_t p = std::lower_bound(_mapping, _mapping + _mappingSize, i) - _mapping;
    if(_mapping[p] == i) {
        uint32_t result = _auxCoverage[p];
        if(p == _mappingSize - 1) {
            return result;
        }
        for(size_t i = p + _treeSize; i != 0; i /= 2) {
            result += _tree[i];
        }
        return result;
    } else {
        uint32_t result = 0;
        for(size_t i = p + _treeSize - 1; i != 0; i /= 2) {
            result += _tree[i];
        }
        return result;
    }
}

/**
 * Sortowanie nierekurencyjne (złożoność pamięciowa O(log(size)))
 *
 * Wymagania:
 * LessThanComparable<T>
 * CopyConstructible<T>
 * CopyAssignable<T>
 */
template<typename T>
void quicksort(T *tab, std::size_t size)
{
    using namespace std::rel_ops;
    using std::swap;
    // QUICK SORT
    Stack<std::pair<uint32_t, uint32_t> > stack;
    stack.push(std::pair<uint32_t, uint32_t>(0, size));
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
        const T selectedValue = tab[position];
        uint32_t less = left;
        uint32_t equal = left;
        for(uint32_t iterator = left; iterator < right; ++iterator) {
            if(tab[iterator] > selectedValue) {
                // DO NOTHING
            } else if(tab[iterator] == selectedValue) {
                swap(tab[equal++], tab[iterator]);
            } else {
                T v = tab[iterator];
                tab[iterator] = tab[equal];
                tab[equal++] = tab[less];
                tab[less++] = v;
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
    insertionSort(tab, size);
#ifdef DEBUG
    // CHECK SORTED
    for(size_t i = 1; i < size; ++i)
        check(tab[i - 1] <= tab[i]);
#endif
}

inline static void solution()
{
    using std::swap;
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        uint_fast32_t n;
        uint_fast16_t p;
        in >> n >> p;
        uint16_t *D = new uint16_t[n];
        uint_fast16_t Dsize = 0;
        for(size_t i = 0; i < n; ++i) {
            uint_fast64_t a;
            in >> a;
            if(a <= p)
                D[Dsize++] = a;
        }
        if(Dsize == 0) {
            out << "0\n";
            continue;
        }
        quicksort(D, Dsize);
        uint32_t *S = new uint32_t[Dsize + 1];
        S[0] = 0;
        for(size_t i = 0; i < Dsize; ++i)
            S[i + 1] = S[i] + D[i];

        bool *B = new bool[p + 1];
        B[0] = true;
        memset(B + 1, 0, sizeof(bool)*p);
        uint_fast16_t result = 0;
        for(; result < Dsize; ++result) {
            bool haveSomeTrue = false;
            for(int_fast16_t i = p; i >= 0; --i) {
                bool ans = false;
                if(B[i]) {
                    uint_fast32_t Aload = i;
                    uint_fast32_t Bload = S[result] - Aload;
                    if(Bload + D[result] <= p)
                        ans = true;
                }
                if((!ans) && (i - D[result] >= 0) && (B[i - D[result]])) {
                    ans = true;
                }
                if(ans) {
                    haveSomeTrue = true;
                }
                B[i] = ans;
            }
            if(!haveSomeTrue)
                break;
        }
        out << result << '\n';

        delete [] D;
        delete [] S;
        delete [] B;
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



