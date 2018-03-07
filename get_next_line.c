/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:16:25 by mlauer            #+#    #+#             */
/*   Updated: 2018/03/07 16:36:31 by mlauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_verif(int fd, char **line, char **str)
{
	char	buf[1];

	if (fd == -1 || line == NULL || read(fd, buf, 0))
		return (1);
	if (*str == NULL)
	{
		if ((*str = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
			return (1);
	}
	return (0);
}

char		*ft_read_line(int fd, char *str)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(str, buf);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
	}
	return (str);
}

char		*ft_get_after_nl(char *str, int i)
{
	char *tmp;

	tmp = ft_strdup(&str[i + 1]);
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

int			get_next_line(int const fd, char **line)
{
	static char		*str;
	int				i;

	if (ft_verif(fd, line, &str) == 1)
		return (-1);
	str = ft_read_line(fd, str);
	i = 0;
	if (str[i])
	{
		while (str[i] != '\n' && str[i] && str[i + 1] != '\0')
			i++;
		if (i == 0)
		{
			(*line) = ft_strdup("");
			str = ft_get_after_nl(str, i);
		}
		else
		{
			(*line) = ft_strsub(str, 0, i);
			str = ft_get_after_nl(str, i);
		}
		return (1);
	}
	else
		(*line) = ft_strdup("");
	return (0);
}
