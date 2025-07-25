#include "../include/shell.h"

#include "../include/input.h"
#include "../include/parser.h"

int shell() {
	printf("Welcome to the shell!\n");
	printf("Type 'help' for a list of commands.\n");
	printf("Type 'exit' to exit the shell.\n");
	char input[MAX_INPUT_SIZE];
	char *argv[MAX_ARGC];
	int argc = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	job_t jobs[MAX_JOBS];
	int jobs_count = 0;

	while (1) {
		if (!get_input(input, sizeof(input))) {
			return EXIT_FAILURE;
		}

		int status = parse_input(input, argv, &argc);
		if (status != PARSE_OK) {
			continue;  // Prompt for input again
		}

		// Execute the command
		status = execute_command(argv, argc, jobs, &jobs_count);
		if (status == EXIT_SHELL) {
			break;  // Exit the shell
		}

		input[0] = '\0';  // Ensure input is empty for the next iteration
	}

	return EXIT_SUCCESS;
}

int execute_command(char **argv, int argc, job_t jobs[], int *jobs_count) {
	if (strcmp(argv[0], "exit") == 0 && argc == 1) {
		return EXIT_SHELL;
	}
	if (strcmp(argv[0], "help") == 0 && argc == 1) {
		printf("Available commands:\n");
		printf("  exit - Exit the shell\n");
		printf("  help - Show this help message\n");
		printf("  cd <directory> - Change directory\n");
		printf("  jobs - List stopped jobs\n");
		printf("  fg [job_id] - Resume stopped job in foreground\n");
		printf("  bg [job_id] - Resume stopped job in background\n");
		return EXIT_SUCCESS;
	}

	if (strcmp(argv[0], "jobs") == 0) {
		print_jobs(jobs, jobs_count);
		return EXIT_SUCCESS;
	}

	if (strcmp(argv[0], "cd") == 0) {
		if (argc < 2) {
			fprintf(stderr, "Usage: cd <directory>\n");
			return EXIT_FAILURE;
		}
		if (chdir(argv[1]) != 0) {
			perror("cd");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	if (strcmp(argv[0], "fg") == 0 || strcmp(argv[0], "bg") == 0) {
		int job_id;
		if (argc == 1) {
			if (*jobs_count == 0) {
				fprintf(stderr, "%s: no stopped job\n", argv[0]);
				return EXIT_FAILURE;
			}
			job_id = jobs[*jobs_count - 1].id;
		} else {
			job_id = atoi(argv[1]);
			if (job_id <= 0) {
				fprintf(stderr, "%s: invalid job id\n", argv[0]);
				return EXIT_FAILURE;
			}
		}
		job_t *job = find_job_by_id(jobs, *jobs_count, job_id);
		if (!job) {
			fprintf(stderr, "%s: no such job\n", argv[0]);
			return EXIT_FAILURE;
		}

		kill(job->pid, SIGCONT);

		if (strcmp(argv[0], "fg") == 0) {
			int status;
			waitpid(job->pid, &status, WUNTRACED);
			if (WIFSTOPPED(status)) {
				job->stopped = 1;
				printf("\nProcess stopped by signal %d\n", WSTOPSIG(status));
			} else {
				int index = job->id - 1;
				remove_job(jobs, jobs_count, index);
			}
		} else {  // bg
			printf("Process %d resumed in background.\n", job->pid);
			job->stopped = 0;
		}
		return EXIT_SUCCESS;
	}

	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork failed");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		execvp(argv[0], argv);
		perror(argv[0]);
		_exit(EXIT_FAILURE);
	} else {
		int status;
		waitpid(pid, &status, WUNTRACED);
		if (WIFSTOPPED(status)) {
			char cmdline[MAX_INPUT_SIZE] = "";
			for (int i = 0; i < argc; i++) {
				strcat(cmdline, argv[i]);
				if (i < argc - 1) strcat(cmdline, " ");
			}
			add_job(jobs, jobs_count, pid, cmdline);
			printf("\n[%d]+ Stopped %s\n", *jobs_count, cmdline);
		}
	}

	return EXIT_SUCCESS;
}

int add_job(job_t jobs[], int *jobs_count, pid_t pid, const char *cmdline) {
	if (*jobs_count >= MAX_JOBS) return -1;
	jobs[*jobs_count].pid = pid;
	strncpy(jobs[*jobs_count].cmdline, cmdline, MAX_INPUT_SIZE);
	jobs[*jobs_count].stopped = 1;
	jobs[*jobs_count].id = *jobs_count + 1;
	return (*jobs_count)++;
}

void remove_job(job_t jobs[], int *jobs_count, int index) {
	if (index < 0 || index >= *jobs_count) return;
	for (int i = index; i < *jobs_count - 1; i++) {
		jobs[i] = jobs[i + 1];
	}
	(*jobs_count)--;
	for (int i = 0; i < *jobs_count; i++) {
		jobs[i].id = i + 1;
	}
}

job_t *find_job_by_id(job_t jobs[], int jobs_count, int id) {
	for (int i = 0; i < jobs_count; i++) {
		if (jobs[i].id == id) return &jobs[i];
	}
	return NULL;
}

void print_jobs(job_t jobs[], int *jobs_count) {
	for (int i = 0; i < *jobs_count; i++) {
		int status;
		pid_t result = waitpid(jobs[i].pid, &status, WNOHANG);
		if (result == 0) {
			// Процесс ещё жив
			printf("[%d] %s %s\n", jobs[i].id,
			       jobs[i].stopped ? "Stopped" : "Running", jobs[i].cmdline);
		} else if (result > 0) {
			// Завершился — удалить
			remove_job(jobs, jobs_count, i);
			i--;  // Уменьшаем i, т.к. текущий сдвинулся
		} else {
			perror("waitpid");
		}
	}
}
