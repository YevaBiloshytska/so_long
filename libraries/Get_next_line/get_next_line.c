/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:01:39 by ybiloshy          #+#    #+#             */
/*   Updated: 2024/11/23 15:07:29 by ybiloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*new_line(char *storage)
{
	char	*line;
	char	*ptr;
	size_t	len;

	ptr = fft_strchr(storage, '\n');
	len = ptr - storage + 1;
	line = fft_substr(storage, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*readbuf(int fd, char *storage)
{
	int		rid;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(storage), NULL);
	rid = read(fd, buffer, BUFFER_SIZE);
	while (rid > 0)
	{
		buffer[rid] = '\0';
		storage = fft_strjoin(storage, buffer);
		if (!storage)
		{
			free(buffer);
			return (NULL);
		}
		if (fft_strchr(buffer, '\n'))
			break ;
		rid = read(fd, buffer, BUFFER_SIZE);
	}
	free (buffer);
	if (rid == -1)
		return (free(storage), NULL);
	return (storage);
}

char	*clean_storage(char *storage)
{
	char	*new_storage;
	char	*ptr;
	size_t	len;

	ptr = fft_strchr(storage, '\n');
	if (!ptr)
	{
		new_storage = 0;
		return (free(storage), NULL);
	}
	len = ptr - storage + 1;
	if (!storage[len])
		return (free(storage), NULL);
	new_storage = fft_substr(storage, len, fft_strlen(storage) - len);
	free(storage);
	if (!new_storage)
		return (NULL);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage || !fft_strchr(storage, '\n'))
		storage = readbuf(fd, storage);
	if (!storage)
		return (NULL);
	line = new_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = clean_storage(storage);
	return (line);
}

#include <stdio.h>
#include <string.h>

// int main()
// {
// 	int	fd;
// 	char *line;
// 	fd = open("text.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
// 	return (0);
// }

// Функция для временного файла с указанным текстом
// int create_temp_file(const char *content)
// {
//     char filename[] = "/tmp/testfileXXXXXX";
//     int fd = mkstemp(filename);

//     if (fd < 0)
//     {
//         perror("Failed to create temp file");
//         return -1;
//     }

//     if (content != NULL) {
//         write(fd, content, strlen(content));
//         lseek(fd, 0, SEEK_SET);
//     }

//     return fd;
// }

// // Функция для тестирования get_next_line с переданным текстом
// void test_with_content(const char *content)
// {
//     int fd;
//     char *line;

//     fd = create_temp_file(content);
//     if (fd < 0)
//         return;

//     printf("Testing content:\n%s\n", content ? content : "(null)");
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line); // Не забывайте освобождать память
//     }

//     close(fd);
// }

// int main(void)
// {
//     // Тестируем с несколькими строками
//     // test_with_content("Hello, world!\nThis is a test.\n");
// 	test_with_content("\n");

//     // Тестируем с одной строкой без символа новой строки
//     test_with_content("Single line without newline");

//     // Тестируем с пустым содержимым
//     test_with_content("");

//     // Тестируем с длинным содержимым
//     test_with_content("Line 1\nLine 2\nLine 3\nAnother long line to test\n");

// 	// Тестируем с 0
// 	test_with_content("0");

// 	// Тестируем с NULL
// 	test_with_content(NULL);
// 	 test_with_content("Hello\nworld\nThis is a test.\n");
// 	printf("BUFFER_SIZE = %d", BUFFER_SIZE);
//     return 0;
// }