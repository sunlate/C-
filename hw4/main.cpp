//
//  main.cpp
//  hw4
//
//  Created by 孙蕾 on 4/14/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "dynprog.hpp"
#include "timer.hpp"
#include "random_generator.hpp"

int main(int argc, char* argv[])
{
    random_generator rg;
    timer t;
    int n, m,alph;
    int** H;
    char** P;
    
    if (argc > 1)
    {
        n = atoi(argv[1]);
        n = (n < 1) ? 1 : n;
    }
    else
    {
        cout << "hw4: [n] [m] " << endl;
        cout << "[n]  size of the random char array X" << endl;
        cout << "[m]  size of the random char array Y" << endl;
        cout << "[alph]  available random charactors from 'a'(EX: 4 means a,b,c,d)" << endl;
        cout << endl;
        return 0;
    }

    if (argc > 2)
    {
        m = atoi(argv[2]);
        m = (n < 0) ? 0 : m;
    }
    else
        m = 0;

    if (argc > 3)
        alph = atoi(argv[3]);
    else
        alph = 4;
    
    /*
     * create input array random
     * depending on program argument
     * -> input_array is allocated!
     */
    random_generator::seed();
    char* x=rg.random_string_m(n, alph);
    char* y=rg.random_string_m(m, alph);
    /*
     * test case1：HW4 part4
     */
//    char x[]={'d','c','d','c','b','a','c','b','b','b'};
//    char y[]={'a','c','d','c','c','a','b','d','b','b'};
//    char x[]={'d','c','d'};
//    char y[]={'a','c','d'};
    /*
     * test case2:Example1
     */
//    char x[]={'a','b','a','b','a','b','d','a'};
//    char y[]={'a','c','b','a','b','a','b','a'};
    /*
     * test case3:Example2
     */
//    char x[]={'c','a','c','a','c','c','c','b','a','b'};
//    char y[]={'b','c','c','a','d','a','a','d','c','c'};
    /*
     * test case4:Example3
     */
//    char x[]={'c','d','b','a','a','b','b','d','c','a'};
//    char y[]={'c','a','d','c','a','c','c','a','b','d'};
    
    
    //allocate H[n][m] and P[n][m] matrix
    H= new int* [n+1];
    P= new char* [n+1];
    
    for (int i=0;i<n+1;i++)
    {
        H[i]=new int[m+1];
        P[i]=new char[m+1];
    }
    
    /*
     * output initial string of X and Y for debugging purposes
     */
    cout<<"Initialize array of string X: "<<endl;
    cout<<x;

    cout<<endl;
    
    cout<<"Initialize array of string Y: "<<endl;
    cout<<y;

    cout<<endl;
    
    /*
     * run bottom-up smith waterman algorithm
     */
//    t.start();
//    smith_waterman_bottomup(x, y, n, m, H, P);
//    t.stop();
//    cout << "Timer (sort): " << t << endl;
    
    /*
     * run top-down smith waterman algorithm
     */
    t.start();
    smith_waterman_topdown(x, y, n, m, H,P);
    t.stop();
    cout << "Timer (sort): " << t << endl;
    
    
    
    /*
     * print the matrix of H for debug purpose
     */
    cout<<"H matrix is "<<endl;
    for (int i=0;i<=n;i++)
    {
        for (int j=0; j<=m;j++)
            cout<<H[i][j]<<"    ";
        cout<<endl;
    }
    
    /*
     * print the matrix of P for debug purpose
     */
    cout<<"P matrix is "<<endl;
    for (int i=0;i<=n;i++)
    {
        for (int j=0; j<=m;j++)
            cout<<P[i][j]<<"    ";
        cout<<endl;
    }
    
    
    /*
     * print the matching sequence of X'
     */
    cout<<"print the matching sequence of X': "<<endl;
    print_seq_aligh_X(x,P,n,m);
    cout<<endl;
    
    /*
     * print the matching sequence of Y'
     */
    cout<<"print the matching sequence of Y': "<<endl;
    print_seq_aligh_Y(y,P,n,m);
    cout<<endl;

    cout<<"M(n,m)= "<<H[n][m]<<endl;
    
    
    /*
     * memory management: release the allocated
     */
    delete[] x;
    delete[] y;
    
    remove_matrix_P(P,n);
    remove_matrix_H(H,n);
    
    return 0;
}

