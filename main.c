/*
Image scaler & border adder.
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

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	if( argc < 6 )
	{
		printf( "Usage: %s image width height ", argv[0] );
		printf( "border_width border_color (hex value)\n" );
		exit(1);
	}

	gtk_init( &argc, &argv );

	GdkPixbuf *pb;
	GdkPixbuf *new_pb;
	 GdkPixbufFormat *info;

	int width, height, border_width;
	int original_width, original_height;
	guint32 border_color;

	// Final image width and heigth WIHOUT borders.
	width = atoi( argv[2] );
	height = atoi( argv[3] );
	border_width = atoi( argv[4] );

	// Read input image dimensions
	info = gdk_pixbuf_get_file_info( argv[1], 
		&original_width, &original_height );

	// Swap width and height in output image dimensions
	// if height is greater than width.
	if( original_height > original_width )
	{
		int tmp = width;
		width = height;
		height = tmp;
	}


	// Convert fifth param (hex color) to unsigned long.
	char *pEnd = NULL;
	border_color = strtoul( argv[5], &pEnd, 0 );

	// Allocate enough memory for output filename string.
	char *output = malloc( strlen( argv[1] ) + 5 );
	GError *error = NULL;

	if( output == NULL )
	{
		printf( "Failed to malloc!\n" );
		exit(1);
	}

	// Create output filename
	sprintf( output, "new_%s", argv[1] );

	// Final output image pixbuf.
	new_pb = gdk_pixbuf_new( GDK_COLORSPACE_RGB, TRUE, 8,
		width + (2 * border_width), height + (2 * border_width) );
	
	// Open input image scaled.
	pb = gdk_pixbuf_new_from_file_at_scale( argv[1], width, height,
		FALSE, &error );

	// Fill new pixbuf with given border color, so we can get 
	// correct color for borders after we have added copied image.
	gdk_pixbuf_fill( new_pb, border_color );

	// Copy scaled input to output image, but leave enough
	// space for borders.
	gdk_pixbuf_copy_area( pb, 0, 0, width, height, new_pb, 
		border_width, border_width );

	// Save final output image.
	gdk_pixbuf_save( new_pb, output, "jpeg", &error, "quality", 
		"85", NULL );

	return 0;
}
