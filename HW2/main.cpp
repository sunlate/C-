//
//  main.cpp
//  HW2
//
//  Created by 孙蕾 on 3/16/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#include <cstdio>
#include <cstdlib>

#include "random_generator.hpp"
#include "sort.hpp"
#include "timer.hpp"


struct RetVal
{
    char** str_array;
    int* str_length;
};

int main(int argc, char* argv[])
{
    timer t;
    int n, m, d;
    
    if (argc > 1)
    {
        m = atoi(argv[1]);
        m = (m < 1) ? 1 : m;
    }
    else
    {
        cout << "hw1: [m] [n] " << endl;
        cout << "[m]  size of the random string array" << endl;
        cout << "[n]  length of the random strings" << endl;
        cout << endl;
        return 0;
    }
    
    if (argc > 2)
    {
        n = atoi(argv[2]);
        n = (n < 0) ? 0 : n;
    }
    else
        n = 0;
    
    if (argc > 3)
        d = atoi(argv[3]);
    else
        d=0;
    
    char** input_array;
    int* string_length;
    
    /*
     * create input array random
     * depending on program argument
     * -> input_array is allocated!
     */
    t.start();
        auto retvaldata=create_random_string(m,n);
        input_array = retvaldata.str_array;
        string_length=retvaldata.str_length;
    t.stop();
    
    /*
     * output the first 10 elements for debugging purposes
     */
    cout<<"Initialize array of string (Formatting: string | length): "<<endl;
    for (int i=0;(i < m)&&(i < 10); i++)
    {
        cout<<input_array[i]<<" "<<string_length[i]<<endl;
    }
    cout<<endl;
    
    /*
     * Do insertion sort
     */
//    cout << "Running insertion sort algorithm: " << endl;
//    t.start();
//    insertion_sort(input_array, 0, m-1, d,string_length);
//    t.stop();
    
//    /*
//     * output the first 10 elements for debugging purposes
//     */
//    cout<<"After running insertion sort(Formatting: string | character at location d): "<<endl;
//    cout<<"d="<<d<<" "<<endl;
//    for (int i=0;(i < m)&&(i < 10); i++)
//    {
//        if (input_array[i][d]==' ')
//        {
//            input_array[i][d]='A';
//        }
//        cout<<input_array[i]<<"  "<<input_array[i][d]<<endl;
//    }
    
    /*
     * Do radix sort
     */
//     cout << "Running radix sort algorithm: " << endl;
//     t.start();
//     radix_sort(input_array, 0, m-1, d,string_length);
//     t.stop();
//     cout << "Timer (sort): " << t << endl;

    
    /*
     * Do counting sort
     */
        cout << "Running counting sort algorithm: " << endl;
        t.start();
        counting_sort(input_array,m-1, d,string_length);
        t.stop();
        cout << "Timer (sort): " << t << endl;

    /*
     * output the first 10 elements for debugging purposes
     */
    cout<<"After running sort: "<<endl;
    for (int i=0;(i < m)&&(i < 10); i++)
    {
        cout<<input_array[i]<<" "<<input_array[i][d]<<endl;
    }
    cout<<endl;

    
    /*
     * allocated and generate random strings
     * -> do not forget to store the length of the strings
     */
    
//    char* my_char;
//    int length = 0;
//    random_generator* rg = new random_generator();
//    
//    my_char = rg->random_string(10, length);
//    cout << "string: " << my_char << endl;
//    cout << "length: " << length << endl;

    /*
     * check sorted array
     */
//    if (check_sorted(input_array, 0, m-1))
//        cout << "The output is sorted!" << endl;
//    else
//        cout << "ERROR: The output is not sorted!" << endl;

    
    /*
     * free the allocated storage
     */
//    remove_str_array(input_array, m);

    return 0;
}
