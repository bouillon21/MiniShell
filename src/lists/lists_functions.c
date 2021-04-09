/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:32:13 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/09 22:28:47 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_loop(t_token **token)
{
	int i;

	i = -1;
	if ((*token)->command)
		clear_buf(&(*token)->command);
	if ((*token)->args)
		while ((*token)->args[++i])
			clear_buf(&(*token)->args[i]);
	if ((*token)->flags)
		while ((*token)->flags[++i])
			clear_buf(&(*token)->flags[i]);
	free((*token)->args);
	// free((*token)->flags);
}

void	clear_token(t_all *all)
{
	t_token	*tmp;

	while (all->token)
	{
		tmp = all->token;
		clear_loop(&all->token);
		all->token = all->token->prev;
		free(tmp);
	}
	all->token = create_new_token(0);
}

t_token	*create_new_token(t_token *token)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	new_token->separate = 0;
	new_token->command = NULL;
	new_token->args = 0;
	new_token->flags = 0;
	new_token->prev = token;
	new_token->next = NULL;
	return (new_token);
}

t_list_hist *create_new_list(t_list_hist *hist)
{
	t_list_hist *new_list;

	new_list = malloc(sizeof(t_list_hist));
	new_list->string = NULL;
	new_list->prev = hist;
	new_list->next = NULL;
	return (new_list);
}