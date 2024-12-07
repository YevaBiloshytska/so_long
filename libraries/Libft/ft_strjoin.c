/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:54:41 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/07/10 14:16:00 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

// int	main(void)
// {
// 	char const	*s1 = "Hi ";
// 	char const	*s2 = "everybody";
//     char *joined_str;

//     joined_str = ft_strjoin(s1, s2);
//     if (joined_str)
//     {
//         printf("%s\n", joined_str);
//         free(joined_str);
//     }
// 	printf("1%s\n", ft_strjoin(s1, s2));
// 	return (0);
// }
