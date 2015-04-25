/*
    PlusGraph
    Copyright (C) 2015 Ian Duncan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "plusgraph.h"
#include <pluscalc.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

int main(int argc, char **argv)
{
	if(argc > 1 && std::string(argv[1]) == "--license")
	{
			std::cout << "PlusGraph" << std::endl;
    		std::cout << "Copyright (C) 2015 Ian Duncan" << std::endl << std::endl;

    		std::cout << "This program is free software: you can redistribute it and/or modify" << std::endl;
		    std::cout << "it under the terms of the GNU General Public License as published by" << std::endl;
		    std::cout << "the Free Software Foundation, either version 3 of the License, or" << std::endl;
		    std::cout << "(at your option) any later version." << std::endl << std::endl;

		    std::cout << "This program is distributed in the hope that it will be useful," << std::endl;
		    std::cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl;
		    std::cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl;
		    std::cout << "GNU General Public License for more details." << std::endl << std::endl;

		    std::cout << "You should have received a copy of the GNU General Public License" << std::endl;
		    std::cout << "along with this program.  If not, see <http://www.gnu.org/licenses/>." << std::endl << std::endl;
	}
	else if(argc < 5)
	{
		std::cout << "Usage: " << argv[0] << " [width] [height] [scale] [equation]" << std::endl;
		std::cout << "Usage: " << argv[0] << " --license" << std::endl << std::endl;
		std::cout << "This program is free software with ABSOLUTELY NO WARRANTY." << std::endl;
		exit(1);
	}
	else
	{
		int width = atoi(argv[1]);
		int height = atoi(argv[2]);
		int scale = atoi(argv[3]);
		std::string equation = "";
		PGGraph graph = pg_graph_create(width,height);
		PGDisplayInfo dinfo = pg_display_info_create('|', '-', '+', '.', '*', '#');

		if(width == 0 || height == 0 || scale == 0)
		{
			std::cout << "Usage: " << argv[0] << " [width] [height] [scale] [equation]" << std::endl;
			exit(1);
		}

		for(int i = 4; i < argc; i++)
		{
			equation += std::string(argv[i]) += " ";
		}

		for(double x = ((-1*(width/2))*scale); x <= ((width/2)*scale); x+=0.5)
		{
			try
			{
				std::stringstream dconv;

				dconv << x;

				

				std::string eqwithx = ReplaceString(equation, "x", dconv.str());

				

				

				double result = (double)pc_evaluate_math_expression(eqwithx);

				

				graph.points.push_back(pg_point_create(x, result, PGPT_POINT));
			}
			catch(PCException err)
			{
				
				if(err == domainerror)
					; //Domain error (i.e. sqrt -1), just ignore
				else
				{
					std::cout << "Syntax error in equation." << std::endl;
					exit(1);
				}
			}
			catch(...)
			{
				std::cout << "Error evaluating equation." << std::endl;
				exit(2);
			}
		}

		if(!pg_graph_draw(graph, dinfo,scale))
		{
			std::cout << "Error displaying graph." << std::endl;
			exit(2);
		}




	}

	return 0;




	
}

