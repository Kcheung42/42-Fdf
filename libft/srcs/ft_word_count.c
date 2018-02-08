/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:31:01 by kcheung           #+#    #+#             */
/*   Updated: 2016/11/15 21:31:02 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_word_count(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
		}
		if (i == 0 || s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}
