/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:29:09 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/07/04 21:12:31 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	value;
	size_t			len;

	len = ft_strlen(s);
	value = (unsigned char)c;
	if (value == '\0')
		return ((char *)(s + len));
	while (len--)
	{
		if (s[len] == value)
			return ((char *)(s + len));
	}
	return (NULL);
}

// int main()
// {
// 	const char	*s;
// 	int			c;

// 	c = 72;
// 	s = "HO";
// 	printf("%s", ft_strrchr(s, c));
// }