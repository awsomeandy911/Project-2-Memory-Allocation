#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//struct that stores the process objects
struct Process
{
	int startMemory;
	int endMemory;
	int size;
    	char processID[7];
    
}; typedef struct Process Process;

//compares the processes
int processCompare(const void * left, const void * right)
{
	const Process *a =(const void*) left;
	const Process *b = (const void*) right;
	return (*a).startMemory - (*b).startMemory;

}

//function to find specific process
void findProcess(char temp[],Process arr[],int count)
{
 	short marker = 0;
	for(int i = 0; i < count; i++)
    {
		if(strcmp(temp,arr[i].processID)==0)
        {
			marker = 1;
			printf("(%s, %d, %d)\n", arr[i].processID, arr[i].size, arr[i].startMemory);
		}

	}

	if(marker == 0 )
    {
		printf("FAULT\n");
	}
}

//function for first fit memory allocation algorithim
short firstFit(char temp[], int bytes, int count,  Process arr[], int N)
{
	int start;
	short marker =0;
	int free;
	
	if(bytes <= 0)
    {

		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
	if(count == 0)
    {
		free = N;
	}
    else
    {
		free = arr[0].startMemory - 0;
	}

	if(bytes >0 && free >=bytes)
    {
		start = 0;
		marker =1;
	}
	if(marker == 0)
    {
		for(int i =0; i < count; i++)
        {
			if(i == count-1)
            {
				free = N - arr[i].endMemory;
			}
            else
            {
				free = arr[i+1].startMemory - arr[i].endMemory;
			}	
			if(free>=bytes)
            {
				start = arr[i].endMemory;
				marker = 1;
				break;
			}

		}
	}

	if(marker == 1)
    {
		strncpy(arr[count].processID, temp,7);
		arr[count].startMemory = start;
		arr[count].endMemory = arr[count].startMemory + bytes;
		arr[count].size = bytes;
			
		printf("ALLOCATED %s %d \n",arr[count].processID, arr[count].startMemory);
	
		qsort(arr,count+1,sizeof(Process),processCompare);
		return 1;
	}
	else
    {
		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}

}

//function for best fit memory allocation algorithim
short bestFit(char temp[], int bytes, int count,  Process arr[], int N)
{
	int start;
	int min = INT_MAX ;
	short marker = 0;
	int free;

	if(bytes <= 0)
    {

		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
	if(bytes > 0)
    {
	    if(count == 0 )
        {
		    if(N >= bytes)
            {
		        marker = 1;
		        start =0;
		    }
	    }	
	    else
        {
		free = arr[0].startMemory -0;
		    if( free < min && free >= bytes)
            {
			    min = free;
			    start =0;
			    marker = 1;
	        }
	    }
	}
	for(int i = 0; i < count; i++)
    {
		
		if(i == count-1)
        {
			free = N - arr[i].endMemory;
		}
		else
        {
			free = arr[i+1].startMemory - arr[i].endMemory;
		}
		if(free < min && free >= bytes)
        {
			min = free;
			start = arr[i].endMemory ;
			marker = 1;
		}
	}

	if(marker == 1)
    {
		strncpy(arr[count].processID, temp,7);
		arr[count].startMemory = start;
		arr[count].endMemory = arr[count].startMemory + bytes;
		arr[count].size = bytes;
		
		printf("ALLOCATED %s %d \n",arr[count].processID, arr[count].startMemory);
		qsort(arr,count+1,sizeof(Process),processCompare);

		return 1;
	}
	else
    {
		printf("FAIL REQUEST %s %d\n", temp, bytes);
		return 0;
	}
	

}

//function for worst fit memory allocation algorithim
short  worstFit(char temp[], int bytes,  int count, Process arr[], int N)
{
	int start;
	int max =INT_MIN;
	short marker = 0;
	int free;
    
	if(bytes <= 0)
    {

		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
	if(count == 0 && bytes <= N )
    {
		start = 0;
		marker = 1;
	}	
	if(count !=0)
    {
		free = arr[0].startMemory - 0;
		if(bytes > 0 && free >max && free >= bytes)
        {
			max = free;
			start=0;
			marker = 1;
		}
	}

	for(int i = 0; i < count; i++)
    {
		if(i == count-1)
        {
			free = N - arr[i].endMemory;
		} 
		else
        {
			free = arr[i+1].startMemory - arr[i].endMemory;
		}
		if(free > max && free >= bytes)
        {
			max = free;
			start = arr[i].endMemory;
			marker = 1;
		}
	}
	if(marker == 1)
    {
		strncpy(arr[count].processID, temp,7);
		arr[count].startMemory = start;
		arr[count].endMemory = arr[count].startMemory + bytes;
		arr[count].size = bytes;
			
		printf("ALLOCATED %s %d \n",arr[count].processID, arr[count].startMemory);
	
		qsort(arr,count+1,sizeof(Process),processCompare);
		return 1;
	}
	else
    {
		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
}

//function for next fit memory allocation algorithim
short  nextFit(char last[], char temp[], int bytes, int count,  Process arr[], int N)
{
	int start;
	short marker =0;
	int free;
	int lastidx = -1;
	int index;
	

	if(bytes <= 0)
    {

		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
	if(count == 0 && bytes <= N)
    {
		start = 0;
		marker =1;
	}	
	if(count != 0)
    {
		for(int i =0; i < count; i++)
        {
		    if(strcmp(last,arr[i].processID)==0)
            {
			    lastidx = i;
			    index = i;
		    }
		}
	}
	
	if(lastidx != -1)
    {
		for(int i = 0; i <= count; i++) 
		{
		    if(index == count-1)
            {
		    	free = N - arr[index].endMemory;
		    }
                else if(index == count)
                {
			        free = arr[0].startMemory - 0;
		        }
		            else
                    {
		            	free = arr[index+1].startMemory - arr[index].endMemory;
		            }	

		
		if(free>=bytes)
        {
			start = arr[index].endMemory;
			marker = 1;
			break;
		}
		index++;
		index = index % (count+1);
		}
	}
	

	if(marker == 1)
    {
		strncpy(arr[count].processID, temp,7);
		arr[count].startMemory = start;
		arr[count].endMemory = arr[count].startMemory + bytes;
		arr[count].size = bytes;
			
		printf("ALLOCATED %s %d \n",arr[count].processID, arr[count].startMemory);
	
		qsort(arr,count+1,sizeof(Process),processCompare);
		return 1;
	}
	else
    {
		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
}

//function to release memory space
short releaseMem(char temp[],  int count,  Process arr[])
{
	short marker = 0;
	int index;
	for(int i = 0; i < count; i++)
    {
		if(strcmp(temp,arr[i].processID) == 0)
        {
			marker = 1;
			index = i;
		}
	}

	if(marker == 1)
    {
		printf("FREE %s %d %d \n",arr[index].processID, arr[index].size, arr[index].startMemory);
		for(int i = index; i <count-1; i++)
        {
			arr[i] = arr[i+1];
		}
		
		return 1;
	}
	else
    {
		printf("FAIL RELEASE %s\n", temp);
		return 0;
	}
}

//prints assigned memory space
void printAssigned(int count,  Process arr[])
{
	if(count == 0)
    {
		printf("NONE");
	}
	else
    {
		for (int i = 0; i < count; i++)
        {
			printf("(%s, %d, %d) ",arr[i].processID, arr[i].size, arr[i].startMemory);
		}

	}

	printf("\n");
}

//prints available memory space
void printAvailable(int count, Process arr[], int N)
{
	short marker = 0;
	int free;
	if(count == 0)
    {
		marker =1;
		printf("(%d, %d) ",N, 0);
	}
	else
	{
		free = arr[0].startMemory-0 ;
		if(free > 0)
        {
			marker = 1;
			printf("(%d, %d) ",free, 0);
		}
	}
	for(int i =0; i < count; i++)
    {
		if(i == count-1)
        {
			free = N-arr[i].endMemory;
			if(free > 0)
            {
				marker = 1;
				printf("(%d, %d) ",free,arr[i].endMemory);
			}
		}
		else
        {
			free = arr[i+1].startMemory - arr[i].endMemory;
			if(free > 0 )
            {
				marker =1;
				printf("(%d, %d) ", free,arr[i].endMemory);
			}
		}
	}
	if(marker == 0)
    {
		printf("FULL");
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	
	FILE *filePointer;
	filePointer = fopen(argv[3],"r");
    Process arr[200000];

	int count = 0;
	int N = atoi(argv[2]);
	char input[20];
	char comment[] = {"#"};
	char last[7];

	while(fscanf(filePointer,"%s",input) ==1)
    {
		if(strcmp(comment,input) == 0)
        {
			fscanf(filePointer, "%*[^\n]\n");
			continue;
		}
        else if(strcmp("REQUEST", input) == 0)
        {
			char temp[7];
			int bytes;
			if(fscanf(filePointer,"%s",input) == 1)
            {
				strncpy(temp,input,7);
			
			}
			if(fscanf(filePointer, "%s", input) == 1)
            {
				bytes =atoi(input);
			}

			if(strcmp("BESTFIT",argv[1]) == 0)
            {
				if(bestFit(temp,bytes,count,arr,N)==1)
                {
					count++;
				}
	
			}
            else if(strcmp("FIRSTFIT",argv[1])==0)
            {
				if(firstFit(temp,bytes,count,arr,N)==1)
                {
					count++;
				}
			
			
			}
            else if(strcmp("NEXTFIT",argv[1])==0)
            {
				if(nextFit(last,temp,bytes,count,arr,N)==1)
                {
					count++;
					strncpy(last,temp,7);
				}
				
			}
            else if(strcmp("WORSTFIT",argv[1])==0)
            {
				if(worstFit(temp,bytes,count,arr,N) ==1)
                {
					count++;
				}
				
			}
		}
        
        else if(strcmp("RELEASE",input)==0)
        {
			char temp[7];
			if(fscanf(filePointer,"%s",input) == 1)
            {
				strncpy(temp,input,7);
			}
			
			if(releaseMem(temp, count, arr)==1)
            {
				count--;
			}
			
		}
        else if(strcmp("LIST",input) == 0)
        {
			fscanf(filePointer,"%s",input);
			if(strcmp("ASSIGNED",input) == 0)
            {
				printAssigned(count,arr);
			}
			else
            {
				printAvailable(count,arr,N);
			}
		}
        else if(strcmp("FIND",input) == 0)
        {
			if(fscanf(filePointer,"%s",input) == 1)
            {
				findProcess(input,arr,count);
			}
		}	
	
	}
}
