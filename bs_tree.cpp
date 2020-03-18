//
//  bs_tree.cpp
//  hw3
//
//  Created by 孙蕾 on 4/3/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#include "bs_tree.hpp"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
bs_tree::bs_tree()
{
    /*
     * create T_nil element
     */
    T_nil = new bs_tree_node();
    T_nil->p = T_nil;
    T_nil->left = T_nil;
    T_nil->right = T_nil;
    
    /*
     * root of bs tree
     */
    T_root = T_nil;
}

bs_tree::~bs_tree()
{
    /*
     * delete nil element and all other allocated nodes
     */
    remove_all(T_root);
    
    delete T_nil;
}

void bs_tree::insert_count(int* key_array, int n){
    cout<<"Counter for the number of duplicates: "<<dubplicates<<endl;
}

void bs_tree::insert(int* key_array, int n)
{
    for (int i = 0; i < n; i++)
        insert(key_array[i]);
}

void bs_tree::insert(int key)
{
    /*
     * wrapper around insert
     * -> creates black node with key
     * -> inserts node
     */
    bs_tree_node* z;
    
    z = new bs_tree_node;
    z->key = key;
    
    insert(z);
}

void bs_tree::insert(bs_tree_node* z)
{
    /*
     * binary tree type insert
     * -> search position, insert new node
     * -> fix properties after insert
     */
    bs_tree_node* x;
    bs_tree_node* y;
    
    y = T_nil;
    x = T_root;
    while (x != T_nil)
    {
        y = x;
        
        if (z->key == x->key){
            dubplicates++;
            return;
        }
        
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    z->p = y;
    if (y == T_nil)
        T_root = z;
    else
    {
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }
    
    z->left = T_nil;
    z->right = T_nil;
    
}


void bs_tree::inorder_output(bs_tree_node* x, int level)
{
    /*
     * in order walk through binary tree
     * -> see book or slides
     */
    if (x != T_nil)
    {
        inorder_output(x->left, level+1);
        cout << "(" << x->key << "," << level << ")" << endl;
        outputarray.push_back(x->key);
        inorder_output(x->right, level+1);
    }
}

void bs_tree::output(bs_tree_node* x, int r_level)
{
    /*
     * some structured output
     */
    list< pair<bs_tree_node*,int> > l_nodes;
    pair<bs_tree_node*,int> c_node;
    int c_level;
    
    c_level = r_level;
    l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(x, r_level));
    
    while (!l_nodes.empty())
    {
        c_node = *(l_nodes.begin());
        
        if (c_level < c_node.second)
        {
            cout << endl;
            c_level = c_node.second;
        }
        
        cout << "(" << c_node.first->key << ","
        << endl;
        
        if (c_node.first->p == T_nil)
            cout << ",ROOT) ";
        else
            cout << ",P:" << c_node.first->p->key << ") ";
        
        if (c_node.first->left != T_nil)
            l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(c_node.first->left,
                                                                  c_node.second+1));
        if (c_node.first->right != T_nil)
            l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(c_node.first->right,
                                                                  c_node.second+1));
        l_nodes.erase(l_nodes.begin());
    }
    
    cout << endl;
}

void bs_tree::remove_all(bs_tree_node* x)
{ 
    /*
     * recursively remove all tree elements
     */
    if (x != T_nil)
    {
        remove_all(x->left);
        remove_all(x->right);
        
        delete x;
    }
}


