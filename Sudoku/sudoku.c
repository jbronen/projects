/*
 * sudoku.c
 * by Jared Bronen and Matt O'Conor, September 18, 2013
 * COMP 40: HW 2
 *
 * implementation for checking if sudoku graymap is solved
 */

#include <stdio.h>
#include <stdlib.h>
#include "pnmrdr.h"
#include "uarray2.h"

#define WIDTH 9
#define HEIGHT 9
#define MAX_VAL 9
#define MIN_VAL 0

FILE *open_data_file(int argc, char *argv[]);
void is_valid(Pnmrdr_mapdata image_data);
void Sudoku_input(UArray2_T sudoku_array, Pnmrdr_T sudoku_im);

void check_board(UArray2_T su_board, int *values);
void check_line(int value, int check[]);

void check_box(UArray2_T su_board, int check[], int x_bound, int y_bound);
void check_array(int check[], int value);
void check_init(int check[]);
void check_fin_array(int check[]);
void print_array(int check[]);
void check_rows(UArray2_T su_board, int check[]);
void check_cols(UArray2_T su_board, int check[]);

/* opens up the file, sets up image reader and checks for valid input
 * inputs data into UArray2
 * checks if the board is solved
 * frees memory and exits
 */
int main (int argc, char *argv[])
{
        FILE *fp = open_data_file(argc, argv);
        assert(fp);
        Pnmrdr_T sudoku_im = Pnmrdr_new(fp);
        Pnmrdr_mapdata sudoku_data = Pnmrdr_data(sudoku_im);
        is_valid(sudoku_data);
        
        UArray2_T sudoku_array = UArray2_new(HEIGHT,WIDTH,sizeof(int));
        Sudoku_input(sudoku_array, sudoku_im);
    
        int check[MAX_VAL];
        check_init(check);
        check_board(sudoku_array, check);
       
        Pnmrdr_free(&sudoku_im);
        UArray2_free(sudoku_array);
        fclose(fp);
        exit(0);
        return 0;


}
// tests if image meets sudoku specification
void is_valid(Pnmrdr_mapdata image_data)
{

    if (image_data.height != HEIGHT || image_data.width != WIDTH ||
        image_data.denominator != MAX_VAL || image_data.type != 2) {
        exit(1);
    }
}
// opens the data file for reading off of stdin or the command line
FILE *open_data_file(int argc, char *argv[])
{
        FILE *fp = stdin;
        if ( argc > 1) {
                if ( (fp = fopen(argv[1], "rb" ) ) == NULL ) {
                        perror(argv[1]);
                        return NULL;
                }
        }
        return fp;
}
// takes the image data and stores it a UArray2
void Sudoku_input(UArray2_T sudoku_array, Pnmrdr_T sudoku_im)
{
    int *temp = NULL;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            temp = UArray2_at(sudoku_array,i,j);
            *temp = Pnmrdr_get(sudoku_im);
        }
    }

}
/* calls check_rows and check_cols
 * loops through each box in the array and calls check_box
 */
void check_board (UArray2_T su_board, int check[])
{
        check_rows(su_board,check);
        check_cols(su_board,check);
        for (int i = 0; i < MAX_VAL; i = i + 3) {
                for (int j = 0; j < MAX_VAL; j = j + 3) {
                        check_box(su_board,check,i,j);
                }
        }
    
}
/* loops through row by row
 * takes the number at the index and checks it against previous nums in the row
 * checks the finished array
 * reinitializes the array
 */
void check_rows(UArray2_T su_board, int check[])
{
    int *temp = NULL;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            temp = UArray2_at(su_board,i,j);
            check_array(check,*temp);
        }
        check_fin_array(check);
        check_init(check);
    }
}
/* loops through column by columm 
 * same logic as check rows
 */
void check_cols(UArray2_T su_board, int check[])
{
        int *temp = NULL;
        for (int i = 0; i < WIDTH; i++) {
                for (int j = 0; j < HEIGHT; j++) {
                        temp = UArray2_at(su_board,j,i);
                        check_array(check,*temp);
                }
                check_fin_array(check);
                check_init(check);
        }
}
/* given the bounds of the box, loops through the box
 * same logic as check_rows and cols
 */
void check_box (UArray2_T su_board, int check[],
                int x_bound, int y_bound)
{
        int *temp = NULL;
        for (int i = y_bound; i < y_bound + 3; i++) {
                for (int j = x_bound; j < x_bound + 3; j++) {
                temp = UArray2_at(su_board,i,j);
                check_array(check,*temp);
                }
        }
        check_fin_array(check);
        check_init(check);

}
/* tests for input of 0 or greater than MAX_VAL
 * each value is mapped to value -  1
 * if that index has already been set, exits
 * if not sets that index to 1
 */ 
void check_array(int check[], int value)
{
        if(value == 0 || value > MAX_VAL){
                exit(1);
        }
        if(check[value-1]) {
                exit(1);
        }
        else {
                check[value-1] = 1;
        }
}
// initializes the check array to 0
void check_init(int check[])
{
        for ( int i = 0; i < MAX_VAL; i++) {
                check[i] = 0;
        }
}
// checks that all indexes have been set
void check_fin_array(int check[])
{
        for (int i = 0; i < MAX_VAL; i++) {
                if (check[i] == 0) {
                        exit(1);
                }
        }
}


