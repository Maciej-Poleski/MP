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
#include <cmath>

double X,Y,C;

double getPropositionC(double W)
{
    double a=std::sqrt(X*X - W*W);
    double b=std::sqrt(Y*Y - W*W);
    return (a*b)/(a+b);
}

void solution()
{
    using namespace Wrapper;
    int z;
    in>>z;
    while(z--)
    {
        in>>X>Y>>C;
        
    }
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