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
    union {
        char stringKey[8];
        uint64_t key;
    };
    int value;

    Entry() : key(0ULL) {}
    Entry(const char *stringKey, int value) : value(value) {
        this->stringKey[0]=stringKey[0];
        this->stringKey[1]=stringKey[1];
        this->stringKey[2]=stringKey[2];
        this->stringKey[3]=stringKey[3];
        this->stringKey[4]=stringKey[4];
        this->stringKey[5]=stringKey[5];
        this->stringKey[6]=stringKey[6];
        this->stringKey[7]=stringKey[7];
    }
};

static Entry *hashTable;
static uint_fast32_t tableSize;
static uint_fast32_t entryCount;
static uint_fast32_t deletedEntryCount;

static uint_fast32_t hashTableSizes[] = {1009, 2011, 4001, 8009, 16001, 32003, 64007, 128021, 256019, 512009, 1024021, 2048003, 4000037, 8000009, 16000057, 32000011, 64000031, 128000003, 256000001, 512000009};
static uint_fast8_t currentPrime = 0;

static inline uint_fast32_t hash1(const char *string)
{
    uint_fast32_t result = 31;
    for(int i = 0; i < 8; ++i, ++string)
        result = result * 131 + *string;
    return result%tableSize;
}

static inline uint_fast32_t hash2(const char *string)
{
    uint_fast32_t result = 13;
    for(int i = 0; i < 8; ++i, ++string)
        result = result * 67 + *string;
    return result;
}

static inline uint_fast32_t iterateInTable(uint_fast32_t position, uint_fast32_t distance)
{
    return (position + distance) % tableSize;
}

static void insert_unchecked(const Entry &entry)
{
    for(uint_fast32_t i = hash1(entry.stringKey),
            d = hash2(entry.stringKey);
            ;
            i = iterateInTable(i, d)) {
        if(hashTable[i].key == 0ULL) {
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

static void resize()
{
    uint_fast32_t newSize = hashTableSizes[currentPrime];
    Entry *newHashTable = new Entry[newSize];
    Entry *i = hashTable, *e = hashTable + tableSize;
    Entry *oldHashTable = hashTable;
    hashTable = newHashTable;
    tableSize = newSize;
    entryCount = 0;
    deletedEntryCount = 0;
    for(; i != e; ++i) {
        if(i->key != 0ULL && i->key != (~(0ULL)))
            insert_unchecked(Entry(i->stringKey, i->value));
    }
    delete [] oldHashTable;

}

static inline void checkSize()
{
    if(entryCount * 2 > tableSize) {
        ++currentPrime;
        resize();
    }
    if(deletedEntryCount * 4 > tableSize)
        resize();
}

static void inline insert(const Entry &entry)
{
    checkSize();
    insert_unchecked(entry);
}

static inline std::pair<Entry *, Entry *> find(const char* stringKey)
{
    Entry *first = 0;
    Entry cmp(stringKey,0);
    for(uint_fast32_t i = hash1(stringKey), d = hash2(stringKey);
            ;
            i = iterateInTable(i, d)) {
        if(first == 0 && hashTable[i].key == (~(0ULL)))
            first = &hashTable[i];
        else if(hashTable[i].key == cmp.key) {
            return std::make_pair(first, &hashTable[i]);
        }
        if(hashTable[i].key == 0ULL)
            return std::make_pair(first, static_cast<Entry *>(0));
    }
}

static inline Entry *deleteKey(const char * stringKey)
{
    checkSize();
    Entry cmp(stringKey,0);
    for(uint_fast32_t i = hash1(stringKey), d = hash2(stringKey);
            ;
            i = iterateInTable(i,d)) {
        if(hashTable[i].key == cmp.key) {
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
    currentPrime=0;
    tableSize = hashTableSizes[currentPrime];
    hashTable = new Entry[tableSize];
    entryCount = 0;
    deletedEntryCount = 0;
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
                std::pair<Entry *, Entry *> entry = find(stringKey);
                if(entry.second)
                    entry.second->value += value;
                else {
                    if(entry.first == 0)
                        insert(Entry(stringKey, value));
                    else {
                        entry.first->key = Entry(stringKey,0).key;
                        entry.first->value = value;
                    }
                }
            } else if(*command == 'D') {
                Entry *entry = deleteKey(stringKey);
                if(entry)
                    out << entry->value << '\n';
                else
                    out << "ERROR\n";
            } else {
                check(*command == 'F');
                Entry *entry = find(stringKey).second;
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
