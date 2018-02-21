/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logfdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgladush <vgladush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:26:17 by vgladush          #+#    #+#             */
/*   Updated: 2018/02/03 16:34:03 by vgladush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	ft_searc(t_fdf *tmp, int i, int u)
{
	int			k;
	t_fdf		*buf;

	k = 0;
	buf = tmp;
	while (tmp)
	{
		if (u < tmp->y)
			u = tmp->y;
		tmp = tmp->next;
	}
	k = i / 2 * u;
	while (buf)
	{
		buf->x = buf->x * i + k;
		if (buf->next && buf->next->y > buf->y)
			k -= i / 2;
		buf->y *= i;
		buf = buf->next;
	}
}

static	void	ft_height(t_fdf *tmp, int i, double *o)
{
	int			k;
	t_fdf		*buf;

	k = 0;
	buf = tmp;
	while (tmp)
	{
		if (tmp->z > k)
			k = tmp->z;
		tmp = tmp->next;
	}
	if (k && (int)(o[4] = (i - i / 10)) == i)
		o[4] = (o[4] - 1.0) / k;
	else if (k)
		o[4] /= k;
	while (buf)
	{
		buf->y -= buf->z * o[4];
		buf = buf->next;
	}
}

void			ft_goriz(t_ml mw, t_fdf *tmp, int i, double *o)
{
	while (tmp)
	{
		if (tmp->next && tmp->x < tmp->next->x)
		{
			o[0] = (double)(tmp->next->color - tmp->color) /
			(tmp->next->x - tmp->x);
			o[1] = 0.0;
			o[2] = 0.0;
			o[3] = (double)(tmp->y - tmp->next->y) / i;
			while (tmp->x < tmp->next->x)
			{
				mlx_pixel_put(mw.mlx, mw.win, tmp->x + mw.x, tmp->y -
					(int)o[2] + mw.y, tmp->color + (int)o[1] + mw.clr);
				if (tmp->next->y != tmp->y)
					o[2] += o[3];
				tmp->x += 1;
				o[1] += o[0];
			}
			tmp->x -= i;
		}
		else
			mlx_pixel_put(mw.mlx, mw.win, tmp->x + mw.x, tmp->y + mw.y,
				tmp->color + mw.clr);
		tmp = tmp->next;
	}
}

void			ft_vertic(t_ml mw, t_fdf *crd, int i, double *o)
{
	t_fdf		*tmp;

	tmp = crd;
	while (crd)
	{
		while (tmp && tmp->x != (crd->x - i / 2))
			tmp = tmp->next;
		if (tmp)
			ft_versec(mw, crd, tmp, o);
		crd = crd->next;
		tmp = crd;
	}
}

void			ft_logfdf(t_fdf *crd, t_ml *mw)
{
	double		l[6];

	l[0] = 0.0;
	l[1] = 0.0;
	l[2] = 0.0;
	l[3] = 0.0;
	l[4] = 0.0;
	l[5] = 0.0;
	ft_searc(crd, mw->sz, 1);
	ft_height(crd, mw->sz, l);
	ft_goriz(*mw, crd, mw->sz, l);
	ft_vertic(*mw, crd, mw->sz, l);
	mlx_key_hook(mw->win, ft_hot_key, mw);
	mlx_hook(mw->win, 17, 1L << 17, ft_exit, mw);
	mlx_loop(mw->mlx);
}
