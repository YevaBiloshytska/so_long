/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:50:21 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/23 17:01:41 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

size_t	fft_strlen(char *s);
char	*fft_strjoin(char *s1, char *s2);
char	*fft_strchr(char *s, int c);
char	*fft_substr(char *s, unsigned int start, size_t len);
char	*new_line(char *storage);
char	*readbuf(int fd, char *storage);
char	*clean_storage(char *storage);
char	*get_next_line(int fd);

#endif