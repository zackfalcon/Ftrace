/*
** EPITECH PROJECT, 2018
** strace
** File description:
** tools file
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>
#include "syscall.h"
#include <limits.h>

int	is_number(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

int	my_puterror(char *str)
{
	write(2, str, strlen(str));
	return (84);
}

void	fill_type(int *type, struct user_regs_struct *r)
{
	type[0] = table[r->rax].a1;
	type[1] = table[r->rax].a2;
	type[2] = table[r->rax].a3;
	type[3] = table[r->rax].a4;
	type[4] = table[r->rax].a5;
	type[5] = table[r->rax].a6;
}

long	do_peektext(int pid, struct user_regs_struct *regs)
{
	return (ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL));
}
