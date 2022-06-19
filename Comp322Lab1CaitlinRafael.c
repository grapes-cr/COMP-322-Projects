#include <stdio.h>
#include <stdlib.h>

/* Define structures and global variables*/
typedef struct node {
    int process;
    int parent;
    struct node *child;
} *PCB;

PCB pcb;

int numProcesses;

/***************************************************************/
void printProcess() {
	/* declare local vars */
	PCB next;

	/* for each PCB index i from 0 up to (but not including) maximum number*/
	for (int i = 0; i < numProcesses; i++){
		/* check if PCB[i] has a parent and children */
		if ((pcb[i].parent!=-1)&&(pcb[i].child!= NULL)){
			/* print message about children of the current PCB[i] */
			printf("PCB[%d] is the parent of: ", i);
			    for (int j = 1; j < numProcesses; j++){
				/* print message about current child process index */
				if (pcb[j].parent == i){
				    printf("PCB[%d] ", j);
				}
			} /* while */
			/* print newline */
			printf("\n");
		}/* if */
	} /* for */
} /* end of procedure */

/***************************************************************/
void enterParameters() {
	/* declare local vars */
	//PCB pcb;
	/* prompt for maximum number of processes */
	printf("Enter Maximum Number of Processes: ");
	scanf("%d", &numProcesses);
	/* allocate memory for dynamic array of PCBs */
	pcb = (PCB)malloc(numProcesses * sizeof(PCB));
	/* Define PCB[0] */
	pcb[0].parent = 0;
	pcb[0].child = NULL;
	pcb[0].process = 0;
	/* for-loop to intitialize all other indices' parent to -1 */
	for (int i = 1; i < numProcesses; i++){
	    pcb[i].parent = -1;
	    pcb[i].child = NULL;
	    pcb[i].process = i;
	}
	return;
} /* end of procedure */

	
/***************************************************************/
void create() {
	/* define local vars */
	PCB link, childpcb;
	int p, q = 1;
	/* prompt for parent process index p */
	printf("Enter the Parent Process Index: ");
	scanf("%d", &p);
	/* search for first available index q without a parent in a while loop */
	while (pcb[q].parent != -1){
	    q++;
	}

	/* record the parent's index p and process q in childpcb */
	childpcb->parent = p;
	childpcb->child = NULL;
	childpcb->process = q;

	/* set parent and child relationship in global pcb*/
	pcb[p].child = childpcb;
	pcb[q].parent = p;
	
	/* call procedure to print current hierachy of processes */
	printProcess();
	return;
} /* end of procedure */


/***************************************************************/
void destroy(int process) {
	/* declare local vars */
	int q;
	if ((pcb[0].child == NULL) || (pcb == NULL)){ //if only pcb exists or if null, just return
	    return;
	} else {
	/* check if end of linked list--if so return */
	for (int i = 1; i < numProcesses; i++){
	    if (pcb[i].parent == process){
	        pcb[i].parent = -1;
	        pcb[i].child = NULL;
	        pcb[i].process = -1;
	        }
    	}
	}
	pcb[process].child = NULL;
	printProcess();
	return;
} /* end of procedure */

/***************************************************************/
void freeMemory() {
	/* check if PCB is non null) */
	if (pcb != NULL){
	   free(pcb);
	} /* if */
	printf("Memory freed. Goodbye.");
	return;
} /* end of procedure */


/***************************************************************/
int main() {
	/* declare local vars */
	int menuInput, done = 0, process;
	/* while user has not chosen to quit */
	while (done == 0){
		/* print menu of options */
		printf("\nProcess creation and destruction\n---------------------\n1: Enter Parameters\n2: Create New Child Process\n3: Destroy All Descendants of a Process\n4: Quit Program and Free Memory\n\nEnter Selection: ");
		/* prompt for menu selection */
		scanf("%d", &menuInput);
		switch (menuInput){
		    case 1:
		        enterParameters();
		        break;
		    
		    case 2:
		        create();
		        break;
		    
		    case 3:
		        printf("Enter a process to destroy: ");
		        scanf("%d", &process);
		        destroy(process);
		        break;
		        
		    case 4:
		       freeMemory();
		       done++;
		       break;
		    
		    default:
		        printf("\nInvalid input.");
		}
		/* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */	
	} /* while loop */
	 return 1; /* indicates success */
} /* end of procedure */