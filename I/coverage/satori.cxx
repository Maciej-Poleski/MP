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

namespace
{
using namespace Wrapper;

struct Coordinates {
    uint16_t x, y;

    Coordinates() {}
    Coordinates(uint16_t x, uint16_t y) : x(x), y(y) {}
};

static char plan[2001][2001];
static int16_t result[2001][2001];
static Coordinates *queue, *queueBegin, *queueEnd = NULL;
static uint_fast16_t n, m;

static inline bool needVisit(uint_fast16_t x, uint_fast16_t y)
{
    if(x < 1 || x > m || y < 1 || y > n ||
            plan[y][x] == '2' || result[y][x] != -1)
        return false;
    return true;
}

static inline bool canWeakVisit(uint_fast16_t x, uint_fast16_t y)
{
    if(x < 1 || x > m || y < 1 || y > n ||
            plan[y][x] != '2' || result[y][x] != -1)
        return false;
    return true;
}

inline static void solution()
{
    std::tr1::uint_fast32_t z;
    in >> z;
    while(z--) {
        delete [] queue;
        in >> n >> m;
        queue = queueBegin = queueEnd = new Coordinates[n * m];
        for(size_t i = 1; i <= n; ++i)
            for(size_t j = 1; j <= m; ++j)
                result[i][j] = -1;
        for(size_t i = 1; i <= n; ++i) {
            in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            for(size_t j = 1; j <= m; ++j) {
                in >> plan[i][j];
                if(plan[i][j] == '1') {
                    *queueEnd++ = Coordinates(j, i);
                    result[i][j] = 0;
                }
            }
        }
        while(queueBegin != queueEnd) {
            Coordinates coord = *queueBegin++;
            if(needVisit(coord.x - 1, coord.y)) {
                result[coord.y][coord.x - 1] = result[coord.y][coord.x] + 1;
                *queueEnd++ = Coordinates(coord.x - 1, coord.y);
            } else if(canWeakVisit(coord.x - 1, coord.y)) {
                result[coord.y][coord.x - 1] = result[coord.y][coord.x] + 1;
            }
            if(needVisit(coord.x + 1, coord.y)) {
                result[coord.y][coord.x + 1] = result[coord.y][coord.x] + 1;
                *queueEnd++ = Coordinates(coord.x + 1, coord.y);
            } else if(canWeakVisit(coord.x + 1, coord.y)) {
                result[coord.y][coord.x + 1] = result[coord.y][coord.x] + 1;
            }
            if(needVisit(coord.x, coord.y - 1)) {
                result[coord.y - 1][coord.x] = result[coord.y][coord.x] + 1;
                *queueEnd++ = Coordinates(coord.x, coord.y - 1);
            } else if(canWeakVisit(coord.x, coord.y - 1)) {
                result[coord.y - 1][coord.x] = result[coord.y][coord.x] + 1;
            }
            if(needVisit(coord.x, coord.y + 1)) {
                result[coord.y + 1][coord.x] = result[coord.y][coord.x] + 1;
                *queueEnd++ = Coordinates(coord.x, coord.y + 1);
            } else if(canWeakVisit(coord.x, coord.y + 1)) {
                result[coord.y + 1][coord.x] = result[coord.y][coord.x] + 1;
            }
        }
        for(size_t i = 1; i <= n; ++i) {
            for(size_t j = 1; j <= m; ++j)
                out << result[i][j] << ' ';
            out << '\n';
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

