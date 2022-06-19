#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Declare global variables, including dynamic array to store sequence of traversed tracks
int *tracks;
int size, startingTrack, distance;
/*********************************************************/
void enterParameters() {
    // prompt for the sequence size
	printf("Enter size of sequence: ");
	scanf("%d", &size);
	printf("Enter starting track: ");
	scanf("%d", &startingTrack);
	
	size--;
	tracks = (int*)malloc(size * sizeof(int));
	
	printf("Enter sequence of tracks to seek: ");
	for(int i = 0; i < size; i++)
        scanf("%d", &tracks[i]);
        
	return;
}


	// allocate memory for the sequence of traversed tracks
	// prompt for starting track, store in index 0
	// prompt for sequence of tracks to seek, store in index 1 to "sequence size-1"

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int cmpfuncDesc (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}
/*********************************************************/
void fifo() {
	// declare local variables	
	distance = abs(startingTrack - tracks[0]);
	printf("Traversed sequence: %d ", startingTrack);

	// print sequence of traversal
	for(int i = 0; i < size-1; i++){
        printf("%d ", tracks[i]);
        distance += abs(tracks[i] - tracks[i+1]);
	}
	
	// calculate total distance of traversed tracks
	// print total distance of tracks traversed
	printf("%d\nDistance: %d\n", tracks[size-1], distance);
	
	return;
} 	


/*********************************************************/
void sstf() {
	// declare local variables
    int best[size];
    int distances[size];
    int visited[size];
    int distance = 0;
    
    // initialize current track and distance traversed to starting track
    for (int i = 0; i < size; i++){
        distances[i] = abs(startingTrack - tracks[i]);
        visited[i]= 0;
    }
    
    qsort(distances, size, sizeof(int), cmpfunc);
    
    for (int i =0; i < size; i++){
        for (int j = 0; j < size; j++){
            if ((distances[i] == abs(startingTrack - tracks[j])) && (visited[j] == 0)){
                best[i] = j;
                visited[j] = 1;
                break;
            }
        }
    }
    distance += abs(startingTrack - tracks[best[0]]);
    for (int i = 1; i < size; i++){
       distance += abs(tracks[best[i-1]] - tracks[best[i]]);
    }
    printf("Traversed sequence: %d ", startingTrack);
    for (int i = 0; i < size; i++){
        printf("%d ", tracks[best[i]]);
    }
    
    // print total distance traversed
    printf("\nDistance: %d", distance);
    
	return;
} // "OPTION #3" 


