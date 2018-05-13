/*
** EPITECH PROJECT, 2018
** strace
** File description:
** display strace
*/

#include <stdio.h>
#include <sys/ptrace.h>
#include "syscall.h"

struct_t	tab_struct[TAB_SIZE] =
{
	{&disp_string, STRING},
	{&disp_num, NUM},
	{&disp_unsigned_num, UNSIGNED}
};

static void	display_type(int type, int pid,
			unsigned long long int val)
{
	int	done = 0;

	for (int i = 0; i < TAB_SIZE; i++) {
		if (tab_struct[i].type == type) {
			tab_struct[i].function(val, pid);
			done = 1;
		}
	}
	if (done == 0) {
		if (val == 0)
			dprintf(2, "NULL");
		else
			dprintf(2, "0x%llx", val);
	}
}

void	print_return_value(struct user_regs_struct *regs,
			int pid, int is_s)
{
	struct user_regs_struct	regs2;
	int			type = table[regs->rax].return_type;

	ptrace(PTRACE_GETREGS, pid, NULL, &regs2);
	if (table[regs->rax].return_type == VOID)
		dprintf(2, "?\n");
	else {
		if (is_s == 0)
			dprintf(2, "0x%llx\n", regs2.rax);
		else {
			display_type(type, pid, regs2.rax);
			dprintf(2, "\n");
		}
	}
}

void	print_arg(int s, unsigned long long int val, int type, int pid)
{
	if (s == 0)
		dprintf(2, "0x%llx", val);
	else {
		display_type(type, pid, val);
	}
}
