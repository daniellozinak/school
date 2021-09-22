#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <sys/wait.h>

int main(){

	const int n_child = 20;
	for (unsigned i = 1; i <= n_child; i++) {
		int j = fork();
		if (j ==0) {
			std::cout << "child " << i << " sleeping for " << i*1000 << "ms\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(i*1000));
			exit(i);
		}
	}


	int status;
	while(waitpid(-1,&status,0)>0){
		int return_value = status >> 8;
		std::cout<< "child has returned [" << return_value << "] \n";
	}
	
	return 0;
}