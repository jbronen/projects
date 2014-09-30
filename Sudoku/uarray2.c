/*
 * uarray2.c
 * by Jared Bronen & Matt O'Conor
 * Comp 40: HW 2
 *
 * Implementation for 2d unboxed array of Polymorphic elements
 */

#include "uarray2.h"

int UArray2_index (UArray2_T uarray2, int x, int y);

#define T UArray2_T

struct T
{
        int height;
        int width;
        int size;
        UArray_T one_array;
};

/* allocates memory for a new UArray2 of height x width 
 * stores members of size bytes
 * initializes struct members 
 * sets up 1D representation
 * returns the UArray2
 */
T UArray2_new (int height, int width, int size)
{
        T uarray2 = NULL; 
        uarray2 = malloc(sizeof(UArray2_T)+(sizeof(int)*3)+
                     sizeof(UArray_T));
        UArray_T temp = UArray_new(width*height, size);
        uarray2->one_array = temp;
        uarray2->height  = height;
        uarray2->width   = width;
        uarray2->size    = size;
        return uarray2;
}
/* frees the memory */
void UArray2_free (T uarray2)
{
        UArray_free(&uarray2->one_array);
        free(uarray2);

}

int UArray2_height (T uarray2)
{
        assert(uarray2);
    
        return uarray2->height;
}

int UArray2_width (T uarray2)
{
        assert(uarray2);

        return uarray2->width;
}

int UArray2_size(T uarray2)
{
        assert(uarray2);

        return uarray2->size;
}
/* returns the associated 1D index from the 2D coords 
 * indices passed in must be withing the bounds of the board
 * not included in uarray2.h, hidden from client
 */
int UArray2_index (T uarray2, int x, int y)
{
        assert(uarray2);
        assert(x >= 0 && x < UArray2_width(uarray2));
        assert(y >= 0 && y < UArray2_height(uarray2));
        int index = -1;
        index = uarray2->width * x + y;
        return index;
}
/* returns a void pointer to the element stored at the indices passed in */
void* UArray2_at (T uarray2, int row, int col)
{
        assert(uarray2);
        void *elem = NULL;
        elem = UArray_at(uarray2->one_array, UArray2_index(uarray2,row,col));
        return elem;
}    

/* loops through the 2D array col by col
 * calls the apply function on each element
 */
void UArray2_map_col_major (T uarray2, void apply(int index, void *elem,
                                 void *cl),void *cl)
{
        for (int i = 0; i < uarray2->width; i++) {
                for (int j = 0; j < uarray2->height; j++) {
                                apply(UArray2_index(uarray2,i,j),
                                UArray_at(uarray2->one_array, 
                                UArray2_index(uarray2,i,j)), cl);    
        }
    }

}

/* loops through the 2D array row by row
 * calls the apply function on each element
 */
void UArray2_map_row_major (T uarray2, void apply(int index, void *elem,
                                                  void *cl),
                            void *cl)
{
    int area = uarray2->width * uarray2->height;
    for(int i = 0; i < area; i++){
        apply(i,UArray_at(uarray2->one_array, i),cl);
    }

}
