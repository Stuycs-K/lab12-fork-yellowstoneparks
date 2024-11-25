#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("%d about to create 2 child processes\n", getpid());

	pid_t p_1; pid_t p_2;
	p_1 = fork();

	if (p_1 < 0) {
		perror("fork fail");
		exit(1);
	} else if (p_1 == 0) {
		// child1
		printf("child 1\n");

		p_2 = fork();
		if (p_2 < 0) {
			perror("fork fail");
		} else if (p_2 == 0) {
			// child2
			printf("child 2\n");
		} else {
			// back to child 1
			exit(1);
		}
	} else {
		// parent
		printf("parent\n");
	}
}
