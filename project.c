#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000

// Function prototypes
int getSummation(int move, int **option, int nopts[], int target_sum);
void printSubset(int move, int summation, int target_sum, int *hasSubset, int **option, int nopts[]);
void findSubsets(int numbers[], int N, int target_sum);

int main() {
    int num_of_sets; // To store the number of test sets
    FILE *fp = fopen("input.txt", "r"); // Open the input file in read mode

    if (!fp) {
        printf("Failed to open file\n");
        return 1;
    }

    fscanf(fp, "%d\n", &num_of_sets); // Read the number of sets from the file

    for (int i = 0; i < num_of_sets; i++) {
        int target_sum; // Variable to store target sum for the current set
        if (fscanf(fp, "%d\n", &target_sum) != 1) {
            printf("Error reading target sum for set %d\n", i + 1);
            continue;
        }

        int numbers[SIZE]; 
        int numbers_size = 0; 
        char line[2048]; // Buffer to hold the line with numbers

        if (fgets(line, sizeof(line), fp) == NULL) {
            printf("Error reading numbers for set %d\n", i + 1);
            continue;
        }

        char *token = strtok(line, " \n");
        // Process all numbers in the line
        while (token != NULL) {
            numbers[numbers_size++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        printf("\nSet %d:\n", i+1);
        printf("S = { ");
        for (int j = 0; j < numbers_size; j++) {
            printf("%d ", numbers[j]);
        }
        printf("}\n");
        printf("Target Sum: %d\n", target_sum);
        printf("Subsets: \n");

        findSubsets(numbers, numbers_size, target_sum); 
    }

    fclose(fp); // Close the file
    return 0;
}

// Calculate the summation of the current subset
int getSummation(int move, int **option, int nopts[], int target_sum) {
    int summation = 0;
    
    // Calculate the summation of the current subset
    for (int i = 1; i < move; i++) {

		// Add the current element to summation
        summation += option[i][nopts[i]]; 

		 // Break early if summation exceeds the target sum
        if (summation > target_sum) {
            break;
        }
    }
    
    return summation;
}

void printSubset(int move, int summation, int target_sum, int *hasSubset, int **option, int nopts[]) {
    if (summation == target_sum) { 

		// Set flag to indicate a subset was found
        *hasSubset = 1; 
        printf("{ ");
        for (int i = 1; i < move; i++) {

			// Print the subset
            printf("%d ", option[i][nopts[i]]); 
        }
        printf("}\n");
    }
}

void findSubsets(int numbers[], int N, int target_sum) {
    int move, start;

	// Array of top of stacks
    int nopts[N + 2]; 
    
	// Dynamic memory allocation for option stacks
    int **option = (int **)malloc((N + 2) * sizeof(int *)); 
    for (int i = 0; i < N + 2; i++) {

		// Allocate memory for each stack
        option[i] = (int *)malloc((N + 2) * sizeof(int)); 
    }
    
    int i, candidate;

	// Flag to check if any subset is found
    int hasSubset = 0; 
    int summation = 0;
    
    move = start = 0;

	// Initialize the top of the dummy stack
    nopts[start] = 1; 
    
	// Continue until the dummy stack is not empty
    while (nopts[start] > 0) { 
        if (nopts[move] > 0) {
            move++;

			// Initialize new move
            nopts[move] = 0; 
            
			// Prevent moving beyond the allocated memory to avoid out-of-bounds access
            if (move != N + 1) {
                for (candidate = N - 1; candidate > -1; candidate--) {
                    for (i = move - 1; i > -1; i--) {
                        if (numbers[candidate] <= option[i][nopts[i]]) {
                            break;
                        }
                    }
                    
					// Check if the candidate can be added
                    if (!(i >= 1)) { 
                        option[move][++nopts[move]] = numbers[candidate];
                    }
                }
            }
        } else {

			// Calculate summation of the current subset
            int summation = getSummation(move, option, nopts, target_sum); 
            
			// Check and print the subset
            printSubset(move, summation, target_sum, &hasSubset, option, nopts); 
            
			// Move back to the previous stack
            move--; 

			// Decrement the top of the stack
            nopts[move]--; 
        }
    }
    
    if (hasSubset == 0) {

		// Print if no subsets are found
        printf("No possible subsets\n"); 
    }
	
	// Free the allocated memory for each stack
    for(int i = 0; i < N + 2; i++) {
        free(option[i]); 
    }
	// Free the allocated memory for the option array
    free(option); 
}
