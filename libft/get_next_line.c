/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:00:16 by minsuki2          #+#    #+#             */
/*   Updated: 2022/07/22 18:20:35 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_lstfclean(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return (NULL);
}

static t_list	*read_check(int fd, t_list **lst, ssize_t *rd)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*rd = read(fd, buf, BUFFER_SIZE);
	if (*rd <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[*rd] = '\0';
	return (ft_lstadd_back_last(lst, ft_lstnew_str(buf)));
}

static ssize_t	line_check_len(int fd, t_list **lst, size_t *len)
{
	char			*pos;
	t_list			*tmp;
	ssize_t			rd;
	size_t			content_len;

	if (*lst)
	{
		pos = ft_strlen_chr_init((*lst)->content, '\n', &content_len, 0);
		if (pos)
		{
			*len += (pos - (*lst)->content) + 1;
			return (0);
		}
		(*len) += content_len;
	}
	tmp = read_check(fd, lst, &rd);
	if (tmp)
		rd = line_check_len(fd, &tmp, len);
	return (rd);
}

static char	*make_line(t_list **lst, size_t line_len)
{
	char	*line;
	char	*last;
	t_list	*first;
	size_t	i;

	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	line[0] = '\0';
	first = *lst;
	i = 0;
	while (*lst)
	{
		ft_strlen_chr_init(line, 0, &i, 1);
		ft_strlcat_dstlen(line, i, (*lst)->content, line_len + 1);
		if (!(*lst)->next)
			last = (*lst)->content;
		*lst = (*lst)->next;
	}
	if (last && *(last + line_len - i))
		*lst = ft_lstnew_str(ft_strdup(last + line_len - i));
	ft_lstfclean(&first);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lst;
	ssize_t			rd;
	size_t			line_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_len = 0;
	rd = line_check_len(fd, &fd_lst, &line_len);
	if (rd == -1 || (!rd && !line_len))
		return ((char *)ft_lstfclean(&fd_lst));
	return (make_line(&fd_lst, line_len));
}
