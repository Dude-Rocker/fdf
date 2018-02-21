/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finfdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgladush <vgladush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:53:50 by vgladush          #+#    #+#             */
/*   Updated: 2018/02/03 16:38:54 by vgladush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				ft_exit(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

void			ft_hk_sec(int key, t_ml *mw)
{
	if (key == 53)
		exit(1);
	else if (key == 15)
		mw->clr += 30;
	else if (key == 17)
		mw->clr -= 30;
	else if (key == 5)
		mw->clr += 10000;
	else if (key == 4)
		mw->clr -= 10000;
}

int				ft_hot_key(int key, t_ml *mw)
{
	double		l[6];

	l[0] = 0.0;
	l[1] = 0.0;
	l[2] = 0.0;
	l[3] = 0.0;
	l[4] = 0.0;
	l[5] = 0.0;
	if (key == 13)
		mw->y -= 10;
	else if (key == 1)
		mw->y += 10;
	else if (key == 0)
		mw->x -= 10;
	else if (key == 2)
		mw->x += 10;
	ft_hk_sec(key, mw);
	mlx_clear_window(mw->mlx, mw->win);
	ft_goriz(*mw, mw->crd, mw->sz, l);
	ft_vertic(*mw, mw->crd, mw->sz, l);
	return (0);
}

void			ft_versec(t_ml mw, t_fdf *crd, t_fdf *tmp, double *o)
{
	o[1] = (double)(tmp->color - crd->color) / (tmp->y - crd->y);
	o[2] = 0.0;
	o[3] = 0.0;
	o[5] = 1.0;
	o[0] = 0.5;
	o[4] = 0.0;
	if (tmp->z != crd->z)
	{
		o[0] = (double)(crd->x - tmp->x) / (tmp->y - crd->y);
		if (o[0] > 1.0)
		{
			o[5] = (double)(tmp->y - crd->y) / (crd->x - tmp->x);
			o[0] = 1.0;
		}
	}
	while (crd->y + (int)o[4] != tmp->y)
	{
		mlx_pixel_put(mw.mlx, mw.win, crd->x - (int)o[3] + mw.x, crd->y +
			(int)o[4] + mw.y, crd->color + (int)o[2] + mw.clr);
		o[2] += o[1];
		o[3] += o[0];
		o[4] += o[5];
	}
}
