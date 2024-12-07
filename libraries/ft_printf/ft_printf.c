/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 21:09:04 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/09/01 18:57:06 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put_hex(size_t n, char *hex)
{
	int		i;

	i = 0;

	if (n / 16)
		i += ft_put_hex(n / 16, hex);
	i += ft_printchar(hex[n % 16]);
	return (i);
}

static int	ft_put_ptr(void *ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
		return (ft_printstr("(nil)"));
	i += ft_printstr("0x");
	i += ft_put_hex((size_t)ptr, "0123456789abcdef");
	return (i);
}

static int	get_flags(const char *s, int i, va_list args)
{
	int	return_val;

	return_val = 0;
	if (s[i] == 'c')
		return_val += ft_printchar(va_arg(args, int));
	else if (s[i] == 's')
		return_val += ft_printstr(va_arg(args, char *));
	else if (s[i] == 'x')
		return_val += ft_put_hex(va_arg(args, unsigned int),
								 "0123456789abcdef");
	else if (s[i] == 'X')
		return_val += ft_put_hex(va_arg(args, unsigned int),
								 "0123456789ABCDEF");
	else if (s[i] == 'p')
		return_val += ft_put_ptr(va_arg(args, void *));
	else if (s[i] == 'd' || s[i] == 'i')
		return_val += ft_printnum(va_arg(args, int));
	else if (s[i] == 'u')
		return_val += ft_printunum(va_arg(args, unsigned int));
	else if (s[i] == '%')
		return_val += ft_printchar('%');
	return (return_val);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		size;
	va_list	args;

	i = 0;
	size = 0;
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			size += get_flags(s, i, args);
		}
		else
			size += ft_printchar(s[i]);
		i++;
	}
	va_end(args);
	return (size);
}

// int main() {
//     // Примеры тестов
//     char c = 'A';
//     const char *str = "Hello, World!";
//     int num = 12345;
//     unsigned int hex_num = 0xABCD;
//     void *ptr = &num;

//     // // Тестирование спецификаторов формата
//     // ft_printf("Testing %%c:\n");
//     // ft_printf("Character: %c\n", c);

//     // ft_printf("\nTesting %%s:\n");
//     // ft_printf("String: %s\n", str);

//     // ft_printf("\nTesting %%d:\n");
//     // ft_printf("Integer: %d\n", num);

//     // ft_printf("\nTesting %%x:\n");
//     // ft_printf("Hexadecimal (lowercase): %x\n", hex_num);

//     // ft_printf("\nTesting %%X:\n");
//     // ft_printf("Hexadecimal (uppercase): %X\n", hex_num);

//     // ft_printf("\nTesting %%p:\n");
//     // ft_printf("Pointer: %p\n", ptr);

//     // ft_printf("\nTesting %%u:\n");
//     // unsigned int unsigned_num = 12345;
//     // ft_printf("Unsigned integer: %u\n", unsigned_num);

//     // ft_printf("\nTesting %%%%\n");
//     // ft_printf("Percent sign: %%\n");

// 	//ft_printf("cspdiuxX\n%\n");
// 	//ft_printf("number %i, string %s\n", "Yeva", -2147483648);
// 	//printf("number %i, string %d\n", "Yeva", -214);

//    // return 0;
// //}
