//
//  BST.c
//
//
//  Created by Hugh Lavery - 14313812 on 18/11/2016.
//
//

#include <stdio.h>
#include <stdlib.h>

typedef struct BST BST;

//Declaring functions to be used
void tree_insert(BST* root, char data);
BST* tree_search(BST* root, char data);
void tree_print_sorted(BST* root);
void delete_tree(BST* root);
BST* balanced_tree (char list[], int size);
void swap(char* num, int i, int j);
int partition(char* num, int p, int r);
void quicksort(char* num,int p, int r);
BST* finding_child(char list[], int s, int l);

//Declaring stuct for BST
struct BST{
    char data;
    struct BST *left, *right;
};



int main(){
    //Declaring root for insert function
    BST* root = (BST*)malloc(sizeof(BST));
    root->data = 'a';
    root->right = root->left = NULL;
    //Using insert funtion to add elements to the tree
    tree_insert(root, 'd');
    tree_insert(root, 'f');
    tree_insert(root, 'c');
    tree_insert(root, 'z');
    tree_insert(root, 'b');
    tree_insert(root, 'A');
    
    BST* found = (BST*)malloc(sizeof(BST));
    
    //Testing finding function
    found = tree_search(root, 'c');
    
    if (found == NULL){
        printf("data not found in tree\n");
    }
    
    free(found);
    
    //Printing out BST then deleting tree and freeing all memory used
    tree_print_sorted(root);
    delete_tree(root);
    root = NULL;
    
    
    //Declaring array list to be sorted for a balanced binary
    //search tree
    char list[] = {'X', 'Z', 'C', 'B', 'A', 'Y'};
    int size = sizeof(list)/sizeof(char);
    printf("size is %i\n", size);
    //Creating a Balanced BST
    BST* newroot = balanced_tree (list, size);
    printf("root of balanced tree is %c\n", newroot->data);
    
    delete_tree(newroot);
    newroot = NULL;
    return 0;
}

//Function to insert a node into the tree
//(given the root of the tree is already declared)
//This function will just insert the node
//to the left of the parent node if smaller
//and to the right if bigger
//It will not create a balanced tree
//and its order will depend on the order it
//recieves chars to be inserted.
void tree_insert(BST* root, char data ){
    
    if(data < root->data ){
        if(root->left == NULL){
            BST* new = (BST*)malloc(sizeof(BST));
            new->data = data;
            new->left = new->right = NULL;
            root->left = new;
        }
        else{
            tree_insert(root->left, data);
        }
        
    }
    
    else if(data > root->data){
        if(root->right == NULL){
            BST* new = (BST*)malloc(sizeof(BST));
            new->left = new->right = NULL;
            new->data = data;
            root->right = new;
        }
        else {
            tree_insert(root->right, data);
        }
    }
}

//Function for searching for a char in BST
//traverses the tree calling itself recursivly
//until it finds the char. If it doesnt find it
//the function will return NULL
BST* tree_search(BST* root, char data ){
    BST* tmp = NULL;
    
    if(data == root->data){
        //printf("found data %c \n", root->data);
        return root;
    }
    else if(data < root->data && root->left){
        // printf("going left\n");
        tmp = tree_search(root->left, data);
    }
    else if(data > root->data && root->right){
        // printf("going right\n");
        tmp = tree_search(root->right, data);
    }
    return tmp;
}


//This function prints the tree from smallest
//element to biggest. It traverses all the
//way to the left then all the way to the right
//prints the value of that node then goes back to
//the node above it and prints that (if it has no
//more children)
void tree_print_sorted(BST* root ){
    printf("printing list\n");
    BST* tmp = (BST*)malloc(sizeof(BST));
    tmp->data = 0;
    tmp->right = tmp->left = NULL;
    char data;
    if(root->left){
        tmp = root->left;
    }
    else{
        tmp = root;
    }
    while(tmp->left){
        tmp = tmp->left;
    }
    data = tmp->data;
    printf("%c\n", data);
    while(data < 'z'){
        data = data +1;
        
        tmp = tree_search(root, data);
        
        if(tmp != NULL){
            printf("%c \n", data);
        }
    }
}

//This deletes the tree without leaving any node left.
//It goes as leftmost as possible then as rightmost as
//possible deletes that node and goes to the parent,
//checks for another child and deletes it if its there
//then deletes the parent and so on
void delete_tree(BST* root ){
    if (root != NULL){
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
        root = NULL;
    }
    
}

//This function takes an input array, orders it (using
//quicksort)and then uses the sencondary function
//finding_child() to build a balanced binary search
//tree.
BST* balanced_tree (char list[], int size){
    quicksort(list, 0, size-1);
    int midpt = size/2;
    char rootchar = list [midpt];
    
    BST* root = (BST*)malloc(sizeof(BST));
    root->data = rootchar;
    root->right = root->left = NULL;
    
    root->left = finding_child(list, 0, midpt-1);
    root->right = finding_child(list, midpt+1, size-1);
    
    return root;
}

//This function recursivly finds the midpoint of a sub array
//to return as the child of the mid point of the parent array
//above it for both the left sub array and right sub array.
//This aids the balanced_tree array in creating a balanced
//BST.
BST* finding_child(char list[], int s, int l){
    int mid = (s+l)/2;
    BST* root = (BST*)malloc(sizeof(BST));
    root->data = list[mid];
    root->right = root->left = NULL;
    
    if(l-s >= 1){
        root->left = finding_child(list, s, mid-1);
        root->right = finding_child(list, mid+1, l);
    }
    return root;
    
}

//This quicksort function and following partition and
//swap functions are used to sort the array before it
//is used to create the sorted BST
void quicksort(char* num,int p, int r){
    if (p<r){
        char q = partition(num, p, r); // find partition point
        quicksort(num, p, q-1); // call quicksort again for smaller sub list (left)
        quicksort(num,q+1,r); // and again for sub list (right)
    }
}
int partition(char* letter, int p, int r){
    char x = letter[r]; // x =  last element in list
    int i = p-1; // i counter 1 less that first element
    for(int j=p; j < r; j++){
        if(letter[j] <= x){
            i=i+1;
            swap(letter, i,j);// swapping numbers with ones smaller that are to the right
        }
    }//end for
    swap(letter, i+1, r); // getting biggest number to end of the list
    return i+1;
}

void swap(char* letter, int i, int j){ // simple swap function
    char a;
    a = letter[i];
    letter[i] = letter[j];
    letter[j] = a;
}



