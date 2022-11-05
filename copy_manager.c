#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

struct stat get_stat_buffer(const struct dirent* element, const char* current_path);
int get_file_size(const struct dirent* element, const char* current_path);
static int isdir(const struct dirent* element);
static int isfile(const struct dirent* element);
size_t return_file_size(FILE* f);
char* path_concat(const char* string_1, const char* string_2);
int check_filename_presence(const char* path, const char* filename);
int copy_object(const char* destination_path, const char* source_path, const char* filename);
void copy_dir_contents_recursive(const char* destination_path, const char* source_path, int* available_thread_count, int directory_depth);
void copy_dir_contents(const char* destination_path, const char* source_path, int max_thread_count);


// DEPRECATED {

void remove_directory(const char* path) {

	DIR* directory_stream;
	size_t path_len = strlen(path);

	if ((directory_stream = opendir(path)) != 0) {

		struct dirent* p;


		while (p = readdir(directory_stream)) {

			if (strcmp(p->d_name, ".") == 0 || strcmp(p->d_name, "..") == 0)
				continue;

			char* buf;
			struct stat statbuf;

			asprintf(&buf, "%s/%s", path, p->d_name);

			if (stat(buf, &statbuf) == 0)
				if (S_ISDIR(statbuf.st_mode)) {
					printf("%s - %d \n", p->d_name, p->d_type);
					remove_directory(buf);
				}
				else {
					printf("%s - %d - %d \n", p->d_name, p->d_type, get_file_size(p, path));
					unlink(buf);
				}


		}
		closedir(directory_stream);
	}

	rmdir(path);

}

int remove_object(const char* path) {

	struct stat statbuf;

	stat(path, &statbuf);

	if (S_ISDIR(statbuf.st_mode))
		rmdir(path);
	else if (S_ISREG(statbuf.st_mode))
		unlink(path);

}

int copy_directory(const char* destination_path, const char* source_path) {

	DIR* directory_stream;
	size_t path_len = strlen(source_path);

	if ((directory_stream = opendir(source_path)) == 0) {

		printf("Error opening %s\n", source_path);
		return -1;
	}

	struct dirent* p;

	while (p = readdir(directory_stream)) {

		if (strcmp(p->d_name, ".") == 0 || strcmp(p->d_name, "..") == 0)
			continue;

		struct stat statbuf;
		char* full_source_path;
		char* full_destination_path;

		asprintf(&full_source_path, "%s/%s", source_path, p->d_name);
		asprintf(&full_destination_path, "%s/%s", destination_path, p->d_name);

		if (stat(full_source_path, &statbuf) == 0)
			if (S_ISDIR(statbuf.st_mode)) {

				if (check_filename_presence(destination_path, p->d_name) == 0) {

					printf("%s - %d \n", p->d_name, p->d_type);
					copy_object(destination_path, source_path, p->d_name);
				}

				copy_directory(full_destination_path, full_source_path);
			}
			else
				if (check_filename_presence(destination_path, p->d_name) == 0) {

					printf("%s - %d - %d \n", p->d_name, p->d_type, get_file_size(p, source_path));
					copy_object(destination_path, source_path, p->d_name);
				}


	}

	closedir(directory_stream);

	return 1;

}

void print_dir_contents_recursive(const char* current_path, int directory_depth) {

	struct dirent** file_buffer;
	struct dirent** dir_buffer;
	int file_count, dir_count;

	printf("%*s", directory_depth, " ");
	printf(" -- [DIR] [%s] \n", current_path);

	file_count = scandir(current_path, &file_buffer, isfile, alphasort);
	dir_count = scandir(current_path, &dir_buffer, isdir, alphasort);


	if (file_count > 0)
		for (int i = 0; i < file_count; i++) {

			char* temp_path;

			printf("%*s", directory_depth + 3, " ");
			printf(" -- [FILE] [%s] -- %d bytes \n", file_buffer[i]->d_name, get_file_size(file_buffer[i], current_path));

			asprintf(&temp_path, "%s/%s", current_path, file_buffer[i]->d_name);


		}


	if (dir_count > 0)
		for (int i = 0; i < dir_count; i++) {

			if (strcmp(dir_buffer[i]->d_name, ".") == 0 || strcmp(dir_buffer[i]->d_name, "..") == 0)
				continue;

			char* temp_path;

			asprintf(&temp_path, "%s/%s", current_path, dir_buffer[i]->d_name);

			print_dir_contents_recursive(temp_path, directory_depth + 3);

		}

	free(file_buffer);
	free(dir_buffer);

}

void print_dir_contents(const char* current_path) {

	print_dir_contents_recursive(current_path, 1);

}

// }



struct stat get_stat_buffer(const struct dirent* element, const char* current_path) {

	struct stat stat_buffer;
	char* path;

	asprintf(&path, "%s/%s", current_path, element->d_name);

	stat(path, &stat_buffer);

	free(path);

	return stat_buffer;

}

int get_file_size(const struct dirent* element, const char* current_path) {

	return get_stat_buffer(element, current_path).st_size;

}

static int isdir(const struct dirent* element) {

	return (element->d_type == DT_DIR);

}

