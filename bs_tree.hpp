//
//  bs_tree.hpp
//  hw3
//
//  Created by 孙蕾 on 4/3/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#ifndef __BS_TREE_H__
#define __BS_TREE_H__
#include <vector>

struct bs_tree_node
{
    int        key;
    int        color;
    bs_tree_node*    left;
    bs_tree_node*    right;
    bs_tree_node*    p;
};

class bs_tree
{
protected:
    bs_tree_node*    T_nil;
    bs_tree_node*    T_root;
    
public:
    bs_tree();
    ~bs_tree();
    
    std::vector<int> outputarray;
    int dubplicates=0;
    
    void insert(int*, int);
    void insert(int);
    
    void inorder_output()
    { inorder_output(T_root, 1); }
    void output()
    { output(T_root, 1); }
    
    void insert_count(int*, int);
    
protected:
    void insert(bs_tree_node*);
    void remove_all(bs_tree_node*);
    
    void inorder_output(bs_tree_node*, int);
    void output(bs_tree_node*, int);
};


#endif

