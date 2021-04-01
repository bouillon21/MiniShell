/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:32:13 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/01 22:33:49 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_new_token(t_token *token)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	new_token->separate = 0;
	new_token->command = 0;
	new_token->args = 0;
	new_token->flags = 0;
	new_token->prev = token;
	new_token->next = NULL;

	return (new_token);
}

t_list_hist	*create_new_list(t_list_hist *hist)
{
	t_list_hist *new_list;

	new_list = malloc(sizeof(t_list_hist));
	new_list->prev = hist;
	new_list->next = NULL;
}