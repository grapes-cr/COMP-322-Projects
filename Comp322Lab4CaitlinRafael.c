#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declare structure to store block information (id, starting address, ending address, link to next block)
typedef struct linkedList {
    int id;
    int startingAddr;
    int endingAddr;
} *linkedList;

// declare linked list to connect allocation block
linkedList list;

// declare global variables
int size, algorithm, listSize, isDeallocated, totalSize;

/********************************************************************/
void enterParameters() {
	// declare local variables (if any)
	// prompt for size of physical memory and choice of hole-fitting algorithm (0=first-fit, 1=best-fit), initialize remaining memory 
	printf("Enter size of physical memory: ");
	scanf("%d", &size);
	printf("Enter hole-fitting algorithm (0=first fit, 1=best_fit): ");
	scanf("%d", &algorithm);
	
	if ((algorithm == 0) || (algorithm == 1)){
    	listSize = 0;
    	isDeallocated = 0;
    	totalSize = size;
	} else {
	    printf("\nError: Enter only a 0 or 1.\n");
	}
	return;
}


/********************************************************************/
void printTable() {
	// declare local variables
	// print table containing block id, starting address, ending address
	printf("\nID\tStart\tEnd\n-------------------\n");
	for (int i = 0; i < listSize; i++){
	    printf("%d\t%d\t%d\n", list[i].id, list[i].startingAddr, list[i].endingAddr);
	}
	return;
}


/********************************************************************/
void allocate() {
	// declare local variables
	int blockId, blockSize, holeSize;
	int bestSize = 0;
	int flag = 0;
	int best = listSize;
	linkedList temp;
	linkedList temp2;
	
	// initialize best hole so far to size of physical memory
	// prompt for block id & block size
	printf("Enter block id: ");
	scanf("%d", &blockId);
	printf("Enter block size: ");
	scanf("%d", &blockSize);
	// check if size of block is larger than remaining unallocated space, if so, print message and return
	if (blockSize > size){
	    printf("\nError: Block size is too large. Cannot allocate.\n");
	    return;
	} else {
	    // allocate space for new block and set id
	    for (int i = 0; i < listSize; i++){
	        if (list[i].id == blockId){
	            flag++;
	        }
	    }
	    // if id already exists, reject request and return
	    if (flag > 0){
	        printf("\nError: Block id cannot be a duplicate. Cannot allocate.\n");
	        return;
	    } else {
	        // set values for start and end of currently found hole
	        if (isDeallocated != 1){ 
    	        if (listSize == 0){
    	            list = malloc(sizeof(linkedList));
    	            list[listSize].id = blockId;
    	            list[listSize].startingAddr = 0;
    	            list[listSize].endingAddr = blockSize;
    	        } else {
    	            temp2 = malloc(listSize+1 * sizeof (linkedList));
    	            memcpy(&temp2, &list, sizeof(temp2));
    	            list = temp2;
    	            list[listSize].id = blockId;
    	            list[listSize].startingAddr = list[listSize-1].endingAddr;
    	            list[listSize].endingAddr = list[listSize].startingAddr + blockSize;
    	        }
	        } else { //if already deallocated memory, run either best fit or first fit
	            if (listSize == 0){
    	            list = malloc(sizeof(linkedList));
    	            list[listSize].id = blockId;
    	            list[listSize].startingAddr = 0;
    	            list[listSize].endingAddr = blockSize;
    	        } else {
    	            if (algorithm == 1){ //best-fit
    	            bestSize = blockSize;
        	            for (int i = 1; i < listSize; i++){
                        holeSize = list[i].startingAddr - list[i-1].endingAddr;
            	            if (holeSize > blockSize){
            	                bestSize = holeSize;
            	                best = i;
            	                if (holeSize < bestSize){
            	                    best = i;
            	                    bestSize = holeSize;
            	                } 
            	            }
        	            }
        	            if (list[0].startingAddr > 0){
            	           if ((list[0].startingAddr > blockSize) && (blockSize <= bestSize)){
            	               best = 0;
            	               bestSize = list[0].startingAddr;
            	           }
            	       }
            	       if (blockSize == totalSize - list[listSize].endingAddr){
            	           best = listSize;
            	       }
        	            //listSize++;
        	            temp = malloc((listSize) * sizeof(linkedList));
                	    //if the index to delete is not the first index, copy everything before that index
                	    if (best != 0){
                            memmove(&temp, &list, sizeof(linkedList)); 
                	    }
                	    //if the index to delete is not the second to last element, copy everything after that index
                        if (best != (listSize)){
                            memmove(temp + best + 1, list + best, (listSize + best + 2) * sizeof(linkedList)); 
                        }
                        
                        list = temp;
                        if (best != 0){
                	        list[best].id = blockId;
                	        list[best].startingAddr = list[best-1].endingAddr;
                	        list[best].endingAddr = list[best].startingAddr + blockSize;
                        } else {
                            list[best].id = blockId;
                	        list[best].startingAddr = 0;
                	        list[best].endingAddr = blockSize;
                        }
    	            } else { //first-fit
    	                bestSize = blockSize;
        	            for (int i = 1; i < listSize; i++){
        	                holeSize = list[i].startingAddr - list[i-1].endingAddr;
        	                if (holeSize != bestSize){
                	            if (holeSize > blockSize){
                	                bestSize = holeSize;
                	                best = i;
                	                if (holeSize < bestSize){
                	                    best = i;
                	                    bestSize = holeSize;
                	                } 
                	            }
        	                }
        	            }
        	            if (list[0].startingAddr > 0){
            	           if ((list[0].startingAddr > blockSize) && (blockSize <= bestSize)){
            	               best = 0;
            	               bestSize = list[0].startingAddr;
            	           }
            	       }
        	            //listSize++;
        	            temp = malloc((listSize) * sizeof(linkedList));
                	    //if the index to delete is not the first index, copy everything before that index
                	    if (best != 0){
                            memmove(&temp, &list, sizeof(linkedList)); 
                	    }
                	    //if the index to delete is not the second to last element, copy everything after that index
                        if (best != (listSize)){
                            memmove(temp + best + 1, list + best, (listSize + best + 2) * sizeof(linkedList)); 
                        }
                        
                        list = temp;
                        if (best != 0){
                	        list[best].id = blockId;
                	        list[best].startingAddr = list[best-1].endingAddr;
                	        list[best].endingAddr = list[best].startingAddr + blockSize;
                        } else {
                            list[best].id = blockId;
                	        list[best].startingAddr = 0;
                	        list[best].endingAddr = blockSize;
                        }
    	            }
    	        }
	        }
	    }
	    size -= blockSize;
	    listSize++;
	    printTable();
	    //printf("%d", best);
	}
		
		// if hole is large enough for block
			// if first-fit algorithm
				// set start & end fields of new block & add block into linked list
				// reduce remaining available memory and return
			// else--best-fit algorithm
				// if hole is smaller than best so far
					// set values of best start & best end & best hole size so far
					// update best block & advance next block 
	// set start & end fields of new block & add block into linked list 	  
	// reduce remaining available memory and return
	return;	
}
	