/*********************************************************/
void scan() {
	// declare local variables
	int direction;
	int increasing[size];
	int decreasing[size];
	int sorted[size];
	int visited[size];
	int distance = 0;
	
	printf("Enter initial direction: (0=decreasing, 1=increasing): ");
	scanf("%d", &direction);
	
	for (int i = 0; i < size; i++){
	        increasing[i] = tracks[i];
	        decreasing[i] = tracks[i];
	        visited[i] = 0;
	        sorted[i] = 0;
	    }
	    
	qsort(increasing, size, sizeof(int), cmpfunc);
	qsort(decreasing, size, sizeof(int), cmpfuncDesc);
	//prompt for initial direction (0=descreasing, 1=increasing)
	if (direction == 1){
    	for (int i = 0; i < size; i++){
    	    for (int j = 0; j < size; j++){
    	        if ((increasing[j] > startingTrack) && (visited[j] == 0)){
    	            sorted[i] = increasing[j];
    	            visited[j] = 1;
    	            break;
    	        }
    	    }
    	}
    	
    	for (int i = 0; i < size; i++){
    	    if (sorted[i] != 0){
    	        visited[i] = 1;
    	    } else {
    	        visited[i] = 0;
    	    }
    	}
    	
    	for (int i = 0; i < size; i++){
    	    for (int j = 0; j < size; j++){
    	        if ((decreasing[j] < startingTrack) && (visited[j] == 0)){
    	            sorted[j] = decreasing[j];
    	            visited[j] = 1;
    	            break;
    	        }
    	    }
    	} 
	} else if (direction == 0){
	    for (int i = 0; i < size; i++){
    	    for (int j = 0; j < size; j++){
    	        if ((decreasing[j] < startingTrack) && (visited[j] == 0)){
    	            sorted[i] = decreasing[j];
    	            visited[j] = 1;
    	            break;
    	        }
    	    }
    	} 
    	
    	    	
    	for (int i = 0; i < size; i++){
    	    if (sorted[i] != 0){
    	        visited[i] = 1;
    	    } else {
    	        visited[i] = 0;
    	    }
    	}
    	
	    for (int i = 0; i < size; i++){
    	    for (int j = 0; j < size; j++){
    	        if ((increasing[j] > startingTrack) && (visited[j] == 0)){
    	            sorted[j] = increasing[j];
    	            visited[j] = 1;
    	            break;
    	        }
    	    }
    	}
	} else {
	    printf("Invalid response.");
	    return;
	}
	
 	// print total distance traversed
 	distance += abs(startingTrack - sorted[0]);
    for (int i = 1; i < size; i++){
       distance += abs(sorted[i-1] - sorted[i]);
    }
    
    printf("Traversed sequence: %d ", startingTrack);
 	for (int i = 0; i < size; i++){
	   printf("%d ", sorted[i]);
    }
    
    printf("\nDistance: %d", distance);
    	
	return;
} // "OPTION #4"


/*********************************************************/
void cscan() {
	// declare local variables
	int increasing[size];
	int sorted[size];
	int visited[size];
	int distance = 0;
	
	for (int i = 0; i < size; i++){
	   increasing[i] = tracks[i];
	   visited[i] = 0;
	   sorted[i] = 0;
	}
	    
	qsort(increasing, size, sizeof(int), cmpfunc);

    	for (int i = 0; i < size; i++){
    	    for (int j = 0; j < size; j++){
    	        if ((increasing[j] > startingTrack) && (visited[j] == 0)){
    	            sorted[i] = increasing[j];
    	            visited[j] = 1;
    	            break;
    	        }
    	    }
    	}
    	
    	for (int j = 0; j < size; j++){
    	    if (increasing[j] < startingTrack){ 
    	       for (int i = 0; i < size; i++){
    	           if ((sorted[i] == 0) && (visited[j] == 0)){
    	               sorted[i] = increasing[j];
    	               visited[j] = 1;
    	               break;
    	           }
    	       }
    	    }
    	}
	
 	// print total distance traversed
 	distance += abs(startingTrack - sorted[0]);
    for (int i = 1; i < size; i++){
       distance += abs(sorted[i-1] - sorted[i]);
    }
    
    printf("Traversed sequence: %d ", startingTrack);
 	for (int i = 0; i < size; i++){
	   printf("%d ", sorted[i]);
    }
    
    printf("\nDistance: %d", distance);
    	
	return;
} // "OPTION #5


/***************************************************************/
void freeMemory() {
	// if sequence is not NULL, free sequence
	if (tracks != NULL){
	    free(tracks);
	}
	printf("Memory freed. Goodbye.");
	return;
} // "OPTION #6


/***************************************************************/
int main() {
	/* declare local vars */
	int menuInput, done = 0;
	/* while user has not chosen to quit */
	while (done == 0){
		/* print menu of options */
		printf("\n\nDisk scheduling\n---------------\n1) Enter parameters\n2) Calculate distance to traverse tracks using FIFO\n3) Calculate distance to traverse tracks using SSTF\n4) Calculate distance to traverse tracks using Scan\n5) Calculate distance to traverse tracks using C-Scan\n6) Quit program and free memory\n\nEnter Selection: ");
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
                sstf();
		        break;
		    
		    case 4:
		        scan();
		        break;
		    
		    case 5:
		        cscan();
		        break;
		        
		    case 6:
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