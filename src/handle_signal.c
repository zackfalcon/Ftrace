/*
** EPITECH PROJECT, 2018
** PSU_ftrace_2017 
** File description:
** handle_signal
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "strace.h"

static char	*signame[] = {
	"INVALID",
	"SIGHUP",
	"SIGINT",
	"SIGQUIT",
	"SIGILL",
	"SIGTRAP",
	"SIGABRT",
	"SIGBUS",
	"SIGFPE",
	"SIGKILL",
	"SIGUSR1",
	"SIGSEGV",
	"SIGUSR2",
	"SIGPIPE",
	"SIGALRM",
	"SIGTERM",
	"SIGSTKFLT",
	"SIGCHLD",
	"SIGCONT",
	"SIGSTOP",
	"SIGTSTP",
	"SIGTTIN",
	"SIGTTOU",
	"SIGURG",
	"SIGXCPU",
	"SIGXFSZ",
	"SIGVTALRM",
	"SIGPROF",
	"SIGWINCH",
	"SIGPOLL",
	"SIGPWR",
	"SIGSYS",
	NULL
};

void    receiv_sig(siginfo_t sig)
{
	char	*str;

	if (signame[sig.si_signo] != NULL) {
		str = strdup(signame[sig.si_signo]);
		if (strcmp(str, "INVALID") != 0 && strcmp(str, "SIGTRAP") != 0)
			dprintf(2, REC_SIG, str);
	}
}
