/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:59:25 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/07/05 19:19:49 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// #include <ctype.h>
// void	ft_upper_case(unsigned int i, char *str)
// {
// 	*str = toupper(*str);
// }
// int main(void)
// {
// 	char str[] = "hello";
// 	printf("%s\n", str);
// 	ft_striteri(str, ft_upper_case);
// 	printf("%s\n", str);
// 	return (0);
// }
