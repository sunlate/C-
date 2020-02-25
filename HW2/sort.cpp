//
//  sort.cpp
//  HW2
//
//  Created by 孙蕾 on 3/16/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "random_generator.hpp"
#include "sort.hpp"
#include <iostream>
#define RANGE 255

/*
 * HW 2 part
 */
int string_compare(char* s1, char* s2)
{
    /*
     * We assume that s1 and s2 are non-null pointers
     */
    int i=0;
//    i = d-1;
    while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
        i++;
    
    if (s1[i] == s2[i])
        return 0;
    else
    {
        if (s1[i] < s2[i])
            return -1;
        else
            return 1;
    }
}

//int string_compare_new(char* s1, char* s2, int d)
//{
//    /*
//     * We assume that s1 and s2 are non-null pointers
//     */
//    int i;
//        i = d-1;
//    while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
//        i++;
//
//    if (s1[i] == s2[i])
//        return 0;
//    else
//    {
//        if (s1[i] < s2[i])
//            return -1;
//        else
//            return 1;
//    }
//}
//
//void insertion_sort(char** A, int l, int r, int d, int* A_len)
//{
//    int i;
//    char* key;
//
//    for (int j = l+1; j <= r; j++)
//    {
//        key = A[j];
//        i = j - 1;
//
//        while ((i >= l) && (string_compare_new(A[i], key,d) > 0))
//        {
//            A[i+1] = A[i];
//            i = i - 1;
//        }
//
//        A[i+1] = key;
//    }
//}
//
///*
// * Radix sort
// */
//void radix_sort(char** A, int l, int r, int d, int* A_len)
//{
//    int i;
//    char* key;
//
//    for (int j = l+1; j <= r; j++)
//    {
//        key = A[j];
//        i = j - 1;
//
//        while ((i >= l) && (string_compare_new(A[i], key,d) > 0))
//        {
//            A[i+1] = A[i];
//            i = i - 1;
//        }
//
//        A[i+1] = key;
//    }
//}



/*
 * Counting sort
 */
void counting_sort(char** A,int n, int d,int* A_len)
{
    // The output character array
    // that will have sorted arr
    char* output[n];
    int output_len[n];
    

    // Create a count array to store count of inidividul
    // characters and initialize count array as 0
    int count[RANGE + 1];
    memset(count, 0, sizeof(count));

    // Store count of each character
    int i;
    for(i = 0; i<n; i++)
        if(A_len[i]<=d)
        {
            count[0]++;
        }
        else
        {
            count[int(A[i][d])]++;
        }
    
    // Change count[i] so that count[i] now contains actual
    // position of this character in output array
    for (i = 1; i <= RANGE; i++)
        count[i] += count[i-1];

    // Build the output character array
    for (i = 0; i<n; i++)
    {
        if(A_len[i]<=d)
        {
            output[count[0]-1]=A[i];
            output_len[count[0]-1]=A_len[i];
            count[0]--;
        }
        else{
            output[int(count[A[i][d]])-1] = A[i];
            output_len[int(count[A[i][d]])-1]=A_len[i];
            count[int(A[i][d])]--;
        }
        
    }

    // Copy the output array to arr, so that arr now
    // contains sorted characters
    for (i = 0; i<n; ++i)
        A[i] = output[i];
        A_len[i]=output_len[i];
}


   /*
    * generate random arrays of type hw2type
    */
struct RetVal
{
    char** str_array;//array of each string
    int* str_length;//array of each length of string
};

RetVal create_random_string(int m, int n)// "m" for size of array,"n" for length of string
{
    random_generator* rg=new random_generator();
    char** str_array;
    char* my_char;
    int * str_length;
    int length = 0;
    
    str_array=new char*[m];
    str_length=new int[m];
    
    for (int i = 0; i < m; i++)
    {
        my_char = rg->random_string(n, length);
        str_array[i]=my_char;
        str_length[i]=length;
    }
//    for (int i=0; i<m;i++)
//        cout<<i<<" "<<str_array[i]<<" "<<str_length[i]<<" "<<endl;
//    cout<<"m: "<<m<<" n: "<<n<<endl;
//
    return {str_array,str_length};
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is
 *    greater than the i-th element.
 */
//bool check_sorted(char** A, int l, int r)
//{
//    for (int i = l+1; i < r; i++)
//        if (string_compare(A[i-1],A[i]) > 0)
//            return false;
//    return true;
//}

void remove_str_array(char** str_array, int m)
{
    for (int i = 0; i < m; i++)
        delete[] str_array[i];
    delete[] str_array;
}
