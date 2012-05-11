#include <iostream>
#include <fstream>
#include <utility>
#include <functional>
#include <random>

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3) {
        cerr << "Potrzeba dokładnie dwóch argumentów: <wejście> <n>\n";
        abort();
    }
    ofstream out(argv[1]);
    size_t n = stoul(argv[2]);
    size_t m = n;
    out << 1 << '\n' << n << ' ' << m << '\n';
    mt19937 engine(404);
    uniform_int_distribution<uint32_t> distribution(0, 1000);
    auto generator = bind(distribution, engine);
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < m; ++j) {
            out << generator() << ' ';
        }
        out << '\n';
    }
    uniform_int_distribution<uint32_t> coordDistributionX(1, n);
    uniform_int_distribution<uint32_t> coordDistributionY(1, m);
    out << coordDistributionX(engine) << ' ' << coordDistributionY(engine) << ' '
        << coordDistributionX(engine) << ' ' << coordDistributionY(engine) << '\n';
}
