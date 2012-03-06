//Maciej Poleski
#ifdef DEBUG
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
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
#define check(x) assert(x)
#else
#ifndef NDEBUG
#define NDEBUG
#endif
#define check(x)
#include <iostream>
namespace Wrapper {
std::istream &in=std::cin;
std::ostream &out=std::cout;
}
#endif

#include <tr1/cstdint>
#include <string>
#include <algorithm>

struct Node
{
    Node *next;
    int vertex;

    Node(Node *next, int vertex) : next(next), vertex(vertex) {}
};

struct Vertex
{
    int inDeg;
    Node *nextEdge;

    Vertex() : inDeg(0), nextEdge(0) {}
};

inline static void solution()
{
    using namespace Wrapper;
    std::tr1::uint_fast32_t z;
    in>>z;
    while(z--)
    {
        std::tr1::uint_fast32_t n;
        in>>n;
        Vertex G['Z'-'A'+1];
        bool connection['Z'-'A'+1]['Z'-'A'+1]= {{false}};
        std::string oldWord="";
        for(std::tr1::uint32_t i=0; i<n; ++i)
        {
            std::string word;
            in>>word;
            std::pair<std::string::iterator,std::string::iterator> difference=
                std::mismatch(oldWord.begin(),oldWord.end(),word.begin());
            if(difference.first!=oldWord.end())
            {
                std::tr1::uint_fast8_t from=*(difference.first)-'A';
                std::tr1::uint_fast8_t destination=*(difference.second)-'A';
                check(from!=destination);
                if(!connection[from][destination])
                {
                    connection[from][destination]=true;
                    ++G[destination].inDeg;
                    G[from].nextEdge=new Node(G[from].nextEdge,destination);
                }
            }
            oldWord=word;
        }
        Node *queue=0;
        for(std::tr1::uint_fast8_t i=0; i<'Z'-'A'+1; ++i)
        {
            if(G[i].inDeg==0)
            {
                queue=new Node(queue,i);
            }
        }
        std::string result="";
        while(queue)
        {
            std::tr1::uint8_t currentNode=queue->vertex;
            {
                Node *next=queue->next;
                delete queue;
                queue=next;
            }
            result+=static_cast<char>(currentNode+'A');
            result+=' ';
            for(Node *i=G[currentNode].nextEdge;i;)
            {
                if(--G[i->vertex].inDeg==0)
                    queue=new Node(queue,i->vertex);
                Node *next=i->next;
                delete i;
                i=next;
            }
            G[currentNode].nextEdge=0;
        }
        bool ok=true;
        for(std::tr1::uint_fast8_t i=0; i<'Z'-'A'+1; ++i)
        {
            if(G[i].inDeg!=0)
            {
                out<<"NIE\n";
                ok=false;
                break;
            }
        }
        if(ok)
        {
            out<<result<<'\n';
        }
        else
        {
            for(std::tr1::uint_fast8_t i=0; i<'Z'-'A'+1; ++i)
            {
                for(Node *j=G[i].nextEdge;j;)
                {
                    Node *next=j->next;
                    delete j;
                    j=next;
                }
                G[i].nextEdge=0;
            }
        }
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
