/*
owner : github.com/coderSau
date :  1/16/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
static char *args[512];
static int argCount = 0;
static int n;
pid_t pid;

static char *skipwhite(char *s)
{
	while (isspace(*s))
		++s;
	return s;
}

static void cleanup()
{
	int i;
	for (i = 0; i < n; ++i)
		wait(NULL);
}

static void split(char *cmd)
{
	cmd = skipwhite(cmd);
	char *next = strchr(cmd, ' ');
	int i = 0;

	while (next != NULL)
	{
		next[0] = '\0';
		args[i] = cmd;

		++i;
		cmd = skipwhite(next + 1);
		next = strchr(cmd, ' ');
	}

	if (cmd[0] != '\0')
	{
		args[i] = cmd;

		next = strchr(cmd, '\n');
		next[0] = '\0';

		++i;
	}
	// exit with 'quit' command
	if (strcmp(args[0], "quit") == 0)
	{
		cleanup();
		exit(0);
	}

	args[i] = NULL;
}

void welcomeMessage()
{
	printf("Simple bash program github.com/coderSau \n");
}

void run(char *command)
{
	// split the command and assign it to args
	split(command);
	pid = fork();

	if (args[0] == "")
	{
		printf("komut yok");
	}
	else
	{

		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
				perror("command not found or command cannot be executed");
			kill(getpid(), SIGTERM);
		}
		else if (pid < 0)
		{
			perror("error");
		}
	}
}
int splitBy(const char *txt, char delim, char ***tokens)
{
	int *tklen, *t, count = 1;
	char **arr, *p = (char *)txt;

	while (*p != '\0')
		if (*p++ == delim)
			count += 1;
	t = tklen = calloc(count, sizeof(int));
	for (p = (char *)txt; *p != '\0'; p++)
		*p == delim ? *t++ : (*t)++;
	*tokens = arr = malloc(count * sizeof(char *));
	t = tklen;
	p = *arr++ = calloc(*(t++) + 1, sizeof(char *));
	while (*txt != '\0')
	{
		if (*txt == delim)
		{
			p = *arr++ = calloc(*(t++) + 1, sizeof(char *));
			txt++;
		}
		else
			*p++ = *txt++;
	}
	free(tklen);
	return count;
}

void splitFile(char *cmd)
{
	// skip white space character
	cmd = skipwhite(cmd);
	char **tokens;
	int count, i;
	int an = 0;
	// divide array by space and assign divided values to tokens
	count = splitBy(cmd, ' ', &tokens);
	for (i = 0; i < count; i++)
	{
		if (strlen(tokens[i]) > 0)
		{
			printf("%s ", tokens[i]);
			// add command to args
			args[an] = tokens[i];
			++an;
			
		}
	}
	printf("\n");
	if (strcmp(args[0], "quit") == 0)
	{
		cleanup();
		exit(0);
	}
}

void runFile(char *command)
{
	// split the commands 
	splitFile(command);

	pid = fork();

	if (args[0] == "")
	{
		printf("komut yok");
	}
	else
	{

		if (pid == 0)
		{
			// execute command
			if (execvp(args[0], args) == -1)
				perror("command not found or command cannot be executed");
			kill(getpid(), SIGTERM);
		}
		else if (pid < 0)
		{
			perror("hata");
		}
	}
}
char *trim(char *s)
{
	char *ptr;
	if (!s)
		return NULL; // handle NULL string
	if (!*s)
		return s; // handle empty string
	for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr)
		;
	ptr[1] = '\0';
	return s;
}
int main(int argc, char *argv[])
{

	welcomeMessage();
	char *filename = argv[1];
	
	//if there is file then execute the command inside that file
	if (filename != NULL)
	{
		FILE *fp;
		char str[512];

		n = 0;
		fp = fopen(filename, "r");
		if (fp == NULL)
		{
			printf("The file could not be opened %s \n", filename);
		}
		else
		{
			// read the command line by line
			while (fgets(str, 512, fp) != NULL)
			{
				char *currentLine = str;

				char *nextCom = strtok(currentLine, ";");
				// read the line by ';' character
				while (nextCom != NULL)
				{
					int nextLength = strlen(skipwhite(nextCom));
					// if there is a command then execute it 
					if (nextLength != 0)
					{
						runFile(trim(nextCom));
						n++;
					}
					nextCom = strtok(NULL, ";");
				}
			}

			cleanup();
			fclose(fp);
		}
	}
	// if there is no file wait for user to enter commands
	else
	{

		char line[512];
		int length;

		while (1)
		{

			printf("$ CoderSauShell> ");
			n = 0;

			if (!fgets(line, 512, stdin))
				return 0;

			if (strlen(line) > 512)
			{
				printf("You entered a very long command line more than 512 characters including '/ n' for this project \n");
			}
			else
			{
				char *next = strtok(line, ";");
				while (next != NULL)
				{
					length = strlen(next);
					if (length == 1)
					{
						printf("please enter a command \n");
					}
					else
					{
						run(next);
						n++;
					}

					next = strtok(NULL, ";");
				}

				cleanup();
			}
		}
	}

	return 0;
}