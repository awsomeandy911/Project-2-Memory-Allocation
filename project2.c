#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct process
{
	char pid[7];
	int startMemory;
	int endMemory;
	int size;
};

typedef struct process process;


int processCompare(const void * left, const void * right)
{
	const process *a =(const void*) left;
	const process *b = (const void*) right;
	return (*a).startMemory - (*b).startMemory;

}

void find(char temp[],process array[],int count)
{
 	short flag = 0;
	for(int i =0; i < count; i++){
		if(strcmp(temp,array[i].pid)==0){
			flag = 1;
			printf("(%s, %d, %d)\n", array[i].pid, array[i].size, array[i].startMemory);
		}

	}

	if(flag == 0 ){
		printf("FAULT\n");
	}
}

short bestFit(char temp[], int bytes, int count,  process array[], int N)
{
	int start;
	int min =INT_MAX ;
	short flag = 0;
	int free;

	if(bytes <= 0)
    {

		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
	if(bytes > 0){
	if(count == 0 ){
		if(N >= bytes){
		flag = 1;
		start =0;
		}
	}	
	else{
		free = array[0].startMemory -0;
		if( free < min && free >= bytes){
			min = free;
			start =0;
			flag = 1;
		}
	}
	}
	for(int i = 0; i < count; i++){
		
		if(i == count-1){
			free = N - array[i].endMemory;
		}
		else{
			free = array[i+1].startMemory - array[i].endMemory;
		}
		if(free < min && free >= bytes){
			min = free;
			start = array[i].endMemory ;
			flag = 1;
		}
	}
	if(flag == 1){
		strncpy(array[count].pid, temp,7);
		array[count].startMemory = start;
		array[count].endMemory = array[count].startMemory + bytes;
		array[count].size = bytes;
		
		printf("ALLOCATED %s %d \n",array[count].pid, array[count].startMemory);
		qsort(array,count+1,sizeof(process),processCompare);

		return 1;
	}
	else{
		printf("FAIL REQUEST %s %d\n", temp, bytes);
		return 0;
	}
	

}

short firstFit(char temp[], int bytes, int count,  process array[], int N)
{
	int start;
	short flag =0;
	int free;
	
	if(bytes <= 0){

		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
	if(count == 0){
		free = N;
	}else{
		free = array[0].startMemory - 0;
	}

	if(bytes >0 && free >=bytes){
		start = 0;
		flag =1;
	}
	if(flag == 0){
		for(int i =0; i < count; i++){
			if(i == count-1){
				free = N - array[i].endMemory;
			}else{
				free = array[i+1].startMemory - array[i].endMemory;
			}	
			if(free>=bytes){
				start = array[i].endMemory;
				flag = 1;
				break;
			}

		}
	}

	if(flag == 1){
		strncpy(array[count].pid, temp,7);
		array[count].startMemory = start;
		array[count].endMemory = array[count].startMemory + bytes;
		array[count].size = bytes;
			
		printf("ALLOCATED %s %d \n",array[count].pid, array[count].startMemory);
	
		qsort(array,count+1,sizeof(process),processCompare);
		return 1;
	}
	else{
		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}

}

short  nextFit(char last[], char temp[], int bytes, int count,  process array[], int N)
{
	int start;
	short flag =0;
	int free;
	int lastidx = -1;
	int index;
	

	if(bytes <= 0){

		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
	if(count == 0 && bytes <= N){
		start = 0;
		flag =1;
	}	
	if(count != 0){
		for(int i =0; i < count; i++){
		if(strcmp(last,array[i].pid)==0){
			lastidx = i;
			index = i;
		}
		}

	}
	
	if(lastidx != -1){
		for(int i = 0; i <= count; i++) 
		{
		if(index == count-1){
			free = N - array[index].endMemory;
		}else if(index == count){
			free = array[0].startMemory - 0;
		}
		else{
			free = array[index+1].startMemory - array[index].endMemory;
		}	

		
		if(free>=bytes){
			start = array[index].endMemory;
			flag = 1;
			break;
		}



		index++;
		index = index % (count+1);

		}
	}
	

	if(flag == 1){
		strncpy(array[count].pid, temp,7);
		array[count].startMemory = start;
		array[count].endMemory = array[count].startMemory + bytes;
		array[count].size = bytes;
			
		printf("ALLOCATED %s %d \n",array[count].pid, array[count].startMemory);
	
		qsort(array,count+1,sizeof(process),processCompare);
		return 1;
	}
	else{
		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
}

short  worstFit(char temp[], int bytes,  int count, process array[], int N)
{
	int start;
	int max =INT_MIN;
	short flag = 0;
	int free;
	if(bytes <= 0){

		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
	if(count == 0 && bytes <= N ){
		start = 0;
		flag = 1;
	}	
	if(count !=0){
		free = array[0].startMemory - 0;
		if(bytes > 0 && free >max && free >= bytes){
			max = free;
			start=0;
			flag = 1;
		}
	}

	for(int i = 0; i < count; i++){
		
		if(i == count-1){
			free = N - array[i].endMemory;
		} 
		else{
			free = array[i+1].startMemory - array[i].endMemory;
		}
		if(free > max && free >= bytes){
			max = free;
			start = array[i].endMemory;
			flag = 1;
		}
	}
	if(flag == 1){
		strncpy(array[count].pid, temp,7);
		array[count].startMemory = start;
		array[count].endMemory = array[count].startMemory + bytes;
		array[count].size = bytes;
			
		printf("ALLOCATED %s %d \n",array[count].pid, array[count].startMemory);
	
		qsort(array,count+1,sizeof(process),processCompare);
		return 1;
	}
	else{
		printf("FAIL REQUEST %s %d\n", temp, bytes);
			return 0;
	}
}

short release(char temp[],  int count,  process array[])
{
	short flag = 0;
	int index;
	for(int i = 0; i < count; i++){
		if(strcmp(temp,array[i].pid) == 0){
			flag = 1;
			index = i;
		}
	}

	if(flag == 1){
		printf("FREE %s %d %d \n",array[index].pid, array[index].size, array[index].startMemory);
		for(int i = index; i <count-1; i++){
			array[i] = array[i+1];
		}
		
		return 1;
	}
	else{
		printf("FAIL RELEASE %s\n", temp);
		return 0;
	}
}

void listAssigned(int count,  process array[])
{
	if(count == 0){
		printf("NONE");
	}
	else{
		for (int i = 0; i < count; i++){
			printf("(%s, %d, %d) ",array[i].pid, array[i].size, array[i].startMemory);
		}

	}

	printf("\n");
}

void listAvaiable(int count, process array[], int N)
{
	short flag = 0;
	int free;
	if(count == 0){
		flag =1;
		printf("(%d, %d) ",N, 0);
	}
	else
	{
		free = array[0].startMemory-0 ;
		if(free > 0){
			flag = 1;
			printf("(%d, %d) ",free, 0);
		}
	}
	for(int i =0; i < count; i++){
		if(i == count-1){
			free = N-array[i].endMemory;
			if(free > 0){
				flag = 1;
				printf("(%d, %d) ",free,array[i].endMemory);
			}
		}
		else{
			free = array[i+1].startMemory - array[i].endMemory;
			if(free > 0 ){
				flag =1;
				printf("(%d, %d) ", free,array[i].endMemory);
			}
		}
	}
	if(flag == 0){
		printf("FULL");
	}
	printf("\n");
}




int main(int argc, char** argv){
	
	FILE *fptr;
	fptr = fopen(argv[3],"r");
	int count = 0;
	int N = atoi(argv[2]);
	char input[20];
	char comment[] = {"#"};
	char last[7];
	process array[200000];

	while(fscanf(fptr,"%s",input) ==1){
		if(strcmp(comment,input) == 0){
			fscanf(fptr, "%*[^\n]\n");
			continue;
		}else if(strcmp("REQUEST", input) == 0){
			char temp[7];
			int bytes;
			if(fscanf(fptr,"%s",input) == 1){
				strncpy(temp,input,7);
			
			}
			if(fscanf(fptr, "%s", input) == 1){
				bytes =atoi(input);
			}

			if(strcmp("BESTFIT",argv[1]) == 0){
				if(bestFit(temp,bytes,count,array,N)==1){
					count++;
				}
	
			}else if(strcmp("FIRSTFIT",argv[1])==0){
				if(firstFit(temp,bytes,count,array,N)==1){
					count++;
				}
			
			
			}else if(strcmp("NEXTFIT",argv[1])==0){
				if(nextFit(last,temp,bytes,count,array,N)==1){
					count++;
					strncpy(last,temp,7);
				}
				
			}else if(strcmp("WORSTFIT",argv[1])==0){
				if(worstFit(temp,bytes,count,array,N) ==1){
					count++;
				}
				
			}
		}else if(strcmp("RELEASE",input)==0){
			char temp[7];
			if(fscanf(fptr,"%s",input) == 1){
				strncpy(temp,input,7);
			}
			
			if(release(temp, count, array)==1){
				count--;
			}
			
		}else if(strcmp("LIST",input) == 0){
			fscanf(fptr,"%s",input);
			if(strcmp("ASSIGNED",input) == 0){
				listAssigned(count,array);
			}
			else{
				listAvaiable(count,array,N);
			}
		}else if(strcmp("FIND",input) == 0){
			if(fscanf(fptr,"%s",input) == 1){
				find(input,array,count);
			}
		}	
	
	}
}
