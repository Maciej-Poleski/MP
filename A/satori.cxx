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

inline static double getPropositionC(const double W)
{
    double a=std::sqrt(X*X - W*W);
    double b=std::sqrt(Y*Y - W*W);
    return (a*b)/(a+b);
}

inline static void solution()
{
    using namespace Wrapper;
    out.precision(3);
    int z;
    in>>z;
    while(z--)
    {
        in>>X>>Y>>C;
        double L=0.;
        double R=std::min(X,Y);
        while(R-L>=0.0001)
        {
            double Wp=(L+R)/2.;
            double Cp=getPropositionC(Wp);
            if(Cp>C)
                L=Wp;
            else
                R=Wp;
        }
        out<<std::fixed<<(R+L)/2<<'\n';
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