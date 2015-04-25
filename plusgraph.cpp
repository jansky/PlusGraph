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
#include "plusgraph.h"

PGGraphRaw pg_init_raw_graph(int width, int height)
{
	PGGraphRaw raw_graph = (PGPointType**)calloc(height + 1, sizeof(PGPointType*));

	if(raw_graph == NULL)
		return NULL;

	for(int i = 0; i <= height; i++)
	{
		raw_graph[i] = (PGPointType*)calloc(width + 1, sizeof(PGPointType));

		if(raw_graph[i] == NULL)
			return NULL;
	}

	return raw_graph;
}

void pg_destroy_raw_graph(PGGraphRaw raw_graph, int height)
{
	for(int i = 0; i <= height; i++)
	{
		free(raw_graph[i]);
	}

	free(raw_graph);

}

PGGraphRaw pg_raw_graph_gen(PGGraph graph, int scale)
{
	int width = graph.width;
	int height = graph.height;

	PGGraphRaw raw_graph = pg_init_raw_graph(graph.width, graph.height);

	if(raw_graph == NULL)
		return NULL;

	for(int i = 0; i < graph.points.size(); i++)
	{
		int x = (int)round(graph.points[i].x/(double)scale);
		int y = (int)round(graph.points[i].y/(double)scale);

		int xr = 0;
		int yr = 0;

		if(y == 0)
			yr = height/2;
		else if(y > 0)
			yr = (height/2) - y;
		else
			yr = (height/2) + (y*-1);

		if(x == 0)
			xr = width/2;
		else if(x > 0)
			xr = (width/2) + x;
		else
			xr = (width/2) - (x*-1);

		if((xr < 0 || xr > width) || (yr < 0 || yr > height))
			;
		else
			raw_graph[yr][xr] = graph.points[i].type;
	}

	return raw_graph;
}

bool pg_graph_draw(PGGraph graph, PGDisplayInfo dinfo,int scale)
{
	PGGraphRaw raw_graph = pg_raw_graph_gen(graph,scale);

	if(raw_graph == NULL)
		return false;

	for(int y = 0; y <= graph.height; y++)
	{
		for(int x = 0; x <= graph.width; x++)
		{
			//printf("(%d,%d)\n", x, y);
			if(raw_graph[y][x] == PGPT_POINT)
				printf("%c", dinfo.point);
			else if(raw_graph[y][x] == PGPT_SHADED)
				printf("%c", dinfo.shaded);
			else
				if(x == (graph.height/2) && y == (graph.width/2))
					printf("%c", dinfo.origin);
				else if(x == (graph.height/2))
					printf("%c", dinfo.xaxis);
				else if(y == (graph.width/2))
					printf("%c", dinfo.yaxis);
				else
					printf("%c", dinfo.nopoint);
		}

		printf("\n");
	}

	return true;
}

PGGraph pg_graph_create(int width, int height)
{
	std::vector<PGPoint> points;

	PGGraph graph;

	graph.width = width;
	graph.height = height;
	graph.points = points;

	return graph;
}

PGPoint pg_point_create(double x, double y, PGPointType type)
{
	PGPoint point;

	point.x = x;
	point.y = y;
	point.type = type;
	

	return point;
}

PGDisplayInfo pg_display_info_create(char xaxis, char yaxis, char origin, char nopoint, char point, char shaded)
{
	PGDisplayInfo dinfo;

	dinfo.xaxis = xaxis;
	dinfo.yaxis = yaxis;
	dinfo.origin = origin;
	dinfo.nopoint = nopoint;
	dinfo.point = point;
	dinfo.shaded = shaded;

	return dinfo;
}