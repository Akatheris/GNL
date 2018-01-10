/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:16:25 by mlauer            #+#    #+#             */
/*   Updated: 2017/12/21 17:16:45 by mlauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_verif(int fd, char **line, char **str)
{
	if (fd == -1 || line == NULL)
		return (1);
	if (*str != NULL)
	{
		if ((*str = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
			return (1);
	}
	return (0);
}

static char	*ft_read_line(int fd, char *str)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	int		verif;

	verif = 1;
	ret = read(fd, buf, BUFF_SIZE);
	if (ret > 0)
	{
		buf[ret] = '\0';
		if (verif == 1)
		{
			verif = 0;
			str = ft_strdup(buf);
		}
			else
			str = ft_strjoin(str, buf);
	}
	return (str);
}

int			get_next_line(int const fd, char **line)
{
	static char		*str;
	int				i;

	if (ft_verif(fd, line, &str) == 1)
		return (-1);
	if (str != NULL)
		ft_strcpy(*line, str);
	str = ft_read_line(fd, str);
	i = 0;
	if (str[i])
	{
		while (str[i] != '\n' && str[i])
			i++;
		if (i == 0)
			*line = ft_strdup("");
		if (str[i] == '\n')
		{
			*line = ft_strsub(str, 0, i);
			str = &str[i + 1];
		}
		return (1);
	}
	return (0);
}
