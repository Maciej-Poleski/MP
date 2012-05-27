#include <iostream>
#include <fstream>
#include <random>
#include <utility>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc,char**argv)
{
    if(argc!=4)
    {
        cerr<<argv[0]<<" [output] [n] [k]\n";
        abort();
    }
    ofstream out(argv[1]);
    uint32_t n=stoul(argv[2]);
    uint32_t k=stoul(argv[3]);
    mt19937 engine(404);
    uniform_int_distribution<int32_t> pointDistribution(-1000,1000);
    uniform_int_distribution<uint32_t> distanceDistribution(0,400);
    auto point=bind(pointDistribution,engine);
    auto distance=bind(distanceDistribution,engine);
    out<<1<<'\n';
    out<<n<<'\n';
    while(n--)
    {
        int32_t x1,y1,x2,y2;
        x1=point();
        y1=point();
        x2=x1+distance();
        y2=y1+distance();
        out<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<'\n';
    }
    out<<k<<'\n';
    vector<pair<int32_t,int32_t>> points;
    while(k--)
    {
        int32_t x,y;
        x=point();
        y=point();
        points.push_back(make_pair(x,y));
    }
    sort(points.begin(),points.end());
    for(auto pair : points)
    {
        out<<pair.first<<' '<<pair.second<<'\n';
    }
    return 0;
};
