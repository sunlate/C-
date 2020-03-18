//
//  dynprog.cpp
//  hw4
//
//  Created by 孙蕾 on 4/14/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.hpp"

using namespace std;

//struct Matrix
//{
//    int** H;
//    char** P;
//};

/*
 * bottom-up of Smith-Waterman algorithm
 */

void smith_waterman_bottomup(char* x, char* y, int n, int m, int** H, char** P)
{
    int p1,p2,p3;
    p1=p2=p3=0;
    //initialize the matrixes
    for (int i=0; i<=n;i++)
    {
        H[i][0]=P[i][0]=0;
    }
    for (int j=0; j<=m;j++)
    {
        H[0][j]=P[0][j]=0;
    }
    
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            if (x[i-1]==y[j-1])
            {
                p1=H[i-1][j-1]+2;
            }
            else
            {
                p1=H[i-1][j-1]-1;
            }
            p2=H[i-1][j]-1;
            p3=H[i][j-1]-1;
            
            H[i][j]=std::max(std::max(p1,p2),p3);
            
            if (H[i][j]==p1)
            {
                P[i][j]='c';//c: upper left corner; u: upper; 1: left
            }
            else{
                if(H[i][j]==p2)
                {
                    P[i][j]='u';
                }
                else{
                    P[i][j]='l';
                }
            }
        }
    }
}

/*
 * top-down with memoization version of Smith-Waterman algorithm stores the subproblem
 */
int smith_waterman_topdown_helper(char* x, char* y, int n, int m, int** H, char** P)
{
    int p1,p2,p3;
    
    if (H[n][m]>=-50)
    {
        return H[n][m];
    }
   
     if (!(n==0 || m==0))
     {
         if (x[n-1]==y[m-1])
         {
             p1=smith_waterman_topdown_helper(x, y, n-1, m-1, H, P)+2;
//             cout<<x[n-1]<<" "<<y[m-1]<<" p1= "<<p1<<" ";
         }
         else
         {
             p1=smith_waterman_topdown_helper(x, y, n-1, m-1, H, P)-1;
//             cout<<x[n-1]<<" "<<y[m-1]<<" p1= "<<p1<<" ";
         }
         p2=smith_waterman_topdown_helper(x, y, n-1, m, H, P)-1;
//         cout<<" p2= "<<p2<<" ";
         p3=smith_waterman_topdown_helper(x, y, n, m-1, H, P)-1;
//         cout<<" p3= "<<p3<<" ";
         
         H[n][m]=std::max(std::max(p1,p2),p3);
         
//         cout<<"H["<<n<<"]["<<m<<"] "<<H[n][m]<<endl;
//         cout<<endl;
         
         if (H[n][m]==p1)
         {
             P[n][m]='c';//c: upper left corner; u: upper; 1: left
         }
         else{
             if(H[n][m]==p2)
             {
                 P[n][m]='u';
             }
             else{
                 P[n][m]='l';
             }
         }

     }
    return H[n][m];
}
/*
 * top-down with memoization version of Smith-Waterman algorithm
 */
void smith_waterman_topdown(char* x, char* y, int n, int m, int** H, char** P)
{
    //initialize the matrixes
    for (int i=0; i<=n;i++)
    {
        H[i][0]=P[i][0]=0;
    }
    for (int j=0; j<=m;j++)
    {
        H[0][j]=P[0][j]=0;
    }

    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            H[i][j]=INT_MIN;
        }
        
    }
    smith_waterman_topdown_helper(x,y,n,m,H,P);
}

/*
 * print sequency align of X
 */
void print_seq_aligh_X(char* x, char** P, int n, int m)
{
    if (!(n==0 || m==0))
    {
        if (P[n][m]=='c')
        {
//            cout<<"case1:leco  P["<<n<<"]["<<m<<"]"<< P[n][m]<<" "<<x[n-1]<<endl;
            print_seq_aligh_X(x,P, n-1, m-1);
            cout<<x[n-1];
        }
        else{
            if (P[n][m]=='l')
            {
//                cout<<"case2:left  P["<<n<<"]["<<m<<"]"<< P[n][m]<<" "<<x[n-1]<<endl;
                print_seq_aligh_X(x, P, n, m-1);
                cout<<"-";
            }
            else {
//                cout<<"case3:upper P["<<n<<"]["<<m<<"]"<< P[n][m]<<" "<<x[n-1]<<endl;
                print_seq_aligh_X(x, P, n-1, m);
                cout<<x[n-1];
            }
        }
    }
}

/*
 * print sequency align of Y
 */
void print_seq_aligh_Y(char* y, char** P, int n, int m)
{
    if (!(n==0 || m==0))
    {
        if (P[n][m]=='c')
        {
//            cout<<"case1:leco  P["<<n<<"]["<<m<<"]"<< P[n][m]<<" "<<y[m-1]<<endl;
            print_seq_aligh_Y(y,P, n-1, m-1);
            cout<<y[m-1];
        }
        else{
            if (P[n][m]=='u')
            {
//                cout<<"case2:upper P["<<n<<"]["<<m<<"]"<< P[n][m]<<" "<<y[m-1]<<endl;
                print_seq_aligh_Y(y, P, n-1, m);
                cout<<"-";
            }
            else{
//                cout<<"case3:left  P["<<n<<"]["<<m<<"]"<< P[n][m]<<" "<<y[m-1]<<endl;
                print_seq_aligh_Y(y, P, n, m-1);
                cout<<y[m-1];
            }
        }
    }
}

void remove_matrix_P(char** P,int n)
{
    for (int i=0;i<n+1;i++)
    {
        delete[] P[i];
    }
    delete[] P;
}

void remove_matrix_H(int**H,int n)
{
    for (int i=0;i<n+1;i++)
    {
        delete[] H[i];
    }
    delete[] H;
}
