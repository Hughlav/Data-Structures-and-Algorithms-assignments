#include <stdio.h>
#include <string.h>
#include <stdbool.h> //so bool can be used (c99)
#include <stdlib.h> // malloc
#include <time.h> //time
#include <math.h>

#define M_SIZE 100
int compQS = 0;
void quicksort(int* num,int p, int r);
int partition(int* num, int p, int r);
void swap(int* num, int i, int j);


void bubblesort(int* num, int size){
    int compBS = 0; // probe counter to find complexity
    bool sorted = false;
    
    while(sorted == false){ // loops until smaller numbers are to the left of bigger
        sorted = true; //only set false again if lift isnt sorted
        int a;
        
        for( int i=0; i < size ; i++){
            compBS++; // probe for finding complexity
            if(num[i+1] < num[i]){ // cheching if left number is bigger than right (smaller numbers should always be on left)
                swap(num, i, i+1); // if left number is bigger swap the numbers
                sorted = false;
            }
        } // end for
    } // end while
    printf("The number of elements compared for bubble sort is: %i \n", compBS);
}// end function



void quicksort(int* num,int p, int r){
    if (p<r){
        int q = partition(num, p, r); // find partition point
        quicksort(num, p, q-1); // call quicksort again for smaller sub list (left)
        quicksort(num,q+1,r); // and again for sub list (right)
    }
}

int partition(int* num, int p, int r){
    int x = num[r]; // x =  last element in list
    int i = p-1; // i counter 1 less that first element
    for(int j=p; j < r; j++){
        if(num[j] <= x){
            compQS++; //probe for finding complexity
            i=i+1;
            swap(num, i,j);// swapping numbers with ones smaller that are to the right
        }
    }//end for
    swap(num, i+1, r); // getting biggest number to end of the list
    return i+1;
}

void swap(int* num, int i, int j){ // simple swap function
    int a;
    a = num[i];
    num[i] = num[j];
    num[j] = a;
}


int main(){
    srand(time(NULL)); // so array always has random elements each time program is run
    int* num,* num1;
    num = (int*) malloc(sizeof(int)*M_SIZE); //declaring space for array in memory
    num1 = (int*) malloc(sizeof(int)*M_SIZE); //used for passing same array to both functions for creating testing results only

    //for (int j= 0; j<10; j++){
    //compQS = 0 // for test results only
    
    for(int i=0; i < M_SIZE; i++){ //for loop used to generate 10 test results for analysing complexity
        num[i] = rand()%1000; // filling array with random numbers between 1-1000
        num1[i] = num[i]; // creating test results only
        printf("%i ", num[i]); //printing list
    }
    
    
    printf("\n\n");
    bubblesort(num1, M_SIZE);  // BUBBLE SORT Used num1 which is same array as num so both methods can be run at the same time
    quicksort(num, 0, M_SIZE-1);  //QUICKSORT
    printf("The number of elements compared for quicksort is: %i \n", compQS);
    //} //end of for loop that was used to generate test results
    printf("\nsorted list is \n\n");
    for(int i=0; i < M_SIZE; i++){ //printing sorted list
        printf("%i ", num[i]);
    }
    printf("\n");
    
    return 0;
}

