
#include "graph.hpp"
#include <list>
#include <iostream>
#include <limits.h>

using namespace std;


/*
 * constructor/destructor
 */
graph::graph(int n)
{
    no_vert = (n > 0) ? n : 1;
    
    dist=new int[n];
    prev_node=new int[n];
    /*
     * allocate adjacency matrix
     */
    m_edge = new int*[no_vert];
    for (int i = 0; i < no_vert; i++)
        m_edge[i] = new int[no_vert];
    
    initialize();
}

graph::~graph()
{
    /*
     * delete nil element and all other allocated nodes
     */
    for (int i = 0; i < no_vert; i++)
        delete[] m_edge[i];
    delete[] m_edge;
}


void graph::initialize()
{
    /*
     * initialize adjacency matrix
     * -> use infinity to allow 0 weight edges
     */
    for (int i = 0; i < no_vert; i++)
        for (int j = 0; j < no_vert; j++)
            m_edge[i][j] = INT_MAX;
//    /*
//     * test case for bellman-ford
//     */
//    m_edge[0][1] = 3;
//    m_edge[1][2] = 2;
//    m_edge[2][3] = 4;
//    m_edge[3][2] = -1;
//    m_edge[1][3] = 8;
//    m_edge[0][2] = 1;
    
    /*
     * test case for floyd_warshall
     */
    m_edge[0][1] = 3;
    m_edge[0][2] = 8;
    m_edge[0][4] = -4;
    m_edge[1][4] = 7;
    m_edge[1][3] = 1;

    m_edge[2][1] = 4;

    m_edge[3][2] = -5;
    m_edge[3][0] = 2;
    m_edge[4][3] = 6;
    
    

    
}
//max m-1 edges for non-cyclic path
void graph::permutation(int* perm, int n)
{
    random_generator rg;
    int p_tmp, p_pos;
    
    for (int i = 0; i < n; i++)
        perm[i] = i;
    
    for (int i = 0; i < n; i++)
    {
        rg >> p_pos;//a random position
        p_pos = (p_pos % (n - i)) + i;
        
        p_tmp = perm[i];
        perm[i] = perm[p_pos];
        perm[p_pos] = p_tmp;//update perm
    }
}

