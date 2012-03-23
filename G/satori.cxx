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
}

}

#include <string>
#include <algorithm>
#include <limits>
#include <locale>

namespace
{

class InternalNode;

class Node
{
public:
    Node *rightSibling;

protected:
    InternalNode *_parent;
    Wrapper::int32_t _value;

public:
    Node(InternalNode *parent, Wrapper::int32_t value) :
        rightSibling(NULL), _parent(parent), _value(value) {}

    virtual Wrapper::int32_t computeValue() = 0;

    Wrapper::int32_t value() const {
        return _value;
    }

    void setValue(Wrapper::int32_t value) {
        _value = value;
    }

    virtual ~Node() {
        for(Node *i = rightSibling; i != NULL;) {
            Node *next = i->rightSibling;
            i->rightSibling = 0;
            delete i;
            i = next;
        }
    }
};

class InternalNode : public Node
{
public:
    Node *leftChild;

    InternalNode(InternalNode *parent, Wrapper::int32_t value = 0) :
        Node(parent, value), leftChild(NULL) {}

    virtual ~InternalNode() {
        check(leftChild);
        delete leftChild;
    }

    virtual void reflectChangeOfChild(Wrapper::int32_t  oldValue, Wrapper::int32_t  newValue) = 0;
};

class Leaf : public Node
{
public:
    Leaf(InternalNode *parent, Wrapper::int32_t value) : Node(parent, value) {}

    virtual Wrapper::int32_t computeValue() {
        return _value;
    }

    void update(Wrapper::int32_t newValue) {
        if(_value != newValue) {
            Wrapper::int32_t old = _value;
            _value = newValue;
            if(_parent)
                _parent->reflectChangeOfChild(old, newValue);
        }
    }
};

class AddNode : public InternalNode
{
public:
    AddNode(InternalNode *parent) : InternalNode(parent) {}

    virtual Wrapper::int32_t computeValue() {
        check(leftChild);
        Wrapper::int32_t result = 0;
        for(Node *i = leftChild; i; i = i->rightSibling) {
            result += i->computeValue();
        }
        return _value = result;
    }

    virtual void reflectChangeOfChild(Wrapper::int32_t  oldValue, Wrapper::int32_t  newValue) {
        check(oldValue != newValue);
        Wrapper::int32_t result = _value + (newValue - oldValue);
        Wrapper::int32_t old = _value;
        _value = result;
        if(_parent)
            _parent->reflectChangeOfChild(old, result);
    }
};

class NegNode : public InternalNode
{
public:
    NegNode(InternalNode *parent) : InternalNode(parent) {}

    virtual Wrapper::int32_t computeValue() {
        check(leftChild);
        return _value = - (leftChild->computeValue());
    }

    virtual void reflectChangeOfChild(Wrapper::int32_t  oldValue, Wrapper::int32_t  newValue) {
        check(oldValue != newValue);
        (void)oldValue;
        Wrapper::int32_t result = -newValue;
        Wrapper::int32_t old = _value;
        _value = result;
        if(_parent)
            _parent->reflectChangeOfChild(old, result);
    }
};

class MaxNode : public InternalNode
{
public:
    MaxNode(InternalNode *parent) : InternalNode(parent) {}

    virtual Wrapper::int32_t computeValue() {
        check(leftChild);
        Wrapper::int32_t result = std::numeric_limits<int32_t>::min();
        for(Node *i = leftChild; i; i = i->rightSibling) {
            result = std::max(result, i->computeValue());
        }
        return _value = result;
    }

    virtual void reflectChangeOfChild(Wrapper::int32_t  oldValue, Wrapper::int32_t  newValue) {
        check(oldValue != newValue);
        if(newValue > oldValue) {
            if(_value < newValue) {
                Wrapper::int32_t old = _value;
                _value = newValue;
                if(_parent)
                    _parent->reflectChangeOfChild(old, newValue);
            }
        } else {
            if(oldValue == _value) {
                check(leftChild);
                Wrapper::int32_t result = std::numeric_limits<int32_t>::min();
                for(Node *i = leftChild; i; i = i->rightSibling) {
                    result = std::max(result, i->value());
                }
                if(result != _value) {
                    Wrapper::int32_t old = _value;
                    _value = result;
                    if(_parent)
                        _parent->reflectChangeOfChild(old, result);
                }
            }
        }
    }
};

class MinNode : public InternalNode
{
public:
    MinNode(InternalNode *parent) : InternalNode(parent) {}

