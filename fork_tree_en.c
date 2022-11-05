#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

	printf("[CHILD] -- 0_1 [%d] | [PARENT] -- [%d]\n", getpid(), getppid());

	pid_t pid_1_1;

	if ((pid_1_1 = fork()) == 0) {

		printf("[FORK] %d --> %d\n", getppid(), getpid());
		printf("[CHILD] -- 1_2 [%d] | [PARENT] -- [%d]\n", getpid(), getppid());
		printf("[EXIT] 1_2 [%d]\n", getpid());

		exit(0);
	}

	wait(0);

	pid_t pid_1_2;

	if ((pid_1_2 = fork()) == 0) {

		printf("[FORK] %d --> %d\n", getppid(), getpid());
		printf("[CHILD] -- 1_3 [%d] | [PARENT] -- [%d]\n", getpid(), getppid());

		pid_t pid_2_4;

		if ((pid_2_4 = fork()) == 0) {

			printf("[FORK] %d --> %d\n", getppid(), getpid());
			printf("[CHILD] -- 2_5 [%d] | [PARENT] -- [%d]\n", getpid(), getppid());

			pid_t pid_3_6;

			if ((pid_3_6 = fork()) == 0) {

				printf("[FORK] %d --> %d\n", getppid(), getpid());
				printf("[CHILD] -- 2_7 [%d] | [PARENT] -- [%d]\n", getpid(), getppid());
				printf("[EXIT] 2_7 [%d]\n", getpid());

				exit(0);
			}

			wait(0);

			printf("[EXIT] 2_5 [%d]\n", getpid());
			exit(0);
		}

		wait(0);

		pid_t pid_2_5;

		if ((pid_2_5 = fork()) == 0) {

			printf("[FORK] %d --> %d\n", getppid(), getpid());
			printf("[CHILD] -- 2_6 [%d] | [PARENT] -- [%d]\n", getpid(), getppid());

			printf("[ORDER 66] 2_6 [%d] executes order 66 (pwd)\n", getpid());
			execvp("pwd", argv);

			printf("[EXIT] 2_6 [%d]\n", getpid());
			exit(0);
		}

		wait(0);

		printf("[EXIT] 1_3 [%d]\n", getpid());
		exit(0);
	}

	wait(0);

	pid_t pid_1_3;

	if ((pid_1_3 = fork()) == 0) {

		printf("[FORK] %d --> %d\n", getppid(), getpid());
		printf("[CHILD] -- 1_4 [%d] | [PARENT] -- [%d]\n", getpid(), getppid());
		printf("[EXIT] 1_4 [%d]\n", getpid());

		exit(0);
	}

	wait(0);

	printf("[EXIT] 0_1 [%d]\n", getpid());
	return 0;
}