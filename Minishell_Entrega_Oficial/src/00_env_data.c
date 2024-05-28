/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_env_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:45:53 by codespace         #+#    #+#             */
/*   Updated: 2024/05/26 12:47:55 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"


static void	ft_export_all(t_vars *list)
{
	t_vars	*tmp;

	tmp = list;
	while (tmp)
	{
		// printf("tmp->name = %s\n", tmp->name);
		if (ft_strcmp(tmp->name, "?"))
			tmp->is_exp = 1;
		tmp = tmp->next;
	}
}

// char *expand_env_variable(char *var) {
//     char *expanded_var ;
//     if (var[0] == '$') {
//         char *env_var_name = var + 1;
//         char *env_var_value = ft_getenv_local(env_var_name);
//         if (env_var_value != NULL) {
//             expanded_var = strdup(env_var_value);
//         }
//     }
//     return (expanded_var);
// }
t_vars *ft_getenv_local(t_vars *line, char *name)
{
	//printf("     00_env_data.c - "YELLOW"ft_getenv_local"RESET_COLOR" | str to find = %s\n", name);
	if (line == NULL) 
	{
		perror("Error: No  or pwd\n");
		return (NULL);   
	}
    while (line)
    {
        // Asegúrate de que 'line->name' está correctamente inicializado
        if (line->name && !strcmp(line->name, name))
        {
            return (line);
        }
        line = line->next;
    }
    return (NULL);
}

int ft_write_val(t_vars *new, char *value) // This function writes the value of the variable in the environment
{
	if (!value) // This if statement checks if the value is NULL
		free(new->val); 
		// Free the memory allocated for the value of the variable
	if (value) // If the value is not NULL
		new->val = ft_strdup(value);
		// printf("new->val = %s\n", new->val);
	return (0);
}

int ft_setenv_local(t_vars *list, char *name, char *value, int overwrite)
{
	t_vars	*tmp;
	t_vars	*new;

	tmp = list;
	while (tmp)
	{
		// if 
		if (!ft_strcmp(tmp->name, name))
		{
			if (overwrite) // If the variable already exists
			{
				ft_write_val(tmp, value); // This function writes the value of the variable in the environment local.
				return (0);
			}
			return (-1);
		}
		if (!tmp->next) // If the next variable is NULL
		{
			// This if statement checks if the variable is the last one in the list
			if (!(new = ft_varsnew(ft_strdup(name), ft_strdup(value))))
				return (-1);
			tmp->next = new; // Assigns the new variable to the next variable
			return (0);
		}
		tmp = tmp->next; // Assigns the next variable to the current variable
		// printf("tmp->name = %s\n", tmp->name);
		// printf("tmp->val = %s\n", tmp->val);
	}
	return (0);
}

t_vars *ft_varsnew(char *name, char *value) // This function creates a new variable in the environment local and volcate memory for it	
{
	t_vars	*new;

	// Allocating memory for the new variable
	if (!(new = (t_vars *)malloc(sizeof(t_vars)))) // Verifies if the allocation was successful and returns NULL if it was not
			return (NULL); 
	new->name = name;
	new->val = value;
	new->is_exp = 0;
	new->next = NULL;
	return (new);
	
}


// Function to import the environment variables
static void ft_import_envp(t_prompt *data, char **envp)
{
	int i; 
	int l;
	char *name;
	char *value;
	int flag;
	// (void)envp;
	// Correctly initialized of the information of the environment variable
	
	if(!(data->vars = ft_varsnew(ft_strdup("?"), ft_strdup("0")))) // Allocaion of memory for the vars structure
		write(1, "Error: Malloc failed.\n", 22);
	// printf("data->vars->name = %s\n", data->vars->name);
		// ft_free_all(data); 
		// Function to free all the allocated memory
	i = -1;
	while (*(envp + (++i))) 
	// Loop to iterate over the environment variables and insert them into the data structure.
	{
		l = ft_sstrncmp(*(envp + i), '='); 
		// Fuction to find the position of the equal sign
		// printf("l = %d\n", l);
		// printf("envp + i = %s\n", *(envp + i));
		// printf("i = %d\n", i);
		if (l != -1 && l != 0)
		{
			name = ft_substr(*(envp + i), 0, l); 
			// Function to extract the name of the variable from the environment variable and store it in the "Name" variable
			// printf("name = %s\n", name);
			value = ft_substr(*(envp + i), l + 1, ft_strlen(*(envp + i)) - l);
			// Function to extract the value of the variable from the environment variable and store it in the "Value" variable
			// printf("value = %s\n", value);
			flag = ft_setenv_local(data->vars, name, value, 0);
			// Function to set the environment variable and store it in the "Flag" variable	after checking if the variable already exists
			// printf("flag = %d\n", flag);
			if (flag == -1)
			// ft_free_all(data)
			write(1, "Error: Malloc failed.\n", 22);
		}
	}
	ft_export_all(data->vars);
	printf("Imported envp correctly\n");
	
}

// Pendiente inicializar la variable de entorno:
// data->custom
// data-> cmd
// data->baseline_in_fd
// data->baseline_out_fd

// Function to initialize the data structure
t_prompt *ft_init_data(char **envp)
{
	(void)envp;
	
	t_prompt *data;
	// Allocating memory for the data structure
	// Verifies if the allocation was successful
	if (!(data = (t_prompt *)malloc(sizeof(t_prompt))))
		perror("Error: Malloc failed.\n");
	ft_import_envp(data, envp);
	// Initializes the data structure with the fuction duplicate the file descriptor
	data->line_infd = dup(STDIN_FILENO);
    data->line_outfd = dup(STDOUT_FILENO);
	// Initializes the data structure
	data->input = NULL;
	// data->cmd = NULL;
	data->prompt = NULL;
	// function to import the environment variables
	printf("Data Initialized\n");
	return(data);
}
 
 

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argv;
// 	(void)envp;
// 	if (argc != 1)
// 			perror("Error: No arguments are allowed.\n");
// 	g_data =ft_init_data(envp);
// 	// printf("g_data->input = %s\n", g_data->input);
	
// 	if (g_data->prompt != NULL)
// 		free (g_data->prompt);
// 	// g_data->prompt = ft_gen_prompt(g_data);	
// 	while (1)
// 		g_data->input = readline(PROMPT);

// }