static int isfile(const struct dirent* element) {

	return (element->d_type == DT_REG);

}

size_t return_file_size(FILE* f) {

	size_t pos = ftell(f);
	size_t size;

	fseek(f, 0L, SEEK_END);
	size = ftell(f);
	fseek(f, pos, SEEK_SET);

	return size;
}

char* path_concat(const char* string_1, const char* string_2) {

	char* output;

	asprintf(&output, "%s/%s", string_1, string_2);

	return output;
}

int check_filename_presence(const char* path, const char* filename) {

	DIR* dir_stream;
	struct dirent* entry;

	if ((dir_stream = opendir(path)) == NULL) {
		printf("Error opening directory stream on %s\n", path);
		return -1;
	}

	while (entry = readdir(dir_stream))
		if (strcmp(entry->d_name, filename) == 0) {

			closedir(dir_stream);
			return 1;
		}

	closedir(dir_stream);
	return 0;

}

int copy_object(const char* destination_path, const char* source_path, const char* filename) {

	char* full_source_path, * full_destination_path;
	struct stat statbuf;

	asprintf(&full_source_path, "%s/%s", source_path, filename);
	asprintf(&full_destination_path, "%s/%s", destination_path, filename);

	stat(full_source_path, &statbuf);

	if (S_ISDIR(statbuf.st_mode))
		mkdir(full_destination_path, statbuf.st_mode);
	else if (S_ISREG(statbuf.st_mode)) {

		FILE* source_object;
		FILE* destination_object;
		int temp_char;
		char *buf;

		if ((source_object = fopen(full_source_path, "r")) == NULL) {

			printf("Error opening %s\n", full_source_path);
			return -1;
		}
		if ((destination_object = fopen(full_destination_path, "w")) == NULL) {

			printf("Error opening %s\n", full_destination_path);
			return -1;
		}

		//while ((temp_char = getc(source_object)) != EOF)
		//	fputc(temp_char, destination_object);
		//while ((temp_char = fread(buf, 1, 1024, source_object)) == 1024)
		//	fwrite(buf, 1, 1024, destination_object);
		//fwrite(buf, 1, temp_char, destination_object);

		buf = malloc(return_file_size(source_object) + 1);
		temp_char = fread(buf, 1, return_file_size(source_object) + 1, source_object);
		fwrite(buf, 1, temp_char, destination_object);
		free(buf);

		chmod(full_destination_path, statbuf.st_mode);

		fclose(source_object);
		fclose(destination_object);

		return 1;

	}

}

void copy_dir_contents_recursive(const char* destination_path, const char* source_path, int* available_thread_count, int directory_depth) {

	struct dirent** file_buffer;
	struct dirent** dir_buffer;
	int file_count, dir_count;


	printf("%*s", directory_depth, " ");
	printf(" -- [DIR] [%s] \n", source_path);

	file_count = scandir(source_path, &file_buffer, isfile, alphasort);
	dir_count = scandir(source_path, &dir_buffer, isdir, alphasort);


	if (file_count > 0)
		for (int i = 0; i < file_count; i++)
			if (check_filename_presence(destination_path, file_buffer[i]->d_name) == 0) {

				if ((*available_thread_count) == 0) {

					wait(0);
					(*available_thread_count)++;
				}

				(*available_thread_count)--;

				pid_t pid;

				if ((pid = fork()) < 0) {

					printf("Error creating new process\n");
					return;
				}
				else if (pid == 0) {

				printf("%*s", directory_depth + 3, " ");
				printf(" -- [FILE] [PID %d] [TA: %d] | [%d MB] [%s] \n", getpid(), (*available_thread_count), get_file_size(file_buffer[i], source_path) / (1024 * 1024), file_buffer[i]->d_name);

				copy_object(destination_path, source_path, file_buffer[i]->d_name);


				exit(0);

				}


			}


	if (dir_count > 0)
		for (int i = 0; i < dir_count; i++)
			if (strcmp(dir_buffer[i]->d_name, ".") == 0 || strcmp(dir_buffer[i]->d_name, "..") == 0)
				continue;
			else {

				if (check_filename_presence(destination_path, dir_buffer[i]->d_name) == 0) {


					copy_object(destination_path, source_path, dir_buffer[i]->d_name);
				}

				copy_dir_contents_recursive(path_concat(destination_path, dir_buffer[i]->d_name), path_concat(source_path, dir_buffer[i]->d_name), available_thread_count, directory_depth + 3);
			}

	free(file_buffer);
	free(dir_buffer);

}

void copy_dir_contents(const char* destination_path, const char* source_path, int max_thread_count) {

	int* available_thread_count = malloc(sizeof(int));
	*available_thread_count = max_thread_count;

	copy_dir_contents_recursive(destination_path, source_path, available_thread_count, 1);

}


int main(int argc, char* argv[]) {

	if (argc < 4) {

		printf("*****ERROR***** \nIncorrect number of parameters in function main(): 3 expected but only %d given", argc - 1);
		return -1;
	}

	copy_dir_contents(argv[1], argv[2], atoi(argv[3]));

	return 0;
}