/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:48:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/04 10:19:59 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start(void)
{
	add_history(g_s->in);
}

void	ft_shlvl(void)
{
	int	i;

	i = 0;
	while (ft_strncmp(g_s->env[i], "SHLVL=", 6))
		if (!g_s->env[++i])
			exit(write(2, "unset\n", 6));
	free(g_s->env[i]);
	if (ft_atoi(g_s->env[i] + 6) == 999)
		g_s->env[i] = "SHLVL=";
	else if (!ft_atoi(g_s->env[i] + 6))
		g_s->env[i] = "SHLVL=1";
	else
		g_s->env[i] = ft_strjoin("SHLVL=",
				ft_itoa(ft_atoi(g_s->env[i] + 6) + 1), 0, 1);
}

void	ft_init_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_s->env = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (env[++i])
		g_s->env[i] = ft_substr(env[i], 0, ft_strlen(env[i]));
	g_s->env[i] = NULL;
}

void	ft_init_struct(void)
{
	g_s = malloc(sizeof(t_s));
	g_s->in = NULL;
	g_s->env = NULL;
	g_s->ex_code = 0;
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_init_struct();
	ft_init_env(env);
	ft_shlvl();
	while (1)
	{
		ft_sig();
		g_s->in = readline("$ ");
		if (!g_s->in)
			exit(0);
		else if (!g_s->in[0])
		{
			free(g_s->in);
			continue ;
		}
		else
			ft_start();
		if (!g_s->in)
			free(g_s->in);
	}
}
