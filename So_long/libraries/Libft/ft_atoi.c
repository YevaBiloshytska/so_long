/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:31:13 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/07/05 16:29:58 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		res;
	int		sign;
	char	*num;

	num = (char *)nptr;
	sign = 1;
	res = 0;
	while ((*num >= 9 && *num <= 13) || *num == 32)
		num++;
	if (*num == '+' || *num == '-')
	{
		if (*num == '-')
			sign *= -1;
		num++;
	}
	while (*num >= '0' && *num <= '9')
	{
		res = res * 10 + (*num - 48);
		num++;
	}
	return (sign * res);
}

// int	main(void)
// {
// 	const char	*str;

// 	str = "\e475";
// 	printf("%d", ft_atoi(str));
// 	return (0);
// }