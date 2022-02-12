/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaatar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:43:24 by bbaatar           #+#    #+#             */
/*   Updated: 2022/02/12 14:43:26 by bbaatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_char_in(char ch, char *delimiters)
{
	while (*delimiters)
	{
		if (ch == *delimiters)
			return (true);
		delimiters++;
	}
	return (false);
}

int	locate_chars(char *s, char *delimiters)
{
	int		i;
	char	open;
	bool	escape;

	i = 0;
	open = 0;
	escape = false;
	while (s[i])
	{
		if (escape)
		{
			escape = false;
			i++;
			continue ;
		}
		if (s[i] == '"' || s[i] == '\'')
		{
			if (open == 0)
				open = s[i];
			else if (open == s[i])
				open = 0;
		}
		else if (s[i] == '\\')
			escape = true;
		else if (open == 0 && is_char_in(s[i], delimiters))
			return (i);
		i++;
	}
	return (-1);
}

int	locate_char(char *s, char delimiter)
{
	char	delimiters[2];

	delimiters[0] = delimiter;
	delimiters[1] = 0;
	return (locate_chars(s, delimiters));
}
