// Hugh Lavery 14313812
// hash table starter implementation
// First v. 20 Oct 2016. Dr Anton Gerdelan <gerdela@scss.tcd.ie>
// Written in C99
//
// considerations:
// * remember to put your own name and date on your file(s)
// * start with the easiest and simplest approach, and build up from that.
// * i just have an array for the table and a function, but you
//   might prefer to put these in a c++ class - just as good.
// * i just have one hash function for both searching and storing
//   operations, and i would do the actual storing in main().
//   you might find it tidier to make separate functions for each task.
// * my hash table just stores fixed-length strings, but you might prefer to
//   store structs, or even pointers to dynamically allocated memory
// * when you upgrade to a double hashing function you are vulnerable
//   to some new errors - incomplete coverage and being stuck in an
//   infinite loop. some light reading may be required!
// * if you get stuck in an infinite loop CTRL+C is the code to force quit
//   your program if it's in a terminal
//

#include <stdio.h> // printf() etc.
#include <string.h> // strcpy(), strlen() etc.

//
// i #define array lengths so i only have to change them in one place
#define NUM_TEST_KEYS 9
#define MAX_KEY_LENGTH 16
#define HASH_TABLE_SIZE_M 17

//
// -- the hash table itself --
char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];
double num_ent = 0;

// Linear probing
int hash_function1( const char *key, int table_size ) {
	int index = 0;
	int probe = 0;
    int t = (int) key[0]; //ascii value for first char of string
	
	
	index = (strlen(key)*t)%table_size;	//string length by ascii 1st char modulus to table size
	probe++;
    
	if(strcmp(hash_table[index],key)==0){
	printf("%s is already in the list\n", key);
	return -2;
	}
    
	while(hash_table[index][0] != '\0'){
	index = index + 1;          //linear probe
	probe++;
		if(num_ent == table_size){ //if table is full
		return -1;
		}
	}
	
	
	printf("probe: %d", probe);
	num_ent ++;
	return index;
}

// Double hashing
int hash_function2( const char *key, int table_size ) {
    int index = 0;
    int probe = 0;
    int p = 233; //prime number
    int t = (int) key[0]; //ascii value for first char of string
    //printf("%i\n" , step);
    
    index = (strlen(key)*t)%table_size;	//string length
    probe++;
    
    if(strcmp(hash_table[index],key)==0){
        printf("%s is already in the list\n", key);
        return -2;
    }
    int step = t*p % (table_size-1) + 1; //unique step size for given key
    
    while(hash_table[index][0] != '\0'){
        index = index + step % table_size; //increasing index by unique step size for any string
        probe++;
        if(num_ent == table_size){
            return -1;
        }
    }
    printf("probe: %d", probe);
    num_ent ++;
    return index;
}
    
int main() {
	//
	// example: array of test strings to use as keys
	char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH] = {
		"prince adam", "orko", "cringer", "teela", "aleet", "princess adora", "orko" , "hugh" , "mary"
	};

	
	for ( int i = 0; i < NUM_TEST_KEYS; i++ ) {
        // SEE HERE FOR CHANGING BETWEEN LINEAR PROBING AND DOUBLE HASHING
		//int index = hash_function1( test_strings[i], HASH_TABLE_SIZE_M ); // linear probing
        int index = hash_function2( test_strings[i], HASH_TABLE_SIZE_M ); // Double Hashing
        
		if(index == -1){
		printf( "The list is full");
		}
        if (index != -2){
		strcpy(hash_table[index], test_strings[i]);
		
		printf( "%16s %6i\n", test_strings[i], index );
        }
	}
	
	double load = num_ent/(double)HASH_TABLE_SIZE_M ;
	printf("The load is: %f\n\n" , load);
	
	return 0;
}


// https://github.com/ossec/ossec-hids/blob/master/src/shared/hash_op.c
