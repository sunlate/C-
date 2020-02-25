//
//  rb_tree.hpp
//  hw3
//
//  Created by 孙蕾 on 4/3/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#ifndef __RB_TREE_H__
#define __RB_TREE_H__
#include <vector>

enum rb_tree_color
{
    RB_RED,
    RB_BLACK
};

struct rb_tree_node
{
    int        key;
    int        color;
    rb_tree_node*    left;
    rb_tree_node*    right;
    rb_tree_node*    p;
//    int* output_array;
};

class rb_tree
{
protected:
    rb_tree_node*    T_nil;
    rb_tree_node*    T_root;
    
public:
    rb_tree();
    ~rb_tree();
    
    void insert(int*, int);
    void insert(int);
    
    std::vector<int> outputarray;
    
    int dubplicates=0;
    int case1=0; int case2=0; int case3=0;
    int leftR=0;int rightR=0;
    
    void inorder_output()
    { return inorder_output(T_root, 1); }
    void output()
    { output(T_root, 1); }
    
    void insert_count();
    
    void test()
    { test(T_root,1);}
    
    
protected:
    void insert(rb_tree_node*);
    void insert_fixup(rb_tree_node*&);
    
    void remove_all(rb_tree_node*);
    
    void left_rotate(rb_tree_node*);
    void right_rotate(rb_tree_node*);
    
    void inorder_output(rb_tree_node*, int);
    void output(rb_tree_node*, int);
    
    void test(rb_tree_node*,int);
    
};


#endif

