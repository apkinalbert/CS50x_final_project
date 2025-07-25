#ifndef SHELL_H
#define SHELL_H

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define EXIT_SHELL 2
#define _POSIX_C_SOURCE 200809L
#define MAX_JOBS 64
#define MAX_INPUT_SIZE 1024

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
	pid_t pid;
	char cmdline[MAX_INPUT_SIZE];
	int stopped;
	int id;
} job_t;

int shell();
int execute_command(char **argv, int argc, job_t jobs[], int *jobs_count);
int add_job(job_t jobs[], int *jobs_count, pid_t pid, const char *cmdline);
void remove_job(job_t jobs[], int *jobs_count, int index);
job_t *find_job_by_id(job_t jobs[], int jobs_count, int id);
void print_jobs(job_t jobs[], int *jobs_count);

#endif