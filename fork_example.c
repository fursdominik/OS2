#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

	printf("[CHILD] [%d] | [PARENT] -- [%d]\n", getpid(), getppid());
	system("date +'HOUR: %H | MINUTE: %M SECOND: %S.%3N'");

	pid_t pid_1;

	if ((pid_1 = fork()) == 0) {

		printf("[CHILD] [%d] | [PARENT] -- [%d]\n", getpid(), getppid());
		system("date +'HOUR: %H | MINUTE: %M SECOND: %S.%3N'");

		exit(0);
	}

	pid_t pid_2;

	if ((pid_2 = fork()) == 0) {

		printf("[CHILD] [%d] | [PARENT] -- [%d]\n", getpid(), getppid());
		system("date +'HOUR: %H | MINUTE: %M SECOND: %S.%3N'");

		exit(0);
	}

	printf("\n\n");
	system("ps -x");

	for (int i = 0; i < 2; i++)
		wait(0);

	return 0;
}