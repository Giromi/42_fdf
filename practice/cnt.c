
#include <stdio.h>
#define SUCCESS 0
#define ERROR -1

int is_set(char *set, char c)
{
	if (!set)
		return (ERROR);
	while (*set)
	{
		if (*set == c)
			return (SUCCESS);
		set++;
	}
	return (ERROR);

}

int ft_word_cnt(const char *line, char *set)
{
	int	i;
	int	width;

	if (!set)
		return (ERROR);
	i = 0;
	while (*line)
	{
		if (!is_set(set, *line) && line++)
			continue ;
		width++;
		while (*line && is_set(set, *line) == ERROR)
			line++;
	}
	return (width);
}


int main(int ac, char *av[])
{
	if (ac < 2)
		return (-1);
	printf("cnt : %d\n", ft_word_cnt(av[1], " \n\t"));
	return (0);
}
