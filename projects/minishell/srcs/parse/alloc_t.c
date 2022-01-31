/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaatar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 01:26:08 by bbaatar           #+#    #+#             */
/*   Updated: 2022/01/31 01:26:10 by bbaatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**alloc_t(void)
{
	int i;
	char **arr;

	arr = (char **)malloc(MAX_ALLOC * sizeof(char *));
	memset (arr, 0, MAX_ALLOC * sizeof(char *));
	i = 0;
	while (i < MAX_ALLOC)
	{
		arr[i] = (char *)malloc(MAX_ALLOC * sizeof(char));
		memset (arr[i], 0, MAX_ALLOC * sizeof(char));
		i++;
	}
	return (arr);
}
