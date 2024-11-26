#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main() {
	printf("%d about to create 2 child processes\n", getpid());
	int ppid = getpid();

	pid_t p_1; pid_t p_2;
	p_1 = fork();

	if (p_1 < 0) {
		perror("fork fail");
		exit(1);
	} else if (p_1 == 0) {
		p_2 = fork();
		if (p_2 < 0) {
			perror("fork fail");
		} else if (p_2 == 0) {
			// child2
			int pid = getpid();
			srand(pid);
			int sec = rand() % 5 + 1;
			printf("%d %dsec\n", pid, sec);
			sleep(sec);
			printf("%d finished after %d sec\n", pid, sec);
			exit(sec);
		} else {
			// child 1
			int pid = getpid();
			srand(pid);
			int sec = rand() % 5 + 1;
			printf("%d %dsec\n", pid, sec);
			sleep(sec);
			printf("%d finished after %d sec\n", pid, sec);
			exit(sec);
		}
	} else {
		// parent
		int status;
		while (1) {
			pid_t wpid = waitpid(p_1, &status, WNOHANG);

			if (wpid == -1) {
				exit(0);
			}	else if (wpid == 0) {
				sleep(1);
			} else {
				printf("Main process %d is done. Child %d slept for %d seconds\n", ppid, p_1, WEXITSTATUS(status));
				break;
			}
		}	
	}
}
