#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* declare global variables including a table structure to hold scheduling information */
int numProcesses, scheduled = 0, col = 3;
/* optional: define a function that finds the maximum of two integers */

typedef struct table1 {
    int id;
    int arrival;
    int total;
} *table1;

typedef struct table2 {
    int notUsed;
    int start;
    int end;
    int turnaround;
} *table2;

table1 t1;
table2 t2;

/***************************************************************/
void printTable() {
	/* declare local variables */
	/* print table header */
	printf("\nID      Arrival Total\n--------------------------\n");
	
	/* for each process */
	/* print the contents (id, arrival time, total_cycles) of each field of the table's index */
	for (int i = 0; i < numProcesses; i++) {
        printf("\n%d\t%d\t%d", t1[i].id, t1[i].arrival, t1[i].total);
	}
    printf("\n");

	/* if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time) */
	if (scheduled != 0){
	    printf("\nStart   End     Turnaround\n--------------------------\n");
	    for (int i = 0; i < numProcesses; i++) {
            printf("\n%d\t%d\t%d", t2[i].start, t2[i].end, t2[i].turnaround);
	    }
        printf("\n");
        scheduled = 0;
	    return;
	}
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/***************************************************************/
void enterParameters() {	
	/* declare local variables */
	int processID, arrivalCycle, totalCycles;
	/* prompt for total number of processes */	
	printf("\nEnter total number of processes: ");
	scanf("%d", &numProcesses);
	/* allocate memory for table to hold process parameters */
	t1 = malloc(numProcesses* sizeof(table1));
	t2 = malloc(numProcesses * sizeof(table2));
	
	/* for each process */
	/* prompt for process id, arrival time, and total cycle time */	
	for (int i = 0; i < numProcesses; i++){
    	   printf("\nEnter process ID: ");
    	   scanf("%d", &processID);
    	   t1[i].id = processID;
    	   printf("\nEnter arrival cycle for process P[%d]: ", processID);
    	   scanf("%d", &arrivalCycle);
    	   t1[i].arrival = arrivalCycle; 
    	   printf("\nEnter total cycles for process P[%d]: ", processID);
    	   scanf("%d", &totalCycles);
    	   t1[i].total = totalCycles; 
	}


	/* print contents of table */
	printTable();
	return;		
}	
		

/***************************************************************/
void fifo() {
	/* declare (and initilize when appropriate) local variables */
    t2[0].start = 0;
	t2[0].end = t1[0].total;
	t2[0].turnaround = t2[0].end;
	
	for (int i = 1; i < numProcesses; i++){
	    t2[i].start = t2[i-1].end;
	    t2[i].end = t2[i].start + t1[i].total;
	    t2[i].turnaround = t2[i].end - t1[i].arrival;
	} 

	scheduled = 1;
	printTable();
	return;		
}	


/***************************************************************/
void srt() {
    int total = t1[0].total;
    int totals[numProcesses-2];
    int best[numProcesses];
    int shortestArrival = t1[1].arrival;
    
    for (int i = 2; i < numProcesses; i++){
        totals[i-2] = t1[i].total;
    }
	
    for (int i = 1; i < numProcesses; i++){
        if (t1[i].arrival < shortestArrival){
            shortestArrival = t1[i].arrival;
        }
        total += t1[i].total;
    }
    qsort(totals, numProcesses-2, sizeof(int), cmpfunc);

    if (t1[0].total < shortestArrival){
        best[0] = 0;
        for (int i = 1; i < numProcesses; i++){
            for (int j = 0; j < numProcesses; j++){
                if (totals[i-1] == t1[j].total){
                    best[i] = j;
                }
            }
        }
        
        t2[0].start = 0;
	    t2[0].end = t1[0].total;
	    t2[0].turnaround = t2[0].end;
	    for (int i = 1; i < numProcesses; i++){
    	    t2[best[i]].start = t2[best[i-1]].end;
    	    t2[best[i]].end = t2[best[i]].start + t1[best[i]].total;
    	    t2[best[i]].turnaround = t2[best[i]].end - t1[best[i]].arrival;
    	} 
    } else {
        best[1] = 1;
        for (int i = 2; i < numProcesses; i++){
            for (int j = 0; j < numProcesses; j++){
                if (totals[i-2] == t1[j].total){
                    best[i] = j;
                }
            }
        }
        t2[best[1]].start = t1[best[1]].arrival;
	    t2[best[1]].end = t2[best[1]].start + t1[best[1]].total;
	    t2[best[1]].turnaround = t2[best[1]].end - t1[best[1]].arrival;
        for (int i = 2; i < numProcesses; i++){
    	    t2[best[i]].start = t2[best[i-1]].end;
    	    t2[best[i]].end = t2[best[i]].start + t1[best[i]].total;
    	    t2[best[i]].turnaround = t2[best[i]].end - t1[best[i]].arrival;
	    } 
	    t2[0].start = 0;
	    t2[0].end = total;
	    t2[0].turnaround = t2[0].end - t1[0].arrival;
    }
	scheduled = 1;
	printTable();
	return;		
}	
        	

/***************************************************************/
void sjf() {
    int best[numProcesses];
    int totals[numProcesses-1];
    
    t2[0].start = 0;
	t2[0].end = t1[0].total;
	t2[0].turnaround = t2[0].end;
	best[0] = 0;
	
	for (int i = 0; i < numProcesses; i++){
        totals[i] = t1[i].total;
	}
    qsort(totals, numProcesses, sizeof(int), cmpfunc);
 
    for (int i = 1; i < numProcesses; i++){
        for (int j = 0; j < numProcesses; j++){
            if (totals[i-1] == t1[j].total){
                best[i] = j;
            }
        }
    }
 
	for (int i = 1; i < numProcesses; i++){
	    
	    t2[best[i]].start = t2[best[i-1]].end; 
	    t2[best[i]].end = t2[best[i]].start + t1[best[i]].total;
	    t2[best[i]].turnaround = t2[best[i]].end - t1[best[i]].arrival;
	} 

	scheduled = 1;
	printTable();
	
	return;		
}	
        	

/***************************************************************/
void freeMemory() {
	/* free the schedule table if not NULL */
	free(t1);
	printf("Memory freed. Have a good day.");
	return;
}


/***************************************************************/
int main() {
	/* declare local vars */
	int menuInput, done = 0, process;
	/* while user has not chosen to quit */
	while (done == 0){
		/* print menu of options */
		printf("\nBatch scheduling\n----------------\n1: Enter Parameters\n2: Schedule processes with FIFO algorithm\n3: Schedule processes with SJF algorithm\n4: Schedule processes with SRT algorithm\n5: Quit and free memory\n\nEnter Selection: ");
		/* prompt for menu selection */
		scanf("%d", &menuInput);
		switch (menuInput){
		    case 1:
		        enterParameters();
		        break;
		    
		    case 2:
		        fifo();
		        break;
		    
		    case 3:
		        sjf();
		        break;
		  
		    case 4:
		        srt();
		        break;
		        
		    case 5:
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

