#include <iostream>


#include "graph.hpp"
#include "random_generator.hpp"

using namespace std;

int main(int argc, char* argv[])
{
//    random_generator* rg = nullptr;
    
    int n,m;
    
    n=5;m=5;
    graph g(n);
    
    cout<<"Initialize the graph:"<<endl;
    g.output();
    
    /*
     * Random generate m edges and update the graph
     */
//    g.random_graph(m);
//    cout<<"Update the graph:"<<endl;
//    g.output();

    /*
     * Run bellman_ford
     */
    if(g.bellman_ford(0))
    {
        cout<<"FALSE"<<endl;
    }
    else
        cout<<"TRUE"<<endl;
    /*
     * Run floyd_warshall
     */
//    g.floyd_warshall(n);

    
    return 0;
}

