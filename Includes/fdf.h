/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgladush <vgladush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:14:11 by vgladush          #+#    #+#             */
/*   Updated: 2018/02/03 16:44:46 by vgladush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"

typedef	struct		s_ml
{
	void			*mlx;
	void			*win;
	int				sz;
	int				x;
	int				y;
	int				clr;
	struct s_fdf	*crd;
}					t_ml;

typedef	struct		s_fdf
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_fdf	*next;
}					t_fdf;

void				ft_logfdf(t_fdf *crd, t_ml *mw);
void				ft_versec(t_ml mw, t_fdf *crd, t_fdf *tmp, double *o);
int					ft_hot_key(int key, t_ml *mw);
int					ft_exit(void *par);
void				ft_goriz(t_ml mw, t_fdf *tmp, int i, double *o);
void				ft_vertic(t_ml mw, t_fdf *crd, int i, double *o);

#endif
