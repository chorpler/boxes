/*
 * boxes - Command line filter to draw/remove ASCII boxes around text
 * Copyright (c) 1999-2023 Thomas Jensen and the boxes contributors
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
 * License, version 3, as published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

/*
 * Shape handling and information functions
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "bxstring.h"


typedef enum {
    NW, NNW, N, NNE, NE, ENE, E, ESE, SE, SSE, S, SSW, SW, WSW, W, WNW
} shape_t;

extern char *shape_name[];

#define NUM_SHAPES 16

#define SHAPES_PER_SIDE 5
#define CORNERS_PER_SIDE 2
#define NUM_SIDES       4
#define NUM_CORNERS     4

extern shape_t north_side[SHAPES_PER_SIDE];  /* groups of shapes, clockwise */
extern shape_t  east_side[SHAPES_PER_SIDE];
extern shape_t south_side[SHAPES_PER_SIDE];
extern shape_t south_side_rev[SHAPES_PER_SIDE];
extern shape_t  west_side[SHAPES_PER_SIDE];
extern shape_t corners[NUM_CORNERS];
extern shape_t *sides[NUM_SIDES];


typedef struct {
    char    **chars;
    bxstr_t **mbcs;
    size_t    height;
    size_t    width;

    /** elastic is used only in original definition */
    int       elastic;

    /** For each shape line 0..height, a flag which is 1 if all shapes to the left of this shape are blank on the same
     *  shape line. Always 1 if the shape is part of the left (west) box side. */
    int      *blank_leftward;

    /** For each shape line 0..height, a flag which is 1 if all shapes to the right of this shape are blank on the same
     *  shape line. Always 1 if the shape is part of the right (east) box side. */
    int      *blank_rightward;
} sentry_t;

#define SENTRY_INITIALIZER (sentry_t) {NULL, NULL, 0, 0, 0, NULL, NULL}



int genshape (const size_t width, const size_t height, char ***chars, bxstr_t ***mbcs);
void freeshape (sentry_t *shape);

shape_t findshape (const sentry_t *sarr, const int num);
int on_side (const shape_t s, const int idx);

int isempty (const sentry_t *shape);
int isdeepempty (const sentry_t *shape);

size_t highest (const sentry_t *sarr, const int n, ...);
size_t widest (const sentry_t *sarr, const int n, ...);

int empty_side (sentry_t *sarr, const int aside);



#endif /*SHAPE_H*/

/*EOF*/                                          /* vim: set cindent sw=4: */
