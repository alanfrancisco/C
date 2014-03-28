/* AF 1/22/2014 Need input constraints */
#define TRIANGLE_FILE_MAX_LENGTH 100000
#define TRIANGLE_LINE_MAX_LENGTH 600

#include <stdio.h>

FILE *triangle_file_pointer = 0;
int triangle_return_code, triangle_sum = 0, triangle_adjacent_position =
	0, triangle_row_index = 0, triangle_column_index = 0;
char triangle_character_string[TRIANGLE_LINE_MAX_LENGTH];

/* AF 1/28/2014 Find the greatest adjacent number */
void triangle_equal_find_greatest (int triangle_left_num)
{
	int triangle_right_num, triangle_new_adjacent_position =
		triangle_adjacent_position;

	triangle_return_code = fscanf (	triangle_file_pointer, "%d", 
		&triangle_right_num);
	if (triangle_return_code && (triangle_return_code != EOF))
	{
		if (triangle_left_num < triangle_right_num)
		{
			triangle_new_adjacent_position ++;
			triangle_left_num = triangle_right_num;
		}
		triangle_return_code = fscanf (triangle_file_pointer, "%d",
			&triangle_right_num);
		if (triangle_return_code && (triangle_return_code != EOF))
		{
			if (triangle_left_num < triangle_right_num)
			{
				triangle_new_adjacent_position ++;
				triangle_left_num = triangle_right_num;
			}
			triangle_return_code = fscanf (triangle_file_pointer,
				"%d", &triangle_right_num);
			if (triangle_return_code && (triangle_return_code !=
				EOF))
			{
				if (triangle_left_num < triangle_right_num)
				{
					triangle_new_adjacent_position ++;
					triangle_left_num =
						triangle_right_num;
				}
				triangle_sum += triangle_left_num;
				triangle_adjacent_position =
					triangle_new_adjacent_position;
				triangle_return_code = 0;
			}
			else
			/* AF 1/28/2014 File isn't what we expect */
			{
				triangle_return_code = -1;
				printf ("This is not a triangle.\n");
			}
		}
		else
		{
			triangle_return_code = -1;
			printf ("This is not a triangle.\n");
		}
	}
	else
	{
		triangle_return_code = -1;
		printf ("This is not a triangle.\n");
	}
}


/* AF 1/28/2014 What if we have two equal numbers? */
void triangle_equal_numbers ()
{
	int triangle_scanned_number;

	triangle_row_index ++;
	triangle_column_index = 0;
	if (fgets (triangle_character_string, TRIANGLE_LINE_MAX_LENGTH,
		triangle_file_pointer))
	{
		while (!(triangle_return_code || (triangle_return_code == EOF)
				&& (triangle_column_index <
					triangle_adjacent_position)))
		{
			triangle_return_code = fscanf (triangle_file_pointer,
				"%d", &triangle_scanned_number);
			/* AF 1/31/2014 Find adjacent numbers */
			if (triangle_return_code && (triangle_return_code !=
				EOF))
			{
				triangle_return_code = 0;
				triangle_column_index ++;
			}
			else
			{
				triangle_return_code = -1;
				printf ("This is not a triangle.\n");
			}
		}
		if (triangle_column_index == triangle_adjacent_position)
			triangle_equal_find_greatest (triangle_scanned_number);
	}
}

void triangle_summation (int triangle_read_number)
{
	int triangle_left_number, triangle_right_number;

	/* AF 1/23/2014 Are we adjacent? */
	if (triangle_column_index == triangle_adjacent_position) 
	{
		/* AF 1/23/2014 After first row? */
		if (triangle_row_index)
		{
			triangle_left_number = triangle_read_number;
			triangle_return_code = fscanf (triangle_file_pointer,
				"%d", &triangle_right_number);
			if (triangle_return_code && (triangle_return_code !=
				EOF))
			{
				triangle_return_code = 0;
				if (triangle_left_number >=
					triangle_right_number)
				{
					triangle_sum += triangle_left_number;
					/* AF 1/28/2014 If they're equal,
						Find the greatest on the
						next row */
					if (triangle_left_number ==
						triangle_right_number)
						triangle_equal_numbers ();
				}
				else
				{
					triangle_sum += triangle_right_number;
					triangle_adjacent_position ++;
				}
				/* AF 1/23/2014 Next row */
				triangle_row_index ++;
				triangle_column_index = 0;
				fgets (triangle_character_string, 
					TRIANGLE_LINE_MAX_LENGTH,
					triangle_file_pointer);
			}
			else
			/* AF 1/23/2014 File isn't what we expect */
			{
				triangle_return_code = -1;
				printf ("This is not a triangle.\n");
			}
		}
		/* AF 1/23/2014 First row? */
		else
		{
			triangle_sum += triangle_read_number;
			/* AF 1/23/2014 Next row */
			triangle_row_index ++;
			triangle_column_index = 0;
			fgets (triangle_character_string, 
				TRIANGLE_LINE_MAX_LENGTH,
				triangle_file_pointer);

		}
	}
	else
		triangle_column_index ++;
}

void triangle_reading_loop()
{
	int triangle_current_number;

	rewind (triangle_file_pointer);
	/* AF 1/23/2014 Standard EOF check */
	while (!(triangle_return_code || feof(triangle_file_pointer)))
	{
		/* AF 1/23/2014 Make sure we get a number */
		triangle_return_code = fscanf (triangle_file_pointer, "%d",
			&triangle_current_number);
		if (triangle_return_code && (triangle_return_code != EOF))
		{
			triangle_return_code = 0;
			triangle_summation (triangle_current_number);
		}
		else if ((triangle_return_code == EOF) &&
				!triangle_column_index)
		/* AF 1/28/2014 Got trailing newline */
			triangle_return_code = 0;
		else
		{
			/* AF 1/23/2014 File isn't what we expect */
			triangle_return_code = -1;
			printf ("This is not a triangle.\n");
		}
	}
	if (!(triangle_row_index || triangle_column_index))
	{
		triangle_return_code = -1;
		printf ("Sorry, I didn't find the triangle.\n");
	}
}

int main (int argc, char *argv [])
{
	if (triangle_file_pointer = fopen ("triangle.txt", "r"))
	{
		triangle_reading_loop();
		if (!triangle_return_code)
			printf ("The sum is %d.\n", triangle_sum);
		fclose (triangle_file_pointer);
	}
	else
	{
		triangle_return_code = -1;
		printf ("Where's triangle.txt?\n");
	}
	return triangle_return_code;
}