void graph::output()
{
    cout << "[";
    for (int i = 0; i < no_vert; i++)
    {
        cout << "[\t";
        for (int j = 0; j < no_vert; j++)
            if (m_edge[i][j] == INT_MAX)
                cout << "Inf\t";
            else
                cout << m_edge[i][j] << "\t";
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

void graph::random_graph(int m)
{
    int w;
    static int n=10;
    random_generator rg;
    
    int* perm=new int[no_vert];
    int count=0;
    
    while (count<m)
    {
        permutation(perm,no_vert);
        for (int i=0;i<no_vert-1;i++)
        {
//            cout<<" begin at "<<count<<" "<<i<<"->"<<i+1<<" "<<m_edge[perm[i]][perm[i+1]]<<" ";
            if(m_edge[perm[i]][perm[i+1]]==INT_MAX)
            {
                rg>>w;
                w=(w%(2*n+1)-n);//scale w to a small number
                m_edge[perm[i]][perm[i+1]]=w;
                count++;
//                cout<<"update "<<m_edge[perm[i]][perm[i+1]]<<" ";
                if (count==m)
                {
                    break;
                }
            }
//            cout<<endl;
        }
    }
    delete[] perm;
}

void graph::init_single_source(int s)
{
    for (int i=0;i<no_vert;i++)
    {
        dist[i]=INT_MAX;
        prev_node[i]=NULL;
    }
    dist[s]=0;
}

void graph::relax(int u,int v)
{
    if (dist[v] > dist[u] + m_edge[u][v])
    {
        dist[v]=dist[u] + m_edge[u][v];
        prev_node[v]=u;
    }
//    cout<<"u="<<u<<",v="<<v<<",dist["<<v<<"] "<<dist[v]<<" ";
//    cout<<"prev_node["<<v<<"]: "<<prev_node[v]<<endl;
}


bool graph::bellman_ford(int s)
{
    init_single_source(s);
    for(int l=1;l<no_vert-1;l++)
    {
        for (int i=0;i<no_vert;i++)
            for (int j=0;j<no_vert;j++)
                if (m_edge[i][j]!=INT_MAX)
                {
                    relax(i,j);
                }
    }

    for (int j=0;j<no_vert;j++)
    {
        for (int k=0;k<no_vert;k++)
        {
            if (m_edge[j][k]==INT_MAX)
            {
                continue;
            }
            else if(dist[k]>dist[j]+m_edge[j][k])
            {
                //if negative-weight cycle appears
                cout<<"Have negative-weight cycle."<<endl;
                cout<<"Processor of each node: "<<endl;
                print(prev_node);
                cout<<endl;
                cout<<"Distance for each node:"<<endl;
                print(dist);
                cout<<endl;
                return false;
            }
        }
    }
    //non-negative-weight cycle
    cout<<"Non-negative-weight cycle."<<endl;
    cout<<"Processor of each node: "<<endl;
    print(prev_node);
    cout<<endl;
    cout<<"Distance for each node:"<<endl;
    print(dist);
    cout<<endl;
    return true;
}

void graph::print(int* p)
{
    for (int i=0;i<no_vert;i++)
        cout<<p[i]<<" ";
}

int** graph::floyd_warshall(int n)
{
    int** D=new int*[no_vert];//min distance between nodes
    int** Pie=new int*[no_vert];//intermediate(predecessor) node
    
    for (int i = 0; i < no_vert; i++)
        D[i] = new int[no_vert];
    
    for (int i = 0; i < no_vert; i++)
        Pie[i] = new int[no_vert];
    
    /*
     *initialize D and Pie
     */
    for (int i=0;i<no_vert;i++)//let D(k) =d[i][j](k) be a new n*n matrix
    {
        for (int j=0;j<no_vert;j++)
        {
            D[i][j]=INT_MAX;
            Pie[i][j]=-100;
            if (m_edge[i][j]!=INT_MAX)
            {
                D[i][j]=m_edge[i][j];
                Pie[i][j]=i;//update pie
//                cout<<"edge= "<<m_edge[i][j]<<", pie= "<<Pie[i][j]<<endl;
            }
        }
         D[i][i]=0;//set diagonal
         Pie[i][i]=-100;
    }

    for (int k = 0; k < no_vert; k++)
        for (int i=0;i<no_vert;i++)
            for (int j = 0; j < no_vert; j++)
            {
                if (D[i][k]==INT_MAX || D[k][j]==INT_MAX)
                {
                    continue;
                }
//                cout<<"D["<<i<<"]["<<j<<"]= "<<D[i][j]<<", D["<<i<<"]["<<k<<"]= "<<D[i][k]<<", D["<<k<<"]["<<j<<"]= "<<D[k][j]<<endl;
                else if (D[i][j]>D[i][k]+D[k][j])
                {
                    D[i][j]=D[i][k]+D[k][j];
                    //                    cout<<"new D["<<i<<"]["<<j<<"]= "<<D[i][j]<<endl;
                    Pie[i][j]=Pie[k][j];
                }
            }


    /*
     *print output D
     */
    cout<<"The Distance matrix is:"<<endl;
    cout << "[";
    for (int i = 0; i < no_vert; i++)
    {
        cout << "[\t";
        for (int j = 0; j < no_vert; j++)
            if (D[i][j] == INT_MAX)
                cout << "Inf\t";
            else
                cout << D[i][j] << "\t";
        cout << "]" << endl;
    }
    cout << "]" << endl;
    
    /*
     *print output Pie
     */
    cout<<"The predecessor matrix is:"<<endl;
    cout << "[";
    for (int i = 0; i < no_vert; i++)
    {
        cout << "[\t";
        for (int j = 0; j < no_vert; j++)
            if (Pie[i][j] == -100)
                cout << "Nil\t";
            else
                cout << Pie[i][j] << "\t";
        cout << "]" << endl;
    }
    cout << "]" << endl;
    
    remove_matrix(D);
    remove_matrix(Pie);
    return D;
}

void graph::remove_matrix(int** P)
{
    for (int i=0;i<no_vert;i++)
        delete[] P[i];
    delete[] P;
}
