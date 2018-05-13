/*
** EPITECH PROJECT, 2018
** strace
** File description:
** main file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "strace.h"

void	init_tool(tools_t *tools, Elf *elf, GElf_Shdr shdr, GElf_Sym sym)
{
	tools->list_function = malloc(sizeof(save_t));
	tools->list_function->function_name =
		elf_strptr(elf, shdr.sh_link, sym.st_name);
	tools->list_function->next = NULL;
	tools->list_function->prev = NULL;
	tools->list_function->last = tools->list_function;
}

void	init_sc(tools_t *tools, Elf *elf, GElf_Shdr shdr, GElf_Sym sym)
{
	tools->list_function->last->next = malloc(sizeof(save_t));
	tools->list_function->last->next->function_name =
		elf_strptr(elf, shdr.sh_link, sym.st_name);
	tools->list_function->last->next->prev = tools->list_function->last;
	tools->list_function->last = tools->list_function->last->next;
	tools->list_function->last->next = NULL;
	tools->list_function->last->function_size = sym.st_size;
	tools->list_function->last->function_addr = sym.st_value;
}