/********************************************************************/
void deallocate() {
	// declare local variables
	int blockId, toDelete, blockSize;
	int flag = 0;
	linkedList temp;
	// prompt for block id
	printf("Enter block id: ");
	scanf("%d", &blockId);
	for (int i = 0; i < listSize; i++){
	    if (list[i].id == blockId){
	        flag++;
	        toDelete = i;
	    }
	}
	if (flag == 0){
	    printf("Error: Block id not found. ");
	    return;
	} else {
	    blockSize = list[toDelete].endingAddr - list[toDelete].startingAddr;
	    //allocate a temp array that is sized one element less
	    temp = malloc((listSize) * sizeof(linkedList));
	    //if the index to delete is not the first index, copy everything before that index
	    if (toDelete != 0){
            memmove(&temp, &list, sizeof(linkedList)); 
	    }
	    //if the index to delete is not last element, copy everything after that index
        if (toDelete != (listSize)){
            memmove(temp + toDelete, list + toDelete + 1, (listSize - toDelete + 1) * sizeof(linkedList)); 
        }
        list = temp;
	    listSize--;
	    size += blockSize;
        isDeallocated = 1;
	}
	printTable();
	// until end of linked list is reached or block id is found 
		// traverse list
	// if end of linked list reached, print block id not found
	// else remove block and deallocate memory
	return;
}


/********************************************************************/
void defragment() {
	// declare local variables 	
	int holeSize;
	// until end of list is reached
	// calculate current hole size
    // adjust start & end fields of current block to eliminate hole
	for (int i = 1; i < listSize; i++){
	    holeSize = list[i].startingAddr - list[i-1].endingAddr;
	    if (holeSize > 0){
	        list[i].startingAddr = list[i-1].endingAddr;
	        list[i].endingAddr -= holeSize;
	    }
	}
	printTable();
	return;
}


/********************************************************************/
void freeMemory() {
	if (list == NULL){
	    return;
	} else {
	    free(list);
	    printf("\nMemory freed. Goodbye.");
	}
	return;
}


/***************************************************************/
int main() {
	/* declare local vars */
	int menuInput, done = 0, process;
	/* while user has not chosen to quit */
	while (done == 0){
		/* print menu of options */
		printf("\nMemory allocation \n-----------------\n1) Enter parameters\n2) Allocate memory for block\n3) Deallocate memory for block\n4) Defragment memory\n5) Quit program\n\nEnter selection: ");
		/* prompt for menu selection */
		scanf("%d", &menuInput);
		switch (menuInput){
		    case 1:
		        enterParameters();
		        break;
		    
		    case 2:
		        allocate();
		        break;
		        
		    case 3:
		        deallocate();
		        break;
		    
		    case 4: 
		        defragment();
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