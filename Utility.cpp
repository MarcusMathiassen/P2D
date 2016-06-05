#include "Utility.h"
#include "Color.h"

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
		case 5: col = pastel_purple;	break;
		case 6: col = pastel_blue;		break;
	}
}