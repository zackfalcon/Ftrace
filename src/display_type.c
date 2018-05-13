/*
** EPITECH PROJECT, 2018
** disp_string
** File description:
** disp_string
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>
#include "strace.h"

void	disp_string(unsigned long long int reg, int pid)
{
	long ptrace_result;
	char tiny_buffer[4];
	int j = 0;

	dprintf(2, "\"");
	while (j < 32) {
		ptrace_result = ptrace(PTRACE_PEEKTEXT, pid, reg + j, 0);
		memmove(tiny_buffer, &ptrace_result, 1);
		if (tiny_buffer[0] == '\0')
			break;
		if (tiny_buffer[0] == '\n')
			dprintf(2, "\\n");
		else if (tiny_buffer[0] == '\t')
			dprintf(2, "\\t");
		else
			dprintf(2, "%c", tiny_buffer[0]);
		++j;
	}
	dprintf(2, (j == 32) ? "\"..." : "\"");
}

void	disp_num(unsigned long long int reg, int pid)
{
	(void)pid;
	dprintf(2, "%lli", (long long int)reg);
}

void	disp_unsigned_num(unsigned long long int reg, int pid)
{
	(void)pid;
	dprintf(2, "%llu", reg);
}