    virtual Wrapper::int32_t computeValue() {
        check(leftChild);
        Wrapper::int32_t result = std::numeric_limits<int32_t>::max();
        for(Node *i = leftChild; i; i = i->rightSibling) {
            result = std::min(result, i->computeValue());
        }
        return _value = result;
    }

    virtual void reflectChangeOfChild(Wrapper::int32_t  oldValue, Wrapper::int32_t  newValue) {
        check(oldValue != newValue);
        if(newValue < oldValue) {
            if(_value > newValue) {
                Wrapper::int32_t old = _value;
                _value = newValue;
                if(_parent)
                    _parent->reflectChangeOfChild(old, newValue);
            }
        } else {
            if(oldValue == _value) {
                check(leftChild);
                Wrapper::int32_t result = std::numeric_limits<int32_t>::max();
                for(Node *i = leftChild; i; i = i->rightSibling) {
                    result = std::min(result, i->value());
                }
                if(_value != result) {
                    Wrapper::int32_t old = _value;
                    _value = result;
                    if(_parent)
                        _parent->reflectChangeOfChild(old, result);
                }
            }
        }
    }
};

class LeafManager
{
public:
    typedef Leaf **iterator;
public:
    LeafManager() {}

    ~LeafManager() {
        delete [] _leaves;
    }

    void reinitialize(Wrapper::uint_fast32_t maxCount) {
        _count = 0;
        delete [] _leaves;
        _leaves = new Leaf*[maxCount];
    }

    Leaf *newLeaf(InternalNode *parent, Wrapper::int32_t value = 0) {
        return _leaves[_count++] = new Leaf(parent, value);
    }

    void update(Wrapper::uint_fast32_t leaf, Wrapper::int32_t value) {
        _leaves[leaf]->update(value);
    }

    iterator begin() {
        return _leaves;
    }

    iterator end() {
        return &_leaves[_count];
    }

private:
    Wrapper::uint32_t _count;
    Leaf **_leaves;
} leaves;

static inline Node *parseInput(InternalNode *parent)
{
    using namespace Wrapper;
    typedef std::char_traits<char> traits_type;
    typedef traits_type::int_type int_type;
    Node *result = 0;
    Node **next = &result;
    while(true) {
        int_type input = in.get();
        if(input == traits_type::eof() || traits_type::to_char_type(input) == ')'
                || std::isspace(traits_type::to_char_type(input), std::locale::classic()))
            break;
        else if(traits_type::to_char_type(input) == 'x') {
            *next = leaves.newLeaf(parent);
            next = &((*next)->rightSibling);
        } else {
            check(traits_type::to_char_type(input) == '(');
            input = in.get();
            InternalNode *handle;
            if(traits_type::to_char_type(input) == '+')
                handle = new AddNode(parent);
            else if(traits_type::to_char_type(input) == '-')
                handle = new NegNode(parent);
            else if(traits_type::to_char_type(input) == '>')
                handle = new MaxNode(parent);
            else {
                check(traits_type::to_char_type(input) == '<');
                handle = new MinNode(parent);
            }
            *next = handle;
            handle->leftChild = parseInput(handle);
            next = &((*next)->rightSibling);
        }
    }
    return result;
}

inline static void solution()
{
    using namespace Wrapper;
    std::tr1::uint_fast32_t z;
    in >> z;
    Node *tree = 0;
    while(z--) {
        std::tr1::uint_fast32_t p, r;
        in >> p >> r;
        leaves.reinitialize(p);
        delete tree;
        while(in.get() != '\n');
        tree = parseInput(0);
        for(LeafManager::iterator i = leaves.begin(), e = leaves.end(); i != e; ++i) {
            int32_t o;
            in >> o;
            (*i)->setValue(o);
        }
        out << tree->computeValue() << '\n';
        while(r--) {
            uint_fast32_t leaf;
            int32_t value;
            in >> leaf >> value;
            leaves.update(leaf, value);
            out << tree->value() << '\n';
        }
    }
#ifdef DEBUG
    delete tree;     // Silence valgrind
#endif
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
