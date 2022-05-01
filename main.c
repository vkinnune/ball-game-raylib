#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <stdlib.h>

#define MAX_EXPLOSIONS 10
#define MAX_BALLS 100

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
	int	explosions[MAX_EXPLOSIONS];
	int	explosions_x_y[MAX_EXPLOSIONS][2];
	bzero(explosions_x_y, sizeof(explosions_x_y));
	bzero(explosions, sizeof(explosions));
	int	explosion_index = 0;
	DisableCursor();
	int		ball_count = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
		{
			int i;
			int	x;
			float	p2_ball_velocity_x[MAX_BALLS];
			float	p2_ball_velocity_y[MAX_BALLS];
			float	p2_ball_pos_x[MAX_BALLS];
			float	p2_ball_pos_y[MAX_BALLS];
			float	p2_ball_sizes[MAX_BALLS];

			i = 0;
			if (ball_count == MAX_BALLS)
				ball_count = 0;
			if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
			{
				p2_ball_pos_x[ball_count] = rand() % 800;
				p2_ball_pos_y[ball_count] = rand() % 400;
				p2_ball_velocity_x[ball_count] = (rand() % 10) - 5;
				p2_ball_velocity_y[ball_count] = (rand() % 10) - 5;
				p2_ball_sizes[ball_count] = rand() % 30;
				ball_count++;
			}
			while (i != ball_count)
			{
				x = 0;
				while (x != explosion_index)
				{
					if (explosions[x] > 0)
					{
						p2_ball_velocity_x[i] += 20 / (explosions_x_y[x][0] - p2_ball_pos_x[i]);
						p2_ball_velocity_y[i] += 20 / (explosions_x_y[x][1] - p2_ball_pos_y[i]);
					}
					x++;
				}
				p2_ball_velocity_y[i] += 0.15;
				if (p2_ball_pos_y[i] + p2_ball_sizes[i] > screenHeight || p2_ball_pos_y[i] - p2_ball_sizes[i] < 0)
					p2_ball_velocity_y[i] = (p2_ball_velocity_y[i] * -0.9);
				if (p2_ball_pos_x[i] + p2_ball_sizes[i] > screenWidth || p2_ball_pos_x[i] - p2_ball_sizes[i] < 0)
					p2_ball_velocity_x[i] = (p2_ball_velocity_x[i] * -0.9);
				DrawCircle(p2_ball_pos_x[i] += p2_ball_velocity_x[i], p2_ball_pos_y[i] += p2_ball_velocity_y[i], p2_ball_sizes[i], BLUE);
				i++;
			}
		}
		{
			int	mouse_x = GetMouseX();
			int	mouse_y = GetMouseY();
			int	i;
            ClearBackground(RAYWHITE);
			//draw sight
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				explosions_x_y[explosion_index][0] = mouse_x;
				explosions_x_y[explosion_index][1] = mouse_y;
				explosions[explosion_index] = 20;
				explosion_index++;
			}
			i = 0;
			if (explosion_index == MAX_EXPLOSIONS)
				explosion_index = 0;
			while (i != MAX_EXPLOSIONS)
			{
				if (explosions[i] > 0)
				{
					DrawCircle(explosions_x_y[i][0], explosions_x_y[i][1], 10 + explosions[i], ORANGE);
					explosions[i]--;
				}
				printf("%d\n", explosion_index);
				i++;
			}
			{
				DrawLine(mouse_x, mouse_y + 20, mouse_x, mouse_y - 20, RED);
				DrawLine(mouse_x + 20, mouse_y, mouse_x - 20, mouse_y, RED);
			}
		}
        EndDrawing();
    }
    CloseWindow();
    return 0;
}