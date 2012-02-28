//Maciej Poleski
#ifdef DEBUG
#include <iostream>
#include <fstream>
#include <cstdlib>
namespace Wrapper {
    std::ifstream in;
    std::ofstream out;
}
void init(int argc,char**argv)
{
    if(argc!=3)
    {
        std::cerr<<"Potrzeba dokładnie dwóch argumentów\n";
        std::abort();
    }
    Wrapper::in.open(argv[1]);
    Wrapper::out.open(argv[2]);
}
#else
#ifndef NDEBUG
#define NDEBUG
#endif
#include <iostream>
namespace Wrapper {
    std::istream &in=std::cin;
    std::ostream &out=std::cout;
}
#endif

void solution()
{
    int a;
    using namespace Wrapper;
    in>>a;
    out<<"Hello World\n";

}

int main(int argc,char**argv)
{
    std::ios_base::sync_with_stdio(false);
#ifdef DEBUG
    init(argc,argv);
#endif
    solution();
    return 0;
}