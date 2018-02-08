/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toksplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 12:32:08 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/18 23:38:04 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_toksplit(char *line, const char *delim)
{
	int		position;
	int		bufsize;
	char	**tokens;
	char	*token;

	bufsize = TOK_BUFSIZE;
	if (!(tokens = malloc(bufsize * sizeof(char*))))
		return (NULL);
	token = ft_strtok(line, delim);
	position = 0;
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = ft_realloc(tokens, bufsize * sizeof(char*));
			if (!tokens)
				return (NULL);
		}
		token = ft_strtok(NULL, delim);
	}
	tokens[position] = NULL;
	return (tokens);
}
