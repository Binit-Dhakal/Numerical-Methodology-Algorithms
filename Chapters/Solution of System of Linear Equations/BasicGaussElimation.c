#include <stdio.h>
#include<stdlib.h>

void swap(float *a, float *b) {
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


int main () {
    int ord;
    printf("Enter the order of matrix: ");
    scanf("%d", &ord);

    int len_arr = ord*(ord+1);
    float *arr = malloc(len_arr*sizeof(float));

    // Input Logic
    printf("Enter the Augumented Matrix: \n");
    for (int i = 0; i < len_arr; i++) {
        scanf("%f", &arr[i]);
    }

    // Main Logic
    int main_pivot = 0, pot_pivot, operation_ele, range = 0;
    float factor;
    while (main_pivot < len_arr) {
        pot_pivot = main_pivot;
        while (pot_pivot < len_arr) {
            /* 
                If potential pivot position has element 0, then we search for other contenstants for pivot 
                and swap with our main_pivot  
            */
            if (arr[pot_pivot] != 0) {
                if (pot_pivot == main_pivot){
                    break;
                }

                // we need to swap elements if pot_pivot is not same as main_pivot
                for (int i = 0; i <= ord; i++) {
                    swap(&arr[main_pivot+i], &arr[pot_pivot+i]); 
                }
            }
            pot_pivot += (ord + 1);
        }

        if (pot_pivot > len_arr) {
            printf("The potential pivot position not found\n");
            break;
        }

        // Forward Elimination - Generation of upper triangular matrix
        operation_ele = main_pivot + (ord + 1);
        while (operation_ele < len_arr) {
            factor = arr[operation_ele] / arr[main_pivot];
            arr[operation_ele] = 0;
            
            for (int i = 1; i <= ord-range; i++) {
                if (operation_ele + i < len_arr)
                    arr[operation_ele+i] = arr[operation_ele+i] - factor * arr[main_pivot+i];
            }

            operation_ele += (ord + 1);
        }

        range += 1;
        main_pivot = (main_pivot + 1) + (ord + 1);
    }

    // Backward Elimination
    float *sol = malloc(ord * sizeof(float));
    float sum;
    for (int i = ord-1; i >= 0; i--) {
        sum = 0;
        for (int j = i+1; j < ord; j++) {
            sum += sol[j] * arr[i*(ord+1)+j];
        }
        sol[i] = (arr[i*(ord+1)+ord]-sum) / (arr[i*(ord+1)+i]);
    }


    // Output Logic
    printf("--------------------------------------\n");
    printf("The Upper Triangular Matrix: \n");
    for (int i = 0; i < ord; i++) {
        for (int j = 0; j < ord+1; j++) {
            printf("%f  ", arr[i*(ord+1) + j]);
        }
        printf("\n");
    }

    // Solution
    printf("--------------------------------------\n");
    printf("Solution Matrix: \n");
    for (int i = 0; i < ord; i++) {
        printf("X[%d] = %f\n",i,sol[i]);
    }

    free(arr);
    return 0;
}