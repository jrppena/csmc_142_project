#include <stdio.h>
#include <stdlib.h>
# define SIZE 1000

int getSummation(int move, int **option, int nopts[], int target_sum);
void printSubset(int move, int summation, int target_sum, int *hasSubset, int **option, int nopts[]);
void findSubsets(int numbers[], int N, int target_sum);

int main(){

	int num_of_sets;
	FILE *fp;
	
	fp = fopen("input.txt","r");
	char ch;

	fscanf(fp,"%d\n",&num_of_sets);
	
	for(int i = 0; i<num_of_sets;i++){
		int target_sum;
		fscanf(fp,"%d\n",&target_sum);

		int numbers[SIZE];
		int value;
		int numbers_size = 0;

		while(fscanf(fp,"%d",&value) == 1){
			numbers[numbers_size++] = value;
			ch = fgetc(fp);
			while(ch == ' ' || ch =='\t'){
				ch = fgetc(fp);
			}
			if(ch == ' ' || ch == EOF){
				break;
			}
			ungetc(ch,fp);
		}

		printf("\nSet %d:\n",i+1);

    	printf("S = { ");  
		for(int j = 0; j<numbers_size;j++){
			printf("%d ",numbers[j]);
		}
		printf("}\n");

		printf("Target Sum: %d\n",target_sum);

		printf("Subsets: \n");
		
		findSubsets(numbers,numbers_size,target_sum);
	}

}

// Calculate the summation of the current subset
int getSummation(int move, int **option, int nopts[], int target_sum) {
	int summation = 0;

	// Calculate the summation of the current subset
	for (int i = 1; i < move; i++) {
		summation += option[i][nopts[i]];
		if (summation > target_sum) {
			break;
		}
	}

	return summation;
}

void printSubset(int move, int summation, int target_sum, int *hasSubset, int **option, int nopts[]) {
	if (summation == target_sum) {
        *hasSubset = 1;
        printf("{ ");
        for (int i = 1; i < move; i++) {
            printf("%d ", option[i][nopts[i]]);
        }
        printf("}\n");
    }
}

void findSubsets(int numbers[], int N, int target_sum) {
    int move, start;
    int nopts[N + 2]; // Array of top of stacks
    // int option[N + 2][N + 2]; // Array of stacks of options

    int **option = (int **)malloc((N + 2) * sizeof(int *));
	for (int i = 0; i < N + 2; i++) {
		option[i] = (int *)malloc((N + 2) * sizeof(int));
	}

	int i, candidate;
    int hasSubset = 0;
    int summation = 0;

    move = start = 0;
    nopts[start] = 1;

    // Continue until the dummy stack is not empty
    while (nopts[start] > 0) {
        if (nopts[move] > 0) {
            move++;
            nopts[move] = 0; // Initialize new move

            // Populate options for the current position
            if (move != N + 1) {
                for (candidate = N - 1; candidate > -1; candidate--) {
                    // Check if current candidate can be added to the subset
                    for (i = move - 1; i > -1; i--) {
                        if (numbers[candidate] <= option[i][nopts[i]]) {
                            break;
                        }
                    }

                    // If candidate can be added, push to current move's options
                    if (!(i >= 1)) {
                        option[move][++nopts[move]] = numbers[candidate];
                    }
                }
            }
        } else {
            int summation = getSummation(move, option, nopts, target_sum);

            // Check if the current subset matches the target sum
			printSubset(move, summation, target_sum, &hasSubset, option, nopts);

            move--;
            nopts[move]--;
        }
    }

    // Handle the case where no subsets are found
    if (hasSubset == 0) {
        printf("No possible subsets\n");
    }

	// Free the allocated memory for the option array
	for(int i = 0; i < N + 2; i++) {
		free(option[i]);
	}
	free(option);

}