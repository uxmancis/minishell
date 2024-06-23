/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:59:22 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 20:52:28 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	ft_putstr_fd("       ###   ########.ur                             \n", 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd(DEF_COLOR, 1);
}

void	ft_put_name_system_2(char *sysname, char *user_name, char *pwd)
{
	ft_strcat(sysname, "@");
	ft_strcat(sysname, CYAN);
	ft_strcat(sysname, user_name);
	ft_strcat(sysname, WHITE);
	ft_strcat(sysname, " ➜ ");
	ft_strcat(sysname, GREEN);
	ft_strcat(sysname, pwd);
	ft_strcat(sysname, WHITE);
	ft_strcat(sysname, " $ " GREEN);
	ft_strcat(sysname, RESET_COLOR);
}

char	*ft_put_name_system(t_prompt *data)
{
	char	*sysname;
	char	*user_name;
	char	*pwd;

	if (!(ft_getenv_local(data->vars, "USER"))
		|| !(ft_getenv_local(data->vars, "PWD")))
		return (printf("Error: No user or pwd\n"), NULL);
	user_name = ft_getenv_local(data->vars, "USER")->val;
	pwd = ft_getenv_local(data->vars, "PWD")->val;
	sysname = (char *)malloc(ft_strlen(user_name)
			+ ft_strlen(pwd) + 200);
	if (!sysname)
		return (NULL);
	ft_strcpyy_2(sysname, RED);
	ft_put_name_system_2(sysname, user_name, pwd);
	data->prompt = sysname;
	return (sysname);
}

int	ft_ischarset(char c, const char *set)
{
	int	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
