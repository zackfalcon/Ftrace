#include <unistd.h>
#include <string.h>

void my_putchar(char c)
{
	write(1, &c, 1);
}

void my_putstr(char *str)
{
	int i = 0;

	while (str[i]) {
		my_putchar(str[i]);
		++i;
	}
}

int main()
{
	my_putstr("Hello World");
	return (0);
}
