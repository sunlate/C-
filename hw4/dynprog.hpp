//
//  dynprog.hpp
//  hw4
//
//  Created by 孙蕾 on 4/14/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#ifndef __DYNPROG_H__
#define __DYNPROG_H__

void smith_waterman_bottomup(char*, char*, int, int, int**, char**);
void smith_waterman_topdown(char*, char*, int, int, int**, char**);
int smith_waterman_topdown_helper(char*, char*, int, int, int**, char**, int*);
void print_seq_aligh_X(char*, char**, int, int);
void print_seq_aligh_Y(char*, char**, int, int);
void remove_matrix_P(char**,int);
void remove_matrix_H(int**,int);

#endif
