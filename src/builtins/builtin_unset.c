/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 21:14:24 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/24 16:20:53 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

//Debe eliminar la variable de ambiente dada como argumento.
//Como debe hacerlo.??
//Si no tiene argumentos debe mostrar que no hay  "unset: not enough arguments"
//Debe acceder a la variable y contar cuantos elementos hay actualmente,
// luego reserva un nuevo array del tamaño de la lista anterior - el elemento
// a eliminar, donde ira el nuevo array
// recorrer la lista envp mientras que no sea null ,agregamos los punteros al
// nuevo arreglo si no son  la variable  y tambien + 1en (key) + 1 sea igual = ,
//saltamos al siguiente
//agregar NULL al final.
//Debe retornar la lista de variable de ambiente actualizada
int	filter_envp(t_shell *shell, char **cmd_args)
{
	int	i;
	int	j;
	int	finded;
	int	keylen;

	finded = 0;
	keylen = 0;
	j = 0;
	while (shell->env[j] != NULL)
	{
		i = 1;
		while (cmd_args[i])
		{
			keylen = strlen(cmd_args[i]);
			if (shell->env[j] != NULL && ft_strncmp(shell->env[j],
					cmd_args[i], keylen) == 0 && shell->env[j][keylen] == '=' )
			{
				finded++;
				(free(shell->env[j]), shell->env[j] = NULL);
			}
			i++;
		}
		j++;
	}
	return (j - finded);
}

void	compact_envp(t_shell *shell, char **new_env, int len_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < len_env)
	{
		if (shell->env[i] != NULL)
		{
			new_env[j] = shell->env[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void	printenvp(t_shell *shell)
{
	int	k;

	k = 0;
	while (shell->env[k] != NULL)
	{
		printf("%s\n", shell->env[k]);
		k++;
	}
}

int	builtin_unset(t_shell *shell, char **cmd_args)
{
	int		len_env;
	char	**new_env;

	//printf("==================ANTES===============\n");
	//printenvp(shell);
	len_env = 0;
	if (cmd_args[1] == NULL)
		return (0);
	len_env = filter_envp(shell, cmd_args);
	new_env = malloc(sizeof(char *) * (len_env + 1));
	if (!new_env)
	{
		perror("malloc");
		return (1);
	}
	compact_envp(shell, new_env, len_env);
	//printf("==================DESPUES===============\n");
	//printenvp(shell);
	return (0);
}
