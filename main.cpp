//
//  main.cpp
//  hw3
//
//  Created by 孙蕾 on 4/3/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sort.hpp"
#include "bs_tree.hpp"
#include "rb_tree.hpp"
#include "timer.hpp"
#include "random_generator.hpp"

int main(int argc, char* argv[])
{
    random_generator rg;
    timer t;
    int n, d;
    
    if (argc > 1)
    {
        n = atoi(argv[1]);
        n = (n < 1) ? 1 : n;
    }
    else
    {
        cout << "hw1: [n] [direction]" << endl;
        cout << "[n]              size of the random integer " << endl;
        cout << "[direction]      0: random" << endl;
        cout << "                 1: sorted" << endl;
        cout << "                 -1: reverse sorted" << endl;
        cout << endl;
        return 0;
    }
    
    if (argc > 2)
        d = atoi(argv[2]);
    else
        d = 0;
    
    int* input_array;
//    int* output_
    /*
     * create input array sorted/reverse sorted/random
     * depending on program argument
     * -> input_array is allocated!
     */
    t.start();
    if (d == 0)
        input_array = create_random(n);
    else
    {
        if (d < 0)
            input_array = create_reverse_sorted(n);
        else
            input_array = create_sorted(n);
    }
    t.stop();
    
    cout << "Timer (generate): " << t << endl;
    
    /*
     * output the first 20 elements for debugging purposes
     */
    cout<<"output the first 20 elements for debugging purposes"<<endl;
    for (int i = 0; (i < n) && (i < 20); i++)
    {
        cout << input_array[i] << endl;
    }
    
    /*
     * Do red black tree
     */
    cout << "Running Red-Black tree algorithm: " << endl;
    t.start();
    rb_tree rb;

    rb.insert(input_array,n);
    cout<<"Inorder output: "<<endl;
//    int* output_array=rb.inorder_output();
    rb.inorder_output();
//    cout<<" output array verification: "<<rb.outputarray[0]<<endl;

//    cout<<"rb-tree output"<<endl;
//    rb.output();
    t.stop();
    cout << "Timer (sort): " << t << endl;

    rb.insert_count();
//    rb.test();
    
    /*
     * Do binary search tree
     */
//    cout << "Running binary search tree algorithm: " << endl;
//    t.start();
//    bs_tree bs;
//
//    bs.insert(input_array,n);
//    cout<<"Inorder output: "<<endl;
//    bs.inorder_output();
//    //    cout<<"bs-tree output"<<endl;
//    //    bs.output();
//    t.stop();
//    cout << "Timer (sort): " << t << endl;
//
//    bs.insert_count(input_array, n);

    
//    /*
//     * output the first 20 elements for debugging purposes
//     */
//    cout<<"output array verifications: "<<endl;
//    for (int i = 0; (i < n) && (i < 20); i++)
//    {
//        cout << i<<" "<<rb.outputarray[i] << endl;
//    }
    
    /*
     * check whether or not the algorithm sorted the array
     */
    int* final_array = &rb.outputarray[0];
//    int* final_array = &bs.outputarray[0];
    
    if (check_sorted(final_array, 0, 30000))
        cout << "The output is sorted!" << endl;
    else
        cout << "ERROR: The output is not sorted!" << endl;
    
    return 0;
}


