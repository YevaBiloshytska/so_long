/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:22:36 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/07/12 12:54:45 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_len(int n)
{
	unsigned int	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		len;
	int		i;
	long	nbr;

	i = 0;
	nbr = n;
	len = ft_len(nbr);
	arr = (char *)malloc((len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	if (nbr < 0)
	{
		arr[0] = '-';
		i++;
		nbr = -nbr;
	}
	arr[len] = '\0';
	while (len > i)
	{
		arr[--len] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	return (arr);
}

// int main()
// {
// 	int	n;

// 	n = 0;
// 	printf("int n = %i\n", n);
// 	printf("%s\n", ft_itoa(n));
// }