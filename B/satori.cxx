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

const int maxN=10000000;

int n,k;
int *books;

inline static bool isCapacityEnough(const long capacity)
{
    long capacityLeft=0;
    int transportsLeft=k;
    for(int i=0;i<n;++i)
    {
        if(capacityLeft<books[i])
        {
            if(transportsLeft>0)
            {
                capacityLeft=capacity;
                --transportsLeft;
            }
            else
                return false;
        }
        if(capacityLeft<books[i])
            return false;
        capacityLeft-=books[i];
    }
    return true;
}

inline static void solution()
{
    using namespace Wrapper;
    books=new int[maxN];
    int z;
    in>>z;
    while(z--)
    {
        in>>n>>k;
        long L=0;
        long R=0;
        for(int *i=books,*e=books+n; i!=e; ++i)
        {
            in>>*i;
            R+=*i;
        }
        ++R;
        while(L<R)
        {
            long S=(L+R)/2;
            if(isCapacityEnough(S))
                R=S;
            else
                L=S+1;
        }
        out<<L<<'\n';
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
