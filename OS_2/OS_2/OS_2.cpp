#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	printf("Дочерний 0_0 %d\n", getpid());
	printf("Родительский %d\n", getppid());

	pid_t pid_1_2;

	if ((pid_1_2 = fork()) == 0) {

		printf("Процесс %d породил процесс %d\n", getppid(), getpid());
		printf("Дочерний 1_2 %d\n", getpid());
		printf("Родительский %d\n", getppid());
		printf("Дочерний 1_2 %d завершает работу\n", getpid());

		exit(0);
	}

	wait(0);

	pid_t pid_1_3;

	if ((pid_1_3 = fork()) == 0) {

		printf("Процесс %d породил процесс %d\n", getppid(), getpid());
		printf("Дочерний 1_3 %d\n", getpid());
		printf("Родительский %d\n", getppid());

		pid_t pid_3_5;

		if ((pid_3_5 = fork()) == 0) {

			printf("Процесс %d породил процесс %d\n", getppid(), getpid());
			printf("Дочерний 3_5 %d\n", getpid());
			printf("Родительский %d\n", getppid());

			pid_t pid_5_7;

			if ((pid_5_7 = fork()) == 0) {

				printf("Процесс %d породил процесс %d\n", getppid(), getpid());
				printf("Дочерний 5_7 %d\n", getpid());
				printf("Родительский %d\n", getppid());
				printf("Дочерний 5_7 %d завершает работу\n", getpid());

				exit(0);
			}

			wait(0);

			printf("Дочерний 3_5 %d завершает работу\n", getpid());
			exit(0);
		}

		wait(0);

		pid_t pid_3_6;

		if ((pid_3_6 = fork()) == 0) {

			printf("Процесс %d породил процесс %d\n", getppid(), getpid());
			printf("Дочерний 3_6 %d\n", getpid());
			printf("Родительский %d\n", getppid());

			printf("Дочерний 3_6 %d выполняет команду pwd\n", getpid());
			execvp("pwd", argv);

			printf("Дочерний 3_6 %d завершает работу\n", getpid());
			exit(0);
		}

		wait(0);

		printf("Дочерний 1_3 %d завершает работу\n", getpid());
		exit(0);
	}

	wait(0);

	pid_t pid_1_4;

	if ((pid_1_4 = fork()) == 0) {

		printf("Процесс %d породил процесс %d\n", getppid(), getpid());
		printf("Дочерний 1_4 %d\n", getpid());
		printf("Родительский %d\n", getppid());
		printf("Дочерний 1_4 %d завершает работу\n", getpid());

		exit(0);
	}

	wait(0);

	printf("Дочерний 0_0 %d завершает работу\n", getpid());
	return 0;
}
/*
using namespace std;

int main(int argc, char** argv) {

	cout << "Дочерний 0.0  " << getpid() << '\n';
	cout << "Родительский" << getppid() << '\n';

	pid_t pid_1_2;

	if ((pid_1_2 = fork()) == 0) {

		cout << "Процесс " << getppid() << " породил процесс" << getpid() << '\n';
		cout << "Дочерний 1.2  " << getpid() << '\n';
		cout << "Родительский" << getppid() << '\n';
		cout << "Дочерний 1.2 " << getpid() << " завершает работу" << '\n';

		exit(0);
	}
	wait(0);

	pid_t pid_1_3;

	if ((pid_1_3 = fork()) == 0) {

		cout << "Процесс " << getppid() << " породил процесс" << getpid() << '\n';
		cout << "Дочерний 1.3  " << getpid() << '\n';
		cout << "Родительский" << getppid() << '\n';

		pid_t pid_3_5;
		if ((pid_3_5 = fork()) == 0) {

			cout << "Процесс " << getppid() << " породил процесс" << getpid() << '\n';
			cout << "Дочерний 3.5  " << getpid() << '\n';
			cout << "Родительский" << getppid() << '\n';

			pid_t pid_5_7;
			if ((pid_5_7 = fork()) == 0) {

				cout << "Процесс " << getppid() << " породил процесс" << getpid() << '\n';
				cout << "Дочерний 5.7  " << getpid() << '\n';
				cout << "Родительский" << getppid() << '\n';
				cout << "Дочерний 5.7 " << getpid() << " завершает работу" << '\n';

				exit(0);
			}
			wait(0);

			cout << "Дочерний 3.5 " << getpid() << " завершает работу" << '\n';

			exit(0);
		}
		wait(0);

		pid_t pid_3_6;
		if ((pid_3_6 == fork()) == 0) {

			cout << "Процесс " << getppid() << " породил процесс" << getpid() << '\n';
			cout << "Дочерний 3.6  " << getpid() << '\n';
			cout << "Родительский" << getppid() << '\n';

			printf("Дочерний 2_6 %d executes order 66\n", getpid()); cout << "Дочерний 3_6" << getpid() << "выполняет заказ 66" << '\n';
			execvp("pwd", argv);

			cout << "Дочерний 3.6 " << getpid() << " завершает работу" << '\n';

			exit(0);
		}
		wait(0);

		cout << "Дочерний 1.3 " << getpid() << " завершает работу" << '\n';
		exit(0);
	}
	wait(0);

	pid_t pid_1_4;
	if ((pid_1_4 == fork()) == 0) {

		cout << "Процесс " << getppid() << " породил процесс" << getpid() << '\n';
		cout << "Дочерний 1.4  " << getpid() << '\n';
		cout << "Родительский" << getppid() << '\n';
		cout << "Дочерний 1.4 " << getpid() << " завершает работу" << '\n';

		exit(0);
	}

	wait(0);

	cout << "Дочерний 0.0 " << getpid() << " завершает работу" << '\n';

	return 0;
}
*/