/* 
 * uarray2.h 
 * Jared Bronen and Matthew O'Conor, September 15, 2013
 * COMP 40: HW2 Part 1 
 *
 * interface for 2D implementation of unboxed arrays
 */

#include <uarray.h>
#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include <bit.h>
#include <assert.h>
#include <string.h>

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T
typedef struct T *T;

// allocates memory for 2d array of size h * w, for elements of passed in size
extern T    UArray2_new          (int height, int width, int size);
// frees uarray2
extern void UArray2_free         (T uarray2);
// returns number of rows in uarray2
extern int  UArray2_height       (T uarray2);
// returns number of columns in uarray2
extern int  UArray2_width        (T uarray2);
// returns void pointer to value in uarray to at [row][col]
extern void* UArray2_at          (T uarray2, int row, int col);
// map function of uarray2 that maps the 2d array row by row
// (column indices vary more rapidly)
extern void UArray2_map_row_major(T uarray2,
                                  void apply(int index, void *elem, void *cl),
                                  void *cl);
// map function of uarray2 that maps the 2d array column by column
// (row indices vary more rapidly)
extern void UArray2_map_col_major(T uarray2,
                                  void apply(int index, void *elem,
                                             void *cl),
                                  void *cl);
// returns size of uarray2
extern int  UArray2_size         (T uarray2);

#undef T
#endif
