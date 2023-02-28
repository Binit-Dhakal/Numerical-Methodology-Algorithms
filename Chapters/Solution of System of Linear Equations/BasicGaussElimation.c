#include <stdio.h>
#include<stdlib.h>

int forward_elimination(float *arr, int ord, int len_arr);
void upper_triangular_matrix_print(float *arr, int ord);
void backward_elimination(float *arr, int ord);
void swap(float *a, float *b);

int main () {
    int ord;
    printf("Enter the order of matrix: ");
    scanf("%d", &ord);

    int len_arr = ord*(ord+1);
    float *arr = malloc(len_arr*sizeof(float));

    // Input Logic
    printf("Enter the Augumented Matrix(%d): \n", len_arr);
    for (int i = 0; i < len_arr; i++) {
        scanf("%f", &arr[i]);
    }
    
    int has_pivot;
    has_pivot = forward_elimination(arr, ord, len_arr);
    
    upper_triangular_matrix_print(arr, ord);

    if (has_pivot == 1){
        backward_elimination(arr, ord);
    }

    free(arr);
    return 0;
}

void swap(float *a, float *b) {
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int forward_elimination(float *arr, int ord, int len_arr){
    /*
    - First check if the pivot position has 0; if yes check all potential pivot position if non zero element exists and
    swap row if the case exists
    - then carry forward elimination operating in all the row below
    */
    int pivot_row, pivot_col = 0;

    while (pivot_col < ord) {
        pivot_row = pivot_col;
        
        // finding the row with potential pivot position not 0
        while (arr[pivot_row*(ord+1) + pivot_col] == 0 && pivot_row < ord) {
            pivot_row += 1;
        }

        if (pivot_row == ord){
            printf("No pivot position found for row - %d", pivot_col);
            return 0;
        }

        // swap the row we are operating with pivot_row
        for (int col = pivot_col; col < ord+1 && pivot_col != pivot_row; col++) {
            swap(&arr[pivot_row*(ord+1)+col], &arr[pivot_col*(ord+1)+col]);
        }
        
        // Forward Elimination
        pivot_row = pivot_col;
        float factor;
        for (int i = pivot_row; i < ord-1; i++) {
            factor = arr[(i+1)*(ord+1)+pivot_col] / arr[pivot_row*(ord+1)+pivot_col];
            arr[(i+1)*(ord+1)+pivot_col] = 0;
            for (int j = pivot_col+1; j < ord+1; j++) {
                arr[(i+1)*(ord+1) + j] -= factor * arr[pivot_row*(ord+1)+j];      
            }
        } 
        pivot_col += 1;
    }
    return 1;
}

void upper_triangular_matrix_print(float *arr, int ord) {
    printf("--------------------------------------\n");
    printf("The Upper Triangular Matrix: \n");
    for (int i = 0; i < ord; i++) {
        for (int j = 0; j < ord+1; j++) {
            printf("%f  ", arr[i*(ord+1) + j]);
        }
        printf("\n");
    }
}

void backward_elimination(float *arr, int ord) {
    float *sol = malloc(ord * sizeof(float));
    float sum;
    for (int i = ord-1; i >= 0; i--) {
        sum = 0;
        for (int j = i+1; j < ord; j++) {
            sum += sol[j] * arr[i*(ord+1)+j];
        }
        sol[i] = (arr[i*(ord+1)+ord]-sum) / (arr[i*(ord+1)+i]);
    }
    
    // Solution
    printf("--------------------------------------\n");
    printf("Solution Matrix: \n");
    for (int i = 0; i < ord; i++) {
        printf("X[%d] = %f\n",i,sol[i]);
    }

    free(sol);
}
