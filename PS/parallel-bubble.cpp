
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <string>


bool is_sorted = false;
const unsigned limit = 50;

void swap(int &a, int &b){
	a = a + b;
	b = a - b;
	a = a - b;
}

void bubble_sort(int *& arr, int length){
	for(int i = 0; i< length; i++) {
		bool swap_flag = false;
		for (int j = 0; j < length - 1; j++){
			if(arr[j] > arr[j+1]) {
				swap(arr[j],arr[j+1]);
				swap_flag = true; 
			}
		}
		if (!swap_flag) { break; }
	}
}

void fill(int *&arr, int length, int range) {
	for(int i = 0; i< length; i++) {
		arr[i] = rand() % range +1;
	}
	
}

void print(int *&arr, int length) {
	for(int i = 0; i< length; i++) {
		std::cout << arr[i] << "\n";
	}
}

void fork_swap(int *&arr,int length, int offset,int iteration) {
	for(int i = offset; i < length - 1; i+=2) {
		int j = fork();
		if (j == 0) {
			if (arr[i] > arr[i+1]) {
				swap(arr[i],arr[i+1]);
				exit(1 + iteration);
			}
			exit(0);
		}
	}
}

void parallel_sort(int *& arr, int length) {
	unsigned i = 0;
	
	while(!is_sorted) {
		fork_swap(arr,length,(int)i%2==0,i);
		i++;
		is_sorted = (i > limit);
	}

}


int main(){

	int shmid;
	int *shared_memory;
	int shmkey = getuid();
	const unsigned count = 33;
	
	shmid = shmget(shmkey, count*sizeof(int), 0633|IPC_CREAT);
	shared_memory = (int*)shmat(shmid,NULL,0);
	
	fill(shared_memory, count,100);
	std::cout << "Before\n";
	print(shared_memory, count);
	parallel_sort(shared_memory,count);
	
	shmctl(shmid, IPC_RMID, 0);
	int status;
	unsigned no_swap_count = 0; // if no_swap_count = count -1, its sorted
	while(waitpid(-1,&status,0)>0){
		int return_value = status >> 8;
		no_swap_count = (return_value == 0)? no_swap_count + 1: 0;
		if( no_swap_count == count -1) {
			is_sorted = true;
			std::cout << "After\n";
			print(shared_memory, count);
			return 0;
		}
		
	}
	
	return 0;
}