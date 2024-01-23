#ifndef FOUR_LINE_H
# define FOUR_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../mlx/mlx.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	**map;
	int		prev_x;
	int		prev_y;
}	t_vars;

int		main(void);

#endif
