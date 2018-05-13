/*
** EPITECH PROJECT, 2018
** strace
** File description:
** main file
*/

#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include "strace.h"
#include <fcntl.h>
#include <gelf.h>
#include <libelf.h>
#include <elf.h>
#include <stdio.h>
#include <unistd.h>

void    ent_func(tools_t *tools, Elf *e, GElf_Shdr s, GElf_Sym sym)
{
	dprintf(2, E_FC, elf_strptr(e, s.sh_link, sym.st_name), sym.st_value);
	if (!tools->list_function) {
		init_tool(tools, e, s, sym);
	} else {
		init_sc(tools, e, s, sym);
	}
}

void	compare_addr(tools_t *tools, Elf *elf, GElf_Shdr shdr,
		Elf_Scn *scn, unsigned long int addr)
{
	int	count;
	Elf_Data	*data;
	GElf_Sym	sym;

	data = elf_getdata(scn, NULL);
	count = shdr.sh_size / shdr.sh_entsize;
	for (int i = 0; i < count; ++i) {
		gelf_getsym(data, i, &sym);
		if (addr == sym.st_value && addr != 0 && sym.st_size != 0) {
			if (strncmp(elf_strptr(elf, shdr.sh_link,
					sym.st_name), "main", 4) == 0)
				tools->is_found_main = 1;
			if (tools->is_found_main == 1) {
				ent_func(tools, elf, shdr, sym);
				break;
			}
		}
	}
}

int	f_addrfc(unsigned long int addr, tools_t *tools)
{
	int	fd;
	Elf	*elf;
	GElf_Shdr	shdr;
	Elf_Scn	*scn = NULL;

	elf_version(EV_CURRENT);
	fd = open(tools->file_name, O_RDONLY);
	elf = elf_begin(fd, ELF_C_READ, NULL);
	while ((scn = elf_nextscn(elf, scn)) != NULL) {
		gelf_getshdr(scn, &shdr);
		if (shdr.sh_type == SHT_SYMTAB) {
			break;
		}
	}
	compare_addr(tools, elf, shdr, scn, addr);
	elf_end(elf);
	close(fd);
	return (tools->is_found_main);
}

int	main(int ac, char **av, char **env)
{
	int	is_s = 0;

	if (ac == 1)
		return (my_puterror(BAD_NB_ARGS));
	for (int i = 1; i < ac; i++) {
		return (launch_program(av + i, env, is_s));
	}
	return (0);
}
