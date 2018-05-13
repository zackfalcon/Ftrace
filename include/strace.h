/*
** EPITECH PROJECT, 2018
** strace
** File description:
** strace header
*/

#ifndef STRACE_H_
# define STRACE_H_

# include <sys/ioctl.h>
# include <signal.h>
# include <libelf.h>
# include <elf.h>
# include <gelf.h>
# include <sys/user.h>

# define L_FC		"Leaving function %s\n"
# define E_FC		"Entering function %s at %#lx\n"
# define REC_SIG	"Received signal %s\n"
# define BAD_PID	"Bad PID\n"
# define BAD_NB_ARGS	"Invalid number of arguments\n"
# define BAD_FORK	"Problem during fork\n"
# define CANT_TRACE	"Program can't be traced\n"
# define CANT_EXEC	"Problem during execution of the program\n"
# define TAB_SIZE	3

typedef struct	syscall_s
{
	int	num;
	char	*name;
	int	nb_args;
	int	return_type;
	int	a1;
	int	a2;
	int	a3;
	int	a4;
	int	a5;
	int	a6;
}		syscall_t;

typedef struct	struct_s
{
	void	(*function)(unsigned long long int, int);
	int	type;
}		struct_t;

typedef struct	save_s
{
	size_t function_size;
	char		*function_name;
	unsigned long long int function_addr;
	struct	save_s	*prev;
	struct	save_s	*next;
	struct	save_s	*last;
}		save_t;

typedef struct	tools_s
{
	long	offset;
	char	*file_name;
	int	is_found_main;
	int	under_function;
	save_t	*list_function;
}		tools_t;

void	receiv_sig(siginfo_t sig);
int	is_number(char *);
int	my_puterror(char *);
int	launch_program(char **, char **, int);
int	start_strace(int, int, char*);
void	disp_string(unsigned long long int reg, int pid);
int	f_addrfc(unsigned long int, tools_t*);
void	print_return_value(struct user_regs_struct *, int, int);
void	print_arg(int, unsigned long long, int, int);
void	disp_string(unsigned long long int, int);
void	disp_num(unsigned long long int, int);
void	disp_unsigned_num(unsigned long long int, int);
void	init_tool(tools_t *, Elf *, GElf_Shdr, GElf_Sym);
void	init_sc(tools_t *, Elf *, GElf_Shdr, GElf_Sym);
void	fill_type(int *type, struct user_regs_struct *r);
long	do_peektext(int pid, struct user_regs_struct *regs);

#endif /* !STRACE_H_ */
