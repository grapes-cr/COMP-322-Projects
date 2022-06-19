#include <stdio.h>
#include <stdlib.h>

/* Declare dynamic arrays and global variables*/
int** max_claim, **allocated, **need;
int* resource, *available;
int processes, resources; //row, column

/***********************************************************/
void printVector() {
	/* declare local variables */
	/* for loop: print number of total units and available units of each resource index */
	/* for loop: print each resource index */
	printf("\n\tUnits\tAvailable\n------------------------");
	for (int i = 0; i < resources; i++){
	    printf("\nr%d\t%d\t%d", i, resource[i], available[i]);
	}
	return;
}


/***************************************************************/
void printMatrix(int **arr) { 
	/* declare local variables */
	/* for loop: print each resource index */
	/* for each process: */
	for (int n = 0; n < resources; n++){
	    printf("\tr%d", n);
	}
	printf("\n--------------------------------------");
	for (int i = 0; i < processes; i++){
	    printf("\np%d", i);
	    /* for each resource: */
	    for (int j = 0; j < resources; j++){
			/* print maximum number of units each process may request, is allocated, and needs from each resource */
			printf("\t%d", arr[i][j]);
	    }
	}
	return;
}


/****************************************************************/
void enterParameters() {
	/* declare local variables */
	int unit;
	
	/* prompt for number of processes and number of resources */
	printf("\nEnter number of processes: ");
	scanf("%d", &processes);
	printf("Enter number of resources: ");
	scanf("%d", &resources);
	
	/* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */
	resource = (int*)malloc(resources * sizeof(int));
	available = (int*)malloc(resources * sizeof(int));
	max_claim = (int**)malloc(processes * sizeof(int*));
	allocated = (int**)malloc(processes * sizeof(int*));
	need = (int**)malloc(processes * sizeof(int*));
	
	/* for each resource, prompt for number of units, set resource and available vectors indices*/
	for (int i = 0; i < processes; i++){
        max_claim[i] = (int*)malloc(resources * sizeof(int));
        allocated[i] = (int*)malloc(resources * sizeof(int));
        need[i] = (int*)malloc(resources * sizeof(int));
	}
	
	printf("Enter number of units for resources (r0 to r%d): \n", resources - 1);
	for (int j = 0; j < resources; j++){
	    scanf("%d", &unit);
        resource[j] = unit;
        available[j] = 0;
	}
	
	/* for each process, for each resource, prompt for maximum number of units requested by process, update max_claim and need arrays */ 
	for (int m = 0; m < processes; m++){
	    printf("Enter maximum number of units process p%d will request from each resource (r0 to r%d): \n", m, resources - 1);
	    for (int n = 0; n < resources; n++){
	        scanf("%d", &unit);
	        max_claim[m][n] = unit;
	        need[m][n] = unit;
	    }
	}
	
	/* for each process, for each resource, prompt for number of resource units allocated to process */
	for (int m = 0; m < processes; m++){
	    printf("Enter number of units of each resource (r0 to r%d) allocated to process p%d: \n", resources - 1, m);
	    for (int n = 0; n < resources; n++){
	        scanf("%d", &unit);
	        allocated[m][n] = unit;
	        need[m][n] -= unit;
	        available[n] += unit; 
	    }
	}
	
	for (int p = 0; p < resources; p++){
	    available[p] = resource[p] - available[p];
	}

	/* print resource vector, available vector, max_claim array, allocated array, need array */
	printVector();
	printf("\n\n\tMax Claim\n");
	printMatrix(max_claim);
	printf("\n\n\tCurrent\n");
	printMatrix(allocated);
	printf("\n\n\tPotential\n");
	printMatrix(need);
	return;
}


/********************************************************************/
void safeSequence() {

	/* declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count*/
	int done = 0;
    int num_sequenced = 0;
    int sequenced[processes];
    
    for (int w = 0; w < processes; w++){
        sequenced[w] = 0;
    }
	
	/* while not all processed are sequenced */
	while (done == 0){
		/* for each process */
		for (int i = 0; i < processes; i++){
			/* if process has not been safely sequenced yet */
			if (sequenced[i] < resources){
			    sequenced[i] = 0;
				/* for each resource */
				printf("\nChecking: < ");
				for (int x = 0; x < resources; x++)
				    printf("%d ", need[i][x]);
				printf("> <= < ");
				for (int y = 0; y < resources; y++)
				    printf("%d ", available[y]);
				printf(" >");
				
				for (int j = 0; j < resources; j++){
					/* check for safe sequencing by comparing process' need vector to available vector */
	      			/* if each resource is available */
	      			if (need[i][j] <= available[j]){
	      			    sequenced[i] += 1;
	      			} 
				}
				if (sequenced[i] >= resources){
				    /* print message that process had been safely sequenced */
				    printf("\n:p%d safely sequenced", i);
				    for (int z = 0; z < resources; z++){
				        available[z] += allocated[i][z];
				    }
				    num_sequenced++;
				} else {
				    printf("\n:p%d could not be sequenced", i);
				}
			}
		}
		if (num_sequenced == processes){
		    done++;
		}
	}
	printf("\nDeadlock reached!");
    return;
}


/********************************************************************/
void freeMemory() {
	/* check if vectors/array are not NULL--if so, free each vector/array */
	for (int i = 0; i < resources; i++){
	    free(allocated[i]);
	    free(max_claim[i]);
	    free(need[i]);
	}
	free(allocated);
	free(max_claim);
	free(need);
	free(resource);
	free(available);
	printf("\nMemory freed. Goodbye.");
	return;
}


/***************************************************************/
int main() {
	/* declare local vars */
	int menuInput, done = 0, process;
	/* while user has not chosen to quit */
	while (done == 0){
		/* print menu of options */
		printf("\n\nBanker's Algorithm\n------------------\n1) Enter parameters\n2) Determine safe sequence\n3) Quit program\n\nEnter Selection: ");
		/* prompt for menu selection */
		scanf("%d", &menuInput);
		switch (menuInput){
		    case 1:
		        enterParameters();
		        break;
		    
		    case 2:
		        safeSequence();
		        break;
		        
		    case 3:
		        freeMemory();
		        done++;
		        break;
		    
		    default:
		        printf("\nInvalid input.");
		}
		/* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */	
	} /* while loop */
	 return 1;  /* indicates success */
} /* end of procedure */