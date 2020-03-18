#ifndef __AM_GRAPH_H__
#define __AM_GRAPH_H__

#include <limits.h>
#include "random_generator.hpp"

class graph
{
protected:
    int**    m_edge;
    int      no_vert;
    int* dist;
    int* prev_node;
    
public:
    graph(int);
    ~graph();
    
    int get_no_of_vertices()
    { return no_vert; }
    
    void output();
    void random_graph(int);
    void print(int*);
    void init_single_source(int);
    void relax(int, int);
    bool bellman_ford(int);
    int** floyd_warshall(int);
    void remove_matrix(int**);

protected:
    void initialize();
    void permutation(int*, int);
};



#endif
