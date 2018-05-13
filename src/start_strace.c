/*
** EPITECH PROJECT, 2018
** strace
** File description:
** start_strace file
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

void	syscall_function(int pid, struct user_regs_struct *regs,
			unsigned long long int *r_val, int is_s)
{
	int	type[6];

	fill_type(type, regs);
	if (strcmp(table[regs->rax].name, "exit_group") == 0)
		dprintf(2, "Leaving function main\n");
	dprintf(2, "Syscall %s(", table[regs->rax].name);
	for (int i = 0; i < table[regs->rax].nb_args; i++) {
		print_arg(is_s, r_val[i], type[i], pid);
		if ((i + 1) < table[regs->rax].nb_args)
			dprintf(2, ", ");
	}
	dprintf(2, ") = ");
	print_return_value(regs, pid, 0);
}

static void	leaving_function(struct user_regs_struct *regs,
	tools_t	*t)
{
	if (regs->rip - (t->list_function->last->function_size - 1)
		== t->list_function->last->function_addr) {
		dprintf(2, L_FC, t->list_function->last->function_name);
		t->list_function->last = t->list_function->last->prev;
		if (t->list_function->last)
			free(t->list_function->last->next);
		--t->under_function;
	}
}

static void	catch_syscall(int pid, struct user_regs_struct *regs,
			int is_s, char *file_name)
{
	long			val = do_peektext(pid, regs);
	unsigned char		f = (unsigned)0xFF & val;
	unsigned char		s = ((unsigned)0xFF00 & val) >> 8;
	unsigned long long int	r[6] = {regs->rdi, regs->rsi, regs->rdx,
					regs->r10, regs->r8, regs->r9};
	static tools_t		t;

	t.file_name = file_name;
	if (t.is_found_main == 0)
		t.is_found_main = f_addrfc(regs->rax, &t);
	if (f == 0xe8) {
		if (t.is_found_main == 1) {
			t.offset = ptrace(PTRACE_PEEKTEXT, pid, regs->rip + 1, 0);
			f_addrfc(regs->rip + (long)(int)(t.offset &
				(unsigned long)UINT_MAX) + 5, &t);
		}
	} else if ((f == 0xCD && s == 0x80) || (f == 0x0F && s == 0x05)) {
		syscall_function(pid, regs, r, is_s);
	} else if (f == 0xC3 && t.list_function)
		leaving_function(regs, &t);
}

int	start_strace(int pid, int is_s, char *file_name)
{
	int			status;
	int			loop = 0;
	struct rusage		rusage;
	struct user_regs_struct	regs;
	siginfo_t		sigget;

	while (loop == 0) {
		ptrace(PTRACE_GETREGS, pid, NULL, &regs);
		ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
		wait4(pid, &status, 0, &rusage);
		ptrace(PTRACE_GETSIGINFO, pid, NULL, &sigget);
		receiv_sig(sigget);
		if (WEXITSTATUS(status) == 84)
			return (84);
		if (WIFSTOPPED(status))
			catch_syscall(pid, &regs, is_s, file_name);
		if (WIFEXITED(status))
			loop = 1;
	}
	dprintf(2, "+++ exited with %d +++\n", WEXITSTATUS(status));
	return (0);
}

int	launch_program(char **av, char **env, int is_s)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (my_puterror(BAD_FORK));
	else if (pid == 0) {
		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
			exit(my_puterror(CANT_TRACE));
		else if (execve(av[0], av, env) == -1) {
			exit(my_puterror(CANT_EXEC));
		}
		exit(0);
	}
	else
		return (start_strace(pid, is_s, av[0]));
}
