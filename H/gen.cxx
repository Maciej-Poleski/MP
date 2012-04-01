#include <iostream>
#include <string>
#include <utility>
#include <random>
#include <cstdint>
#include <functional>

int main(int argc,char**argv)
{
    if(argc!=2)
    {
        std::cout<<argv[0]<<" [ilosc]\n";
        std::abort();
    }
    std::mt19937 engine;
    std::uniform_int_distribution<char> charGenerator('A','Z');
    std::uniform_int_distribution<int> intGenerator(0,10);
    auto nextChar=std::bind(charGenerator,engine);
    auto nextInt=std::bind(intGenerator,engine);

    uint_fast64_t n=atoi(argv[1]);
    std::cout<<1<<'\n'<<n<<'\n';
    while(n--)
    {
        std::string name;
        for(uint_fast8_t i=0;i<8U;++i)
        {
            name+=nextChar();
        }
        std::cout<<"INSERT "<<name<<' '<<nextInt()<<'\n';
    }
}