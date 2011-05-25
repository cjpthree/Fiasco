/*      
 *  fig.c:		Simple drawing functions for xfig-files
 *
 *  Written by:         Martin Grimm
 *
 *  This file is part of FIASCO (�F�ractal �I�mage �A�nd �S�equence �CO�dec)
 *  Copyright (C) 1994-2000 Ullrich Hafner <hafner@bigfoot.de>
 */
 
/*
 *  $Date: 2000/07/15 17:20:59 $
 *  $Author: hafner $
 *  $Revision: 5.1 $
 *  $State: Exp $
 */

#include "config.h"

#include "types.h"
#include "macros.h"
#include "error.h"

#include <stdio.h>

#include "fig.h"


/*******************************************************************************

				public code
  
*******************************************************************************/

/******************************************************************************
 *                                 NOTE:                                      *
 * all coordinates and widths are measured in 1/1200 inches, if not described *
 ******************************************************************************/

void
xfig_header (FILE *out)
/*
 *  Writes header of xfig-file 'out'.
 *
 *  No return value.
 */
{
   fprintf (out, "#FIG 3.2\n");
   fprintf (out, "#generated by twfa " VERSION "\n");
   fprintf (out, "Landscape\n");
   fprintf (out, "Center\n");
   fprintf (out, "Inches\n");
   fprintf (out, "A4\n");
   fprintf (out, "100.00\n");
   fprintf (out, "Single\n");
   fprintf (out, "-1\n");
   fprintf (out, "1200 2\n");
}

void
xfig_circle (FILE *out, int x, int y, int r, int pencolor, int fillcolor,
	     int level)
/*
 *  Write the command to draw a circle in a xfig-file
 *
 *  out       - the file to write in
 *  x, y      - coordinates of the center
 *  r         - radius
 *  pencolor  - the color of the circle border
 *  fillcolor - the color, the circle is filled with
 *  level     - the level, the circle is drawn on (0-999)
 *
 *  No return value.
 */
{
   fprintf (out, "1 3 0 1 %d %d %d 0 20 0.000 1 0.0000 %d %d %d %d %d %d %d %d\n",
	    pencolor, fillcolor, level, x, y, r, r, x, y, x + r, y + r);
}

void
xfig_triangle (FILE *out, int x, int y, int height, int width, int pencolor,
	       int fillcolor, int level)
/*
 *  Write the command to draw a triangle in a xfig-file
 *
 *  out       - the file to write in
 *  x, y      - coordinates of the upper peak of the triangle
 *  height    - height of the triangle from the peak to the baseline
 *  width     - width of the triangle at the baseline
 *  pencolor  - the color of the triangle border
 *  fillcolor - the color, the triangle is filled with
 *  level     - the level, the triangle is drawn on (0-999)
 */
{
   fprintf (out, "2 3 0 1 %d %d %d 0 20 0.000 0 0 -1 0 0 4\n",
	    pencolor, fillcolor, level);
   fprintf(out, "\t %d %d %d %d %d %d %d %d\n",
	   x, y, x + width / 2, y + height, x - width / 2, y + height, x, y); 
}

void
xfig_line (FILE *out, int x1, int y1, int x2, int y2, int color, int linestyle,
	   int thickness, int level)
/*
 *  Write the command to draw a line in a xfig-file
 *
 *  out       - the file to write in
 *  x1, y1    - coordinates of the start point of the line
 *  x2, y2    - coordinates of the end point of the line
 *  color     - the color of the line
 *  linestyle - SOLID, DASHED or DOTTED
 *  thickness - the thickness of the line in 1/80 inch measures
 *  level     - the level, the line is drawn on (0-999)
 */
{
   fprintf (out, "2 1 %d %d %d -1 %d 0 20 0.000 0 1 7 0 0 2\n",
	    linestyle, thickness, color, level);
   fprintf (out, "\t %d %d %d %d\n", x1, y1, x2, y2);
}

void
xfig_centerbox (FILE *out, int x, int y, int x_offset, int y_offset, int pencolor,
		int fillcolor, int level)
/*
 *  Writes the command to draw a box to a xfig-file, using the center coordinates
 *  and the width and height from the center to border
 *
 *  out       - the file to write in
 *  x, y      - coordinates of the center of the box
 *  x_offset  - distance from the center to the left/right border
 *  y_offset  - distance from the center to the upper/lower border
 *  pencolor  - the color of the border of the box
 *  fillcolor - the color, the box is filled with
 *  level     - the level, the box is drawn on (0-999)
 */
{
   fprintf (out, "2 2 0 1 %d %d %d 0 20 0.000 0 0 -1 0 0 5\n",
	    pencolor, fillcolor, level);
   fprintf (out, "\t %d %d %d %d %d %d %d %d %d %d\n",
	    x - x_offset, y - y_offset, x + x_offset, y - y_offset,
	    x + x_offset, y + y_offset, x - x_offset, y + y_offset,
	    x - x_offset, y - y_offset); 
}

void
xfig_box (FILE *out, int x, int y, int height, int width, int pencolor,
	  int fillcolor, int level)
/*
 *  Writes the command to draw a box to a xfig-file, using the coordinates
 *  of the upper left edge and the width and height of the box
 *
 *  out       - the file to write in
 *  x, y      - coordinates of the upper left edge of the box
 *  height    - height of the box
 *  width     - width of the box
 *  pencolor  - the color of the border of the box
 *  fillcolor - the color, the box is filled with
 *  level     - the level, the box is drawn on (0-999)
 */
{
   fprintf (out, "2 2 0 1 %d %d %d 0 20 0.000 0 0 -1 0 0 5\n",
	    pencolor, fillcolor, level);
   fprintf (out, "\t %d %d %d %d %d %d %d %d %d %d\n",
	    x, y, x + width, y, x + width, y + height, x, y + height, x, y); 
}