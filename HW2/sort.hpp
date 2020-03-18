//
//  sort.hpp
//  HW2
//
//  Created by 孙蕾 on 3/16/19.
//  Copyright © 2019 孙蕾. All rights reserved.
//

#ifndef __SORT_H__
#define __SORT_H__

/*
 * check functions
 */
bool check_sorted(char**, int, int);

/*
 * character sort
 */
int string_compare(char*, char*);
int string_compare_new(char*, char*);
void insertion_sort(char**, int, int, int, int*);
void radix_sort(char**, int, int, int, int*);
void counting_sort(char**, int, int, int*);

struct RetVal;
RetVal create_random_string(int, int);
void remove_str_array(char**, int);

#endif

