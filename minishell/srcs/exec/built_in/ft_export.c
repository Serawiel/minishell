/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:01:17 by scavalli          #+#    #+#             */
/*   Updated: 2025/09/13 10:03:25 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	add_exportvar(t_env **env, char *name, char *value)
{
	t_env	*new_exportvar;
	t_env	*last;

	new_exportvar = malloc(sizeof(t_env));
	if (!new_exportvar)
		error("Error at malloc in add_exportvar");
	new_exportvar->name = ft_strdup(name);
	new_exportvar->value = ft_strdup(value);
	if (!*env)
	{
		new_exportvar->next = NULL;
		new_exportvar->prev = NULL;
		*env = new_exportvar;
	}
	else
	{
		last = find_last_exportvar(*env);
		last->next = new_exportvar;
		new_exportvar->prev = last;
		new_exportvar->next = NULL;
	}
}

bool	print_export(t_env *env, t_token *token)
{
	if (!token->next)
	{
		while (env)
		{
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
			env = env->next;
		}
		return (true);
	}
	return (false);
}

static void	handle_export_var(t_env **env, t_localvar **localvar, char *name,
		t_localvar *local)
{
	t_env	*is_inenv;

	is_inenv = is_env(*env, name);
	if (is_inenv)
		free_env(is_inenv, env);
	if (local)
	{
		add_exportvar(env, local->name, local->value);
		free_localvar(local, localvar);
	}
}

static void	process_export_assignment(t_env **env, t_localvar **localvar,
		char *str, char *name)
{
	char		*value;
	t_localvar	*local;
	int			i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	local = is_local(*localvar, name);
	if (is_env(*env, name))
		free_env(is_env(*env, name), env);
	value = ft_substr(str, i + 1);
	add_exportvar(env, name, value);
	if (local)
		free_localvar(local, localvar);
	free(value);
}

void	ft_export(t_env **env, t_token *token, t_localvar **localvar)
{
	char		*name;
	t_localvar	*local;
	int			i;

	i = 0;
	if (print_export(*env, token))
		return ;
	while (token->next->str[i] && token->next->str[i] != '=')
		i++;
	name = ft_strndup(token->next->str, i);
	if (!ft_contains(token->next->str, "="))
	{
		local = is_local(*localvar, name);
		handle_export_var(env, localvar, token->next->str, local);
		free(name);
		return ;
	}
	process_export_assignment(env, localvar, token->next->str, name);
	free(name);
}
