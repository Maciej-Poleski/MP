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

inline static void solution()
{
    using std::swap;
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        uint_fast16_t n;
        in >> n;
        MinMaxHeap<uint32_t, uint32_t> heap;
        MinMaxHeap<uint32_t, uint32_t> minHeap;
        MinMaxHeap<uint32_t, uint32_t> maxHeap;
        uint_fast64_t result = 0LL;
        bool firstStage = true;
        while(n != 0) {
            uint_fast32_t k;
            in >> k;
            if(firstStage) {
                if(k + heap.size() > 2 * n) {
                    while(heap.size() < 2 * n) {
                        uint32_t v;
                        in >> v;
                        heap.push(v);
                        --k;
                    }
                    for(size_t i = 0; i < n; ++i) {
                        minHeap.push(heap.popMin());
                    }
                    for(size_t i = 0; i < n; ++i) {
                        maxHeap.push(heap.popMax());
                    }
                    heap.clean();
                    firstStage = false;
                    while(k--) {
                        uint32_t v;
                        in >> v;
                        check(!minHeap.isEmpty());
                        check(!maxHeap.isEmpty());
                        if(v < minHeap.max()) {
                            minHeap.popMax();
                            minHeap.push(v);
                        } else if(v > maxHeap.min()) {
                            maxHeap.popMin();
                            maxHeap.push(v);
                        }
                    }
                } else {
                    while(k--) {
                        uint32_t v;
                        in >> v;
                        heap.push(v);
                    }
                }
            } else {
                while(k--) {
                    uint32_t v;
                    in >> v;
                    check(!minHeap.isEmpty());
                    check(!maxHeap.isEmpty());
                    if(v < minHeap.max()) {
                        minHeap.popMax();
                        minHeap.push(v);
                    } else if(v > maxHeap.min()) {
                        maxHeap.popMin();
                        maxHeap.push(v);
                    }
                }
            }
            if(firstStage) {
                result += heap.popMax() - heap.popMin();
            } else {
                result += maxHeap.popMax() - minHeap.popMin();
            }
            --n;
        }
        out << result << '\n';
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


