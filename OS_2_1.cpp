#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int copyf(char* filein, char* fileout);

int main(int argc, char* argv[])
{
	int Num;
	char* Dir1, * Dir2;
	if (argc != 3) {

		printf("Too few parameters\n");

		return 1;
	}

	Dir1 = argv[1];
	Dir2 = argv[2];

	printf("How many process?\n");
	scanf("%d", &Num);
	char File1[256], File2[256];

	DIR* d = opendir(Dir1);

	if (!d) {

		printf("Error opendir");

		return 1;

	}

	struct dirent* dt;

	int n = 0;

	while ((dt = readdir(d))) {

		printf("%4d. %s\n", n++, dt->d_name);

		if (n < 3) continue;

		sprintf(File1, "%s/%s", Dir1, dt->d_name);

		sprintf(File2, "%s/%s", Dir2, dt->d_name);

		pid_t pid;

		if (Num > 0) pid = fork();

		Num--;

		if (pid == 0) {

			if (!copyf(File1, File2))

				printf("file '%s' copied by #%d\n",

					dt->d_name, getpid());

			return 0;

		}
		else {

			if (!copyf(File1, File2))

				printf("file '%s' copied by #%d\n",

					dt->d_name, getpid());

		}

	}

	closedir(d);

	return 0;

}

int copyf(char* filein, char* fileout)

{

	FILE* f_in, * f_out;

	f_in = fopen(filein, "rb");

	if (!f_in) return 1;

	if (fopen(fileout, "rb")) return 1;

	f_out = fopen(fileout, "wb");

	if (!f_out) return 1;

	int bytes = 0;

	char c = fgetc(f_in);

	while (!feof(f_in)) {

		fputc(c, f_out);

		bytes++;

		c = fgetc(f_in);

	}

	fclose(f_in);

	fclose(f_out);

	struct stat stat_f;

	stat(filein, &stat_f);

	chmod(fileout, stat_f.st_mode);

	printf("%d bytes ", bytes);

	return 0;

}