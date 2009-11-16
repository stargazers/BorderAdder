#include <stdio.h>
#include <stdlib.h>
#include <Imlib2.h>
#include <string.h>

/*
Image scaler & Border adder
Copyright (C) 2009 Aleksi Räsänen <aleksi.rasanen@runosydan.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
int main( int argc, char *argv[] )
{
	Imlib_Image input_image;
	Imlib_Image output_image;

	int input_width, input_height;
	int output_width, output_height;
	int border_left, border_right, border_top, border_bottom;
	int color_red, color_green, color_blue, color_alpha;

	if( argc != 12 ) 
	{
		printf( "Usage: %s INPUT OUTPUT WIDTH HEIGHT ", argv[0] );
		printf( "LEFT_BORDER_WIDTH RIGHT_BORDER_WIDTH " );
		printf( "TOP_BORDER_WIDTH BOTTOM_BORDER_WIDTH " );
		printf( "COLOR_RED COLOR_GREEN COLOR_BLUE " );
		exit(1);
	}

	// Output image dimensions are read from CLI args.
	output_width = atoi( argv[3] );
	output_height = atoi( argv[4] );

	// Border size must be read from CLI arg too.
	border_left = atoi( argv[5] );
	border_right = atoi( argv[6] );
	border_top = atoi( argv[7] );
	border_bottom = atoi( argv[8] );

	// Read border color RGB from CLI.
	color_red = atoi( argv[9] );
	color_green = atoi( argv[10] );
	color_blue = atoi( argv[11] );
	color_alpha = 255;

	// Load image
	input_image = imlib_load_image( argv[1] );

	if(! input_image )
	{
		printf( "Failed to load image %s\n", argv[1] );
		exit(1);
	}

	// Read original image size
	imlib_context_set_image( input_image );
	input_width = imlib_image_get_width();
	input_height = imlib_image_get_height();

	// Swap output width and height if image height is greater
	// than its width.
	if( input_height > input_width )
	{
		int tmp = output_height;
		output_height = output_width;
		output_width = tmp;
	}

	// Create new output image with given dimensions
	output_image = imlib_create_image( 
		output_width + border_left + border_right,
		output_height + border_top + border_bottom );

	// Select image to handle
	imlib_context_set_image( output_image );

	// Set current color
	imlib_context_set_color( color_red, color_green, color_blue, 255 );

	// Fill the output image with current color
	imlib_image_fill_rectangle( 0, 0, 
		output_width + border_left + border_right,
		output_height + border_top + border_bottom );

	// Copy whole input image to output image
	imlib_blend_image_onto_image( input_image, 0, 0, 0, 
		input_width, input_height, 
		border_left, 
		border_top, 
		output_width, output_height );

	// Save output imge.
	imlib_save_image( argv[2] );

	return 0;
}
