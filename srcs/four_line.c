#include "../inc/four_line.h"

void	highlight_cell(int y, int x, t_vars *vr, int flag)
{
	int i;
	int j;
	j = y * 50;
	i = x * 50;
	if (y <= 4 && y >= 1 && x <= 4 && x >= 1)
	{
		if (vr->map[y - 1][x - 1] == '0' || flag == 1)
		{
			
			while (i <= x * 50 + 50)
			{
				mlx_pixel_put(vr->mlx, vr->win, i, j, 0xFF0000);
				mlx_pixel_put(vr->mlx, vr->win, i, j + 50, 0xFF0000);
				i++;
			}
			i = x * 50;
			while (j <= y * 50 + 50)
			{
				mlx_pixel_put(vr->mlx, vr->win, i, j, 0xFF0000);
				mlx_pixel_put(vr->mlx, vr->win, i + 50, j, 0xFF0000);
				j++;
			}
		}
	}
}

void	put_grid(t_vars *vr)
{
	int	i = 50;
	int	j = 50;

	while (i <= 250)
	{
		mlx_pixel_put(vr->mlx, vr->win, i, j, 0x332973);
		mlx_pixel_put(vr->mlx, vr->win, i, j + 50, 0x332973);
		mlx_pixel_put(vr->mlx, vr->win, i, j + 100, 0x332973);
		mlx_pixel_put(vr->mlx, vr->win, i, j + 150, 0x332973);
		mlx_pixel_put(vr->mlx, vr->win, i, j + 200, 0x332973);
		i++;
	}
	i = 50;
	while (i <= 250)
	{
		mlx_pixel_put(vr->mlx, vr->win, j, i, 0x332973);
		mlx_pixel_put(vr->mlx, vr->win, j + 50, i, 0x332973);
		mlx_pixel_put(vr->mlx, vr->win, j + 100, i, 0x332973);
		mlx_pixel_put(vr->mlx, vr->win, j + 150, i, 0x332973);
		mlx_pixel_put(vr->mlx, vr->win, j + 200, i, 0x332973);
		i++;
	}
}

void	put_filling(t_vars *vr)
{
	int i = 50;
	int j = 50;

	while (j <= 250)
	{
		while (i <= 250)
		{
			if ((i >= 100 && i <= 200) && (j >= 100 && j <= 200))
				mlx_pixel_put(vr->mlx, vr->win, i, j, 0x5246A6);//inside
			else
				mlx_pixel_put(vr->mlx, vr->win, i, j, 0x9959D9);//outside
			i++;
		}
		j++;
		i = 50;
	}
}

int	move_oponent(int player_turn, char *input, t_vars *vr)
{
	if (player_turn == vr->map[input[1] - '0' - 1][input[0] - '0' - 1] - '0' - 1)
	{
		highlight_cell(input[1] - '0', input[0] - '0', vr, 1);
		highlight_cell(input[1] + 1 - '0', input[0] - '0', vr, 0);
		highlight_cell(input[1] - 1 - '0', input[0] - '0', vr, 0);
		highlight_cell(input[1] - '0', input[0] + 1 - '0', vr, 0);
		highlight_cell(input[1] - '0', input[0] - 1 - '0', vr, 0);
		vr->prev_x = input[0] - '0';
		vr->prev_y = input[1] - '0';
	}
	return (0);
}
void	balls_update(t_vars *vr)
{
    int i, j, x, y, a, b;
	int color;
	a = 0;
	b = 0;

	put_filling(vr);
	put_grid(vr);
	while (a < 4)
	{
		while (b < 4)
		{
			if (vr->map[a][b] == '1')
				color = 0xF0F2A7;
			if (vr->map[a][b] == '2')
				color = 0xF9A045;
			if (vr->map[a][b] != '0')
			{
				y = (a + 1) * 50 + 25;
				x = (b + 1) * 50 + 25;
				for (i = x - 15; i <= x + 15; i++)
					for (j = y - 15; j <= y + 15; j++)
						if ((i - x) * (i - x) + (j - y) * (j - y) <= 15 * 15)
							mlx_pixel_put(vr->mlx, vr->win, i, j, color);
			}
			b++;
        }
		b = 0;
		a++;
    }
} 

void	print_map(t_vars *vr)
{
	int i = 0;
	while (i < 4)
		printf("%s\n", vr->map[i++]);
}

void	place_ball(int player_turn, char* input, t_vars *vr)
{
	if (vr->map[input[1] - '0' - 1][input[0] - '0' - 1] == '0')
		vr->map[input[1] - '0' - 1][input[0] - '0' - 1] = (player_turn > 0) ? '2': '1';
	printf("%c %c\n", input[0], input[1]);
	print_map(vr);
	balls_update(vr);
}

