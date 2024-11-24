/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:56:34 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/07/11 17:23:13 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(const char *str, char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

static char	**ft_free(char **res, size_t j)
{
	while (j > 0)
		free(res[--j]);
	free(res);
	return (NULL);
}

static void	ft_fill_split(char **res, const char *s, char c, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (i < len)
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			res[j] = ft_substr(s, start, i - start);
			if (!res[j])
			{
				ft_free(res, j);
				return ;
			}
			j++;
		}
	}
	res[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	ft_fill_split(res, s, c, len);
	return (res);
}

// int main(void)
// {
//     char const *s = " ";
//     char c = ' ';
//     char **result = ft_split(s, c);
//     if (result)
//     {
//         for (size_t i = 0; result[i]; i++)
//         {
//             printf("Result[%zu]: '%s'\n", i, result[i]);
//             free(result[i]);
//         }
//         free(result);
//     }
//     return 0;
// }
