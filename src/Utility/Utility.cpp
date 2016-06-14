#include "Utility.h"

void assignColor(Color& col)
{
	if (uniCol > 6) uniCol = 0;
	switch(uniCol)
	{
		case 0: col = pastel_red;		break;
		case 1: col = pastel_gray;		break;
		case 2: col = pastel_green;		break;
		case 3: col = pastel_orange;	break;
		case 4: col = pastel_yellow;	break;
		case 5: col = pastel_pink;		break;
		case 6: col = pastel_blue;		break;
	}
}

void assignGrid()
{
	switch(griduni)
	{
		case 0: uniGrid = 4;break;
		case 1: uniGrid = 16;break;
		case 2: uniGrid = 64;break;
		case 3: uniGrid = 256;break;
		case 4: uniGrid = 1024;break;
	}
}