void orbit(t_vars *vr)
{
	char	tmp;

	tmp = vr->map[0][0];
	vr->map[0][0] = vr->map[0][1];
	vr->map[0][1] = vr->map[0][2];
	vr->map[0][2] = vr->map[0][3];
	vr->map[0][3] = vr->map[1][3];
	vr->map[1][3] = vr->map[2][3];
	vr->map[2][3] = vr->map[3][3];
	vr->map[3][3] = vr->map[3][2];
	vr->map[3][2] = vr->map[3][1];
	vr->map[3][1] = vr->map[3][0];
	vr->map[3][0] = vr->map[2][0];
	vr->map[2][0] = vr->map[1][0];
	vr->map[1][0] = tmp;
	tmp = vr->map[1][1];
	vr->map[1][1] = vr->map[1][2];
	vr->map[1][2] = vr->map[2][2];
	vr->map[2][2] = vr->map[2][1];
	vr->map[2][1] = tmp;
	balls_update(vr);
	print_map(vr);
}

void	move_ball(int player_turn, int y, int x, t_vars *vr)
{
	if (y <= 4 && y >= 1 && x <= 4 && x >= 1)
	{
		if (vr->map[y - 1][x - 1] == '0')
		{
			vr->map[y - 1][x - 1] = player_turn + 1 + '0';
		}
	}
	vr->map[vr->prev_y - 1][vr->prev_x - 1] = '0';
	balls_update(vr);
	print_map(vr);
}

void	putkey(char x, t_vars *vr)
{
	int	j = 0;
	static char *input = NULL;
	static int	move_flag = 0;
	static int	player_turn = 0;
	static int	finished = 0;

	if (input == NULL)
	{
		input = malloc(sizeof(char) * 3);
		if (!input)
			exit(1);
		for (int i = 0; i < 3; i++)
			input[i] = 0;
	}
	if (x == 'D')
	{
		j = 4;
		while (!input[j] && j >= 0)
			j--;
		input[j] = 0;
		j = 0;
	}
	else if (x == 'E')
	{
		if (input[0] && input[1])
		{	
			if (move_flag == 1)
			{
				move_oponent(player_turn, input, vr);
				move_flag = 3;
				input[0] = 0;
				input[1] = 0;
			}
			else if (move_flag == 2)
			{
				place_ball(player_turn, input, vr);
				player_turn = !player_turn;
				finished = 1;
				move_flag = 0;
				input[0] = 0;
				input[1] = 0;
			}
			else if (move_flag == 3)
			{
				move_ball(player_turn, input[1] - '0', input[0] - '0', vr);
				move_flag = 0;
				input[0];
				input[1];
			}
		}
	}
	else if (move_flag != 0 && !input[1])
	{
		while (input[j] && j < 2)
			j++;
		input[j] = x;
	}
	else if (x == 'P' && !input[0] && !input[1])
		move_flag = 2;
	else if (x == 'M' && !input[0] && !input[1])
		move_flag = 1;
	else if (x == 'N' && finished == 1)
	{
		orbit(vr);
		balls_update(vr);
		finished = 0;
	}
	printf("input: %s\n", input);
}

int	key_rec(int keycode, t_vars *vr)
{
	if (keycode == 18)
		putkey('1', vr);
	if (keycode == 19)
		putkey('2', vr);
	if (keycode == 20)
		putkey('3', vr);
	if (keycode == 21)
		putkey('4', vr);
	if (keycode == 36)
		putkey('E', vr);
	if (keycode == 51)
		putkey('D', vr);
	if (keycode == 46)
		putkey('M', vr);
	if (keycode == 35)
		putkey('P', vr);
	if (keycode == 45)
		putkey('N', vr);
	if (keycode == 53)
		exit(0);
	//printf("key: %d\n", keycode);
	return 1;
}

/*
[0,0][0,1][0,2][0,3]
[1,0][1,1][1,2][1,3]
[2,0][2,1][2,2][2,3]
[3,0][3,1][3,2][3,3]
*/

void	init_grid(t_vars *vr)
{
	int i = 0;
	int j = 0;
	while (j < 4)
	{
		vr->map[j] = malloc(sizeof(char) * 5);
		if (!vr->map[j])
			return ;
		while (i < 4)
			vr->map[j][i++] = '0';
		vr->map[j][i] = 0;	
		j++;
		i = 0;
	}
	print_map(vr);
	vr->map[j] = NULL;
}

int	main(void)
{
	t_vars	vr;

	vr.map = malloc(sizeof(char *) * 5);
	if (!vr.map)
		return 0;
	init_grid(&vr);
	vr.mlx = mlx_init();
	vr.win = mlx_new_window(vr.mlx, 300, 300, "hola");
	mlx_key_hook(vr.win, key_rec, &vr);
	put_filling(&vr);
	put_grid(&vr);
	mlx_loop(vr.mlx);
}