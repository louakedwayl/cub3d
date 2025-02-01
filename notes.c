




/*


	while (start_angle < end_angle)
	{
		distance = process_raycasting(data, start_angle);

		// printf("distance : %i\n", distance);

		i = 0;
		if (distance > 10)
		{
			while (i < abs(WINDOW_WIDTH / range)) // 12
			{
				if (!DEBUG)
					draw_pixel_column(data, column, distance); //, DRAW
				i++;
				column++;
			}
		}
		else
			column += 1;
		
		// printf("start_angle : %i\n", start_angle);

		start_angle++;

		//start_angle += 1000;
	}

*/