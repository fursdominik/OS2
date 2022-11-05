#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

	pid_t child1;
	pid_t child2;
	pid_t child3;
	pid_t child4;
	pid_t child5;
	pid_t child6;
	int status;

	printf("******„N„@„X„@„L„O******\n");
	printf("„D„€„‰„u„‚„~„y„z 0 %d\n", getpid());
	printf("„Q„€„t„y„„„u„|„Ž„ƒ„{„y„z %d\n", getppid());
	printf("******************\n");

	if ((child1 = fork()) < 0)
		return 1;
	else if (child1 == 0) {

		printf("„P„‚„€„ˆ„u„ƒ„ƒ %d „„€„‚„€„t„y„| „„‚„€„ˆ„u„ƒ„ƒ %d\n", getppid(), getpid());
		printf("„D„€„‰„u„‚„~„y„z 1 %d\n", getpid());
		printf("„Q„€„t„y„„„u„|„Ž„ƒ„{„y„z %d\n", getppid());
		printf("„D„€„‰„u„‚„~„y„z 1 %d „x„p„r„u„‚„Š„p„u„„ „‚„p„q„€„„„…\n", getpid());
		exit(0);

	}
	else {

		waitpid(child1, &status, WUNTRACED);

		if ((child2 = fork()) < 0)
			return 1;
		else if (child2 == 0) {

			printf("„P„‚„€„ˆ„u„ƒ„ƒ %d „„€„‚„€„t„y„| „„‚„€„ˆ„u„ƒ„ƒ %d\n", getppid(), getpid());
			printf("„D„€„‰„u„‚„~„y„z 2 %d\n", getpid());
			printf("„Q„€„t„y„„„u„|„Ž„ƒ„{„y„z %d\n", getppid());

			if ((child4 = fork()) < 0)
				return 1;
			else if (child4 == 0) {

				waitpid(child2, &status, WUNTRACED);

				printf("„P„‚„€„ˆ„u„ƒ„ƒ %d „„€„‚„€„t„y„| „„‚„€„ˆ„u„ƒ„ƒ %d\n", getppid(), getpid());
				printf("„D„€„‰„u„‚„~„y„z 4 %d\n", getpid());
				printf("„Q„€„t„y„„„u„|„Ž„ƒ„{„y„z %d\n", getppid());

				if ((child6 = fork()) < 0)
					return 1;
				else if (child6 == 0) {

					printf("„P„‚„€„ˆ„u„ƒ„ƒ %d „„€„‚„€„t„y„| „„‚„€„ˆ„u„ƒ„ƒ %d\n", getppid(), getpid());
					printf("„D„€„‰„u„‚„~„y„z 6 %d\n", getpid());
					printf("„Q„€„t„y„„„u„|„Ž„ƒ„{„y„z %d\n", getppid());
					printf("„D„€„‰„u„‚„~„y„z 6 %d „x„p„r„u„‚„Š„p„u„„ „‚„p„q„€„„„…\n", getpid());
					exit(0);
				}
				else {
				}

				printf("„D„€„‰„u„‚„~„y„z 4 %d „x„p„r„u„‚„Š„p„u„„ „‚„p„q„€„„„…\n", getpid());
				exit(0);

			}
			else {

				waitpid(child4, &status, WUNTRACED);

				if ((child5 = fork()) < 0)
					return 1;
				else if (child5 == 0) {
					printf("„P„‚„€„ˆ„u„ƒ„ƒ %d „„€„‚„€„t„y„| „„‚„€„ˆ„u„ƒ„ƒ %d\n", getppid(), getpid());
					printf("„D„€„‰„u„‚„~„y„z 5 %d\n", getpid());
					printf("„Q„€„t„y„„„u„|„Ž„ƒ„{„y„z %d\n", getppid());
					printf("„P„‚„€„ˆ„u„ƒ„ƒ %d „y„ƒ„„€„|„~„‘„u„„ „{„€„}„p„~„t„… pwd\n", getpid());
					execvp("pwd", argv);
					printf("„D„€„‰„u„‚„~„y„z 5 %d „x„p„r„u„‚„Š„p„u„„ „‚„p„q„€„„„…\n", getpid());
					exit(0);
				}
				else {
				}
			}

			printf("„D„€„‰„u„‚„~„y„z 2 %d „x„p„r„u„‚„Š„p„u„„ „‚„p„q„€„„„…\n", getpid());
			exit(0);

		}
		else {

			waitpid(child2, &status, WUNTRACED);

			if ((child3 = fork()) < 0)
				return 1;
			else if (child3 == 0) {
				printf("„P„‚„€„ˆ„u„ƒ„ƒ %d „„€„‚„€„t„y„| „„‚„€„ˆ„u„ƒ„ƒ %d\n", getppid(), getpid());
				printf("„D„€„‰„u„‚„~„y„z 3 %d\n", getpid());
				printf("„Q„€„t„y„„„u„|„Ž„ƒ„{„y„z %d\n", getppid());
				printf("„D„€„‰„u„‚„~„y„z 3 %d „x„p„r„u„‚„Š„p„u„„ „‚„p„q„€„„„…\n", getpid());
				exit(0);
			}
			else {
			}

		}

	}

}
