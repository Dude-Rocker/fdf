/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgladush <vgladush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:41:20 by vgladush          #+#    #+#             */
/*   Updated: 2018/02/03 14:17:21 by vgladush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int		validfl(char *s)
{
	while (*s)
	{
		if (*s > 57 || *s < 48)
			exit(write(1, "error\n", 6));
		while (*s < 58 && *s > 47)
			s++;
		if (*s == ',')
			s += 9;
		while (*s && *s == ' ')
			s++;
	}
	return (0);
}

static	int		checkmax(t_fdf *crd)
{
	int			x;
	int			y;
	int			res;

	x = 0;
	y = 0;
	while (crd)
	{
		if (crd->x > x)
			x = crd->x;
		if (crd->y > y)
			y = crd->y;
		crd = crd->next;
	}
	res = ((1200 / x) > (750 / y) ? (750 / y) : (1200 / x));
	if (res % 2)
		res -= 1;
	if (res > 180)
		res = 180;
	else if (res < 6)
		res = 6;
	return (res);
}

static	void	writecoord(t_fdf **crd, char *s, int *os)
{
	char		clr[7];
	int			i;

	(*crd)->x = os[0];
	(*crd)->y = os[1];
	(*crd)->z = ft_atoi(s);
	while (*s && *s < 58 && *s > 47)
		s++;
	if (*s == ',' && !(i = 0))
	{
		s += 3;
		while (*s && *s != ' ')
			clr[i++] = *s++;
		clr[i] = '\0';
		(*crd)->color = (int)ft_basetoint(clr, 16);
	}
	else
		(*crd)->color = 16777215;
	(*crd)->next = NULL;
}

static	void	checkcoord(t_fdf **buf, int fd, int *os)
{
	char		*ln;
	int			i;
	t_fdf		*tmp;

	while (get_next_line(fd, &ln) && !(os[0] = 0))
	{
		i = 0;
		validfl(ln);
		while (ln[i] && (os[0] += 1))
		{
			writecoord(buf, ln + i, os);
			while (ln[i] != ' ' && ln[i])
				i++;
			while (ln[i] == ' ')
				i++;
			if (!((*buf)->next = (t_fdf *)malloc(sizeof(t_fdf))))
				return ;
			tmp = *buf;
			*buf = (*buf)->next;
		}
		os[1] += 1;
		free(ln);
	}
	free(tmp->next);
	tmp->next = NULL;
}

int				main(int ac, char **av)
{
	int			fd;
	int			os[2];
	t_fdf		*coord;
	t_fdf		*buf;
	t_ml		mw;

	os[0] = 1;
	os[1] = 1;
	if (!(coord = (t_fdf *)malloc(sizeof(t_fdf))))
		return (0);
	buf = coord;
	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		exit(write(1, "error\n", 6));
	mw.mlx = mlx_init();
	mw.win = mlx_new_window(mw.mlx, 1680, 1050, "mlx");
	mw.x = 0;
	mw.y = 0;
	mw.clr = 0;
	mw.crd = coord;
	checkcoord(&buf, fd, os);
	mw.sz = checkmax(coord);
	ft_logfdf(mw.crd, &mw);
	return (0);
}
