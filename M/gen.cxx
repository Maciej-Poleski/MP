#include <iostream>
#include <fstream>
#include <random>
#include <functional>
#include <string>

using namespace std;

int main(int argc, char**argv)
{
    if(argc!=3)
    {
        clog<<"Potrzeba dwóch argumentów <wyjście> <n>\n";
        abort();
    }
    ofstream out(argv[1]);
    uint32_t n=stoul(argv[2]);
    out<<1<<'\n'<<n<<'\n';
    mt19937 engine;
    uniform_int_distribution<int32_t> distribution(numeric_limits< int32_t >::min(),numeric_limits< int32_t >::max());
    //uniform_int_distribution<int32_t> distribution(0,1000);
    auto gen=bind(distribution,engine);
    for(size_t i=0;i<n;++i)
        out<<gen()<<' ';
    out<<'\n';
    return 0;
}
