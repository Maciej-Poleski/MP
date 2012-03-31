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
using namespace Wrapper;
struct Entry {
    uint64_t key;
    int value;

    Entry() : key(0ULL) {}
    Entry(uint64_t key, int value) : key(key), value(value) {}
};

Entry *hashTable;
uint32_t tableSize;
uint32_t entryCount;
uint32_t deletedEntryCount;
uint32_t mask;

uint64_t asNumber(const char *string)
{
    return *reinterpret_cast<const uint64_t *>(string);
}
#define PHI 0.6180339887498948482045868343656381177203091798057628
const long double phi = PHI;
const long double phi2 = phi *phi;

static inline uint32_t hash1(uint_fast32_t m, uint64_t k)
{
    return static_cast<uint32_t>(m * (k * phi - static_cast<uint64_t>(k * phi)));
}

static inline uint32_t hash2(uint_fast32_t m, uint64_t k)
{
    return static_cast<uint32_t>(m * (k * phi2 - static_cast<uint64_t>(k * phi2))) | 1;
}

static void insert_unchecked(const Entry &entry)
{
    for(uint_fast32_t i = hash1(tableSize, entry.key),
            d = hash2(tableSize, entry.key);
            ;
            i = (i + d)&mask) {
        if(hashTable[i].key == 0UL) {
            hashTable[i] = entry;
            ++entryCount;
            break;
        } else if(hashTable[i].key == (~(0ULL))) {
            hashTable[i] = entry;
            --deletedEntryCount;
            break;
        }
    }
}

static void resize(uint32_t newSize)
{
    check(__builtin_popcount(newSize) == 1);
    check(newSize >= tableSize);
    check(newSize == tableSize * 2);
    Entry *newHashTable = new Entry[newSize];
    Entry *i = hashTable, *e = hashTable + tableSize;
    Entry *oldHashTable = hashTable;
    hashTable = newHashTable;
    tableSize = newSize;
    entryCount = 0;
    deletedEntryCount = 0;
    mask = (mask << 1) | 1;
    for(; i != e; ++i) {
        if(i->key != 0ULL && i->key != (~(0ULL)))
            insert_unchecked(Entry(i->key, i->value));
    }
    delete [] oldHashTable;

}

static inline void checkSize()
{
    if(entryCount * 2 > tableSize)
        resize(tableSize * 2);
    if(deletedEntryCount * 4 > tableSize)
        resize(tableSize);
}

static void inline insert(const Entry &entry)
{
    checkSize();
    insert_unchecked(entry);
}

static inline std::pair<Entry *, Entry *> find(uint64_t key)
{
    Entry *first = 0;
    for(uint_fast32_t i = hash1(tableSize, key), d = hash2(tableSize, key);
            ;
            i = (i + d)&mask) {
        if(first == 0 && hashTable[i].key == (~(0ULL)))
            first = &hashTable[i];
        else if(hashTable[i].key == key) {
            return std::make_pair(first, &hashTable[i]);
        }
        if(hashTable[i].key == 0ULL)
            return std::make_pair(first, static_cast<Entry *>(0));
    }
}

static inline Entry *deleteKey(uint64_t key)
{
    checkSize();
    for(uint_fast32_t i = hash1(tableSize, key), d = hash2(tableSize, key);
            ;
            i = (i + d)&mask) {
        if(hashTable[i].key == key) {
            hashTable[i].key = ~0ULL;
            ++deletedEntryCount;
            return &hashTable[i];
        }
        if(hashTable[i].key == 0ULL)
            return 0;
    }
}

static inline void clear()
{
    entryCount = 0;
    deletedEntryCount = 0;
    for(Entry *i = hashTable, *e = hashTable + tableSize; i != e; ++i)
        i->key = 0ULL;
}


inline static void solution()
{
    //tableSize = 4;
    tableSize = 1024;
    hashTable = new Entry[tableSize];
    entryCount = 0;
    deletedEntryCount = 0;
    //mask = 3;
    mask = 1023;
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        clear();
        uint_fast64_t n;
        in >> n;
        char command[7];
        char stringKey[9];
        int value;
        while(n--) {
            in >> command >> stringKey;
            if(*command == 'I') {
                in >> value;
                std::pair<Entry *, Entry *> entry = find(asNumber(stringKey));
                if(entry.second)
                    entry.second->value += value;
                else {
                    if(entry.first == 0)
                        insert(Entry(asNumber(stringKey), value));
                    else {
                        entry.first->key = asNumber(stringKey);
                        entry.first->value = value;
                    }
                }
            } else if(*command == 'D') {
                Entry *entry = deleteKey(asNumber(stringKey));
                if(entry)
                    out << entry->value << '\n';
                else
                    out << "ERROR\n";
            } else {
                check(*command == 'F');
                Entry *entry = find(asNumber(stringKey)).second;
                if(entry)
                    out << entry->value << '\n';
                else
                    out << "0\n";
            }
        }
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
