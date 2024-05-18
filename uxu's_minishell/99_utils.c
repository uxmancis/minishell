/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:04:48 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/18 14:20:41 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isspace(int c)
{
	//printf(">>> c = %d\n", c);
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
		return (1);
    return (0);
}

/* DESCRIPTION:
Outputs the char c to the file descriptor fd.
The function returns the number of characters printed and -1 if fails to print.
---------------------------------------------------------------------------- */
int	ft_putchar_fd(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/* DESCRIPTION:
Outputs the string s to the file descriptor fd.
The function returns the number of characters printed and -1 if fails to print.
---------------------------------------------------------------------------- */
int	ft_putstr_fd(char *str, int fd)
{
	int	count;

	count = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (*str)
	{
		count += ft_putchar_fd(*str, fd);
		str++;
	}
	return (count);
}

void	ft_print_welcome(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(MAGENTA, 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd("           :::      ::::::::                         \n", 1);
	ft_putstr_fd("         :+:      :+:    :+:                         \n", 1);
	ft_putstr_fd("       +:+ +:+         +:+                           \n", 1);
	ft_putstr_fd("     +#+  +:+       +#+        \t\tminishell 42 by:  \n", 1);
	ft_putstr_fd("   +#+#+#+#+#+   +#+           \t\tdbonilla          \n", 1);
	ft_putstr_fd("        #+#    #+#             \t\tuxmancis          \n", 1);
	ft_putstr_fd("       ###   ########.fr                             \n", 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd(DEF_COLOR, 1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] == s2[i])
		{	
			i++;
		}
		else
			return ((unsigned char ) s1[i] - (unsigned char) s2[i]);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i++] == '-')
				sign = -1;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{	
			num = (num * 10) + (str[i] - 48);
			i++;
		}
		return (num * sign);
	}
	return (0);
}

//void ft_malloc(void *)