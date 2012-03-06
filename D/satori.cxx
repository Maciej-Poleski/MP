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
    enum
    {
        next=0,
        back=1
    };
    std::string name;
    Node* near[2];

    Node(const std::string &name) : name(name) {
        near[0]=near[1]=0;
    }
};

struct Train
{
    std::string name;
    Node* front;
    Node *back;
    Train *nextTrain;

    Train(const std::string &name, Train *next) : name(name),
        front(0), back(0), nextTrain(next) {}
};

Train *trains;

inline static void newCommand(const std::string &trainName, const std::string &name)
{
    Train *train=new Train(trainName,trains);
    train->front=train->back=new Node(name);
    trains=train;
}

inline static void backCommand(const std::string &trainName, const std::string &name)
{
    Train *train;
    for(train=trains; train; train=train->nextTrain)
        if(train->name==trainName)
            break;
    Node *node=new Node(name);
    check(train->back);
    int index=(train->back->near[1]==0);
    node->near[Node::next]=0;
    node->near[Node::back]=train->back;
    train->back->near[index]=node;
    train->back=node;
}

inline static void frontCommand(const std::string &trainName, const std::string &name)
{
    Train *train;
    for(train=trains; train; train=train->nextTrain)
        if(train->name==trainName)
            break;
    check(train->front);
    Node *node=new Node(name);
    int index=(train->front->near[1]==0);
    node->near[Node::back]=0;
    node->near[Node::next]=train->front;
    train->front->near[index]=node;
    train->front=node;
}

inline static void printCommand(const std::string &trainName)
{
    Train *train;
    for(train=trains; train; train=train->nextTrain)
        if(train->name==trainName)
            break;
    using namespace Wrapper;
    out<<'"'<<train->name<<"\":\n";
    Node *node=train->front;
    out<<node->name;
    Node *prev=0;
    while(true)
    {
        int index=(node->near[0]==prev);
        prev=node;
        node=node->near[index];
        if(node==0)
            break;
        out<<"<-"<<node->name;
    }
    out<<'\n';
}

inline static void reverseCommand(const std::string &trainName)
{
    Train *train;
    for(train=trains; train; train=train->nextTrain)
        if(train->name==trainName)
            break;
    std::swap(train->front,train->back);
}

inline static void unionCommand(const std::string &train1Name, const std::string &train2Name)
{
    Train *train1;
    for(train1=trains; train1; train1=train1->nextTrain)
        if(train1->name==train1Name)
            break;
    Train **train2;
    for(train2=&trains; *train2; train2=&((*train2)->nextTrain))
        if((*train2)->name==train2Name)
            break;
    train1->back->near[train1->back->near[1]==0]=(*train2)->front;
    (*train2)->front->near[(*train2)->front->near[1]==0]=train1->back;
    train1->back=(*train2)->back;
    Train *ptr=*train2;
    *train2=(*train2)->nextTrain;
    delete ptr;
}

inline static void delfrontCommand(const std::string &train2Name, const std::string &train1Name)
{
    Train *train1;
    for(train1=trains; train1; train1=train1->nextTrain)
        if(train1->name==train1Name)
            break;
    check(train1);
    if(train1->front==train1->back)
    {
        train1->name=train2Name;
    }
    else
    {
        Node *node=train1->front;
        Node *next=node->near[node->near[0]==0];
        next->near[next->near[1]==node]=0;
        train1->front=next;
        node->near[0]=node->near[1]=0;
        Train *train2=new Train(train2Name,trains);
        train2->back=train2->front=node;
        trains=train2;
    }
}

inline static void delbackCommand(const std::string &train1Name, const std::string &train2Name)
{
    Train *train1;
    for(train1=trains; train1; train1=train1->nextTrain)
        if(train1->name==train1Name)
            break;
    check(train1);
    if(train1->front==train1->back)
    {
        train1->name=train2Name;
    }
    else
    {
        Node *node=train1->back;
        Node *next=node->near[node->near[0]==0];
        next->near[next->near[1]==node]=0;
        train1->back=next;
        node->near[0]=node->near[1]=0;
        Train *train2=new Train(train2Name,trains);
        train2->back=train2->front=node;
        trains=train2;
    }
}

inline static void solution()
{
    using namespace Wrapper;
    std::tr1::uint_fast32_t z;
    in>>z;
    while(z--)
    {
        std::tr1::uint_fast32_t n;
        in>>n;
        trains=0;
        while(n--)
        {
            std::string command;
            in>>command;
            if(command[0]=='N')
            {
                check(command=="NEW");
                std::string arg1,arg2;
                in>>arg1>>arg2;
                newCommand(arg1,arg2);
            }
            else if(command[0]=='B')
            {
                check(command=="BACK");
                std::string arg1,arg2;
                in>>arg1>>arg2;
                backCommand(arg1,arg2);
            }
            else if(command[0]=='F')
            {
                check(command=="FRONT");
                std::string arg1,arg2;
                in>>arg1>>arg2;
                frontCommand(arg1,arg2);
            }
            else if(command[0]=='P')
            {
                check(command=="PRINT");
                std::string arg1;
                in>>arg1;
                printCommand(arg1);
            }
            else if(command[0]=='R')
            {
                check(command=="REVERSE");
                std::string arg1;
                in>>arg1;
                reverseCommand(arg1);
            }
            else if(command[0]=='U')
            {
                check(command=="UNION");
                std::string arg1,arg2;
                in>>arg1>>arg2;
                unionCommand(arg1,arg2);
            }
            else if(command[3]=='F')
            {
                check(command=="DELFRONT");
                std::string arg1,arg2;
                in>>arg1>>arg2;
                delfrontCommand(arg1,arg2);
            }
            else
            {
                check(command=="DELBACK");
                std::string arg1,arg2;
                in>>arg1>>arg2;
                delbackCommand(arg1,arg2);
            }
        }
        Train *train;
        for(train=trains; train;)
        {
            Node *node=train->front;
            Node *old=0;
            while(node)
            {
                Node *next=node->near[node->near[0]==old];
                old=node;
                delete node;
                node=next;
            }
            Train *next=train->nextTrain;
            delete train;
            train=next;
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
