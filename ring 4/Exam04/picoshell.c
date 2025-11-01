/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:48:12 by cprot             #+#    #+#             */
/*   Updated: 2025/10/29 17:32:51 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int	picoshell(char **cmds[])
{
	// Variables nécessaires ?
	int fd[2];
	int in_fd = 0;
	pid_t pid;
	int ret = 0;
	int status;

	// Boucle sur les commandes ?
	for (int i = 0; cmds[i]; i++)
	{
		// creer un pipe sauf pour la derniere commande
		if (cmds[i + 1] && pipe(fd) == -1)
		{
			if (in_fd != 0)
				close(in_fd);
			// ferme in_fd car il a ete ouvert dans l iteration precedente
			return (1);
		}
		// creer un enfant
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
			{
				close(fd[1]);
				close(fd[0]);
			}
			if (in_fd != 0)
				close(in_fd);
			return (1);
		}
		// role enfant
		else if (pid == 0)
		{
			if (in_fd != 0)
			{
				dup2(in_fd, 0);
				close(in_fd);
			}
			if (cmds[i + 1])
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		else // role parent
		{
			if (in_fd != 0)
			{
				close(in_fd);
			}
			if (cmds[i + 1])
			{
				close(fd[1]);
				in_fd = fd[0];
			}
		}
	}
	while (wait(&status) > 0)
	{
		if (status != 0)
			ret = 1;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	char	**cmds[100];
	int		i;
	int		j;

	if (argc < 2)
	{
		printf("Usage: %s cmd1 arg1 arg2 \"|\" cmd2 arg1 \"|\"\n", argv[0]);
		return (1);
	}

	i = 0;
	j = 1;
	cmds[i] = &argv[j];
	
	while (j < argc)
	{
		if (argv[j][0] == '|' && argv[j][1] == '\0')
		{
			argv[j] = NULL;
			i++;
			cmds[i] = &argv[j + 1];
		}
		j++;
	}
	cmds[i + 1] = NULL;

	int ret = picoshell(cmds);
	printf("Return: %d\n", ret);
	return (ret);
}