/*
    PlusGraph Library (libplusgraph)
    Copyright (C) 2015 Ian Duncan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <vector>

#define PGPT_NOPOINT 0
#define PGPT_POINT 1
#define PGPT_SHADED 2


typedef uint8_t PGPointType;
typedef PGPointType** PGGraphRaw;

typedef struct PGPoint{

	double x;
	double y;

	PGPointType type;

} PGPoint;

typedef struct PGGraph
{
	int width;
	int height;

	std::vector<PGPoint> points;
} PGGraph;

typedef struct PGDisplayInfo
{
	char xaxis;
	char yaxis;
	char origin;
	char nopoint;
	char point;
	char shaded;
} PGDisplayInfo;

PGGraphRaw pg_init_raw_graph(int width, int height);
void pg_destroy_raw_graph(PGGraphRaw raw_graph);

PGGraphRaw pg_raw_graph_gen(PGGraph graph, int scale);

bool pg_graph_draw(PGGraph graph, PGDisplayInfo dinfo,int scale=1);

PGGraph pg_graph_create(int width, int height);
PGPoint pg_point_create(double x, double y, PGPointType type);
PGDisplayInfo pg_display_info_create(char xaxis, char yaxis, char origin, char nopoint, char point, char shaded);

