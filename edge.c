#include <stdio.h>

typedef struct edgeDirectionConverter_t
{
    // These indicate if an edge exists between the direction and the next
    int string_edge_in[8];
    int string_edge_out[8];
    int region_edge_in[8];
    int region_edge_out[8];

    // these map incoming dirctions to outgoing directions
    int string_edge_map[8];
    int region_edge_map[8];
}
edgeDirectionConverter_t;

int wrap_direction(int d)
{
    if(d >= 8)
    {
        d -= 8;
    }
    else if(d < 0)
    {
        d += 8;
    }
    return d;
}

int main(int argc, char **argv)
{
    // Build a set of edge guides for points on a go board
    // depending only on the colour of the surrounding stones
    // The edge of the board is treated as if ot were stones
    //
    // Use bit 0 to show if there is a stone in the x direction
    // Bit 1 is then 45 degrees anticlockwise and so on

    edgeDirectionConverter_t edgeConverter[256];

    for(int i = 0; i < 256; i++)
    {
        //detect changes from 0 to 1 and 1 to 0 in adjacent bits
	for(int j = 0; j < 8; j++)
	{
            edgeConverter[i].string_edge_in[j] = 0;
            edgeConverter[i].string_edge_out[j] = 0;
            edgeConverter[i].region_edge_in[j] = 0;
            edgeConverter[i].region_edge_out[j] = 0;
	}

	for(int j = 0; j < 8; j++)
	{
	    int stone_in_main_direction = i & (1 << j);
	    int stone_in_next_direction = i & (1 << wrap_direction(j + 1));
	
	    if (stone_in_main_direction && !stone_in_next_direction)
	    {
	        edgeConverter[i].string_edge_in[wrap_direction(j + 1)] = 1;
	    }
	    else if (!stone_in_main_direction && stone_in_next_direction)
	    {
	        edgeConverter[i].string_edge_out[j] = 1;
	    }
	}
    }

    // dump 'em
    for(int i = 0; i < 256; i++)
    {
        printf("\n%c %c %c\n", i & (1 << 3) ? 'X' : '.', i & (1 << 2) ? 'X' : '.', i & (1 << 1) ? 'X' : '.');
        printf("%c . %c\n", i & (1 << 4) ? 'X' : '.', i & 1 ? 'X' : '.');
        printf("%c %c %c\n\n", i & (1 << 5) ? 'X' : '.', i & (1 << 6) ? 'X' : '.', i & (1 << 7) ? 'X' : '.');
	for(int j = 0; j < 8; j++)
	{
	    if(edgeConverter[i].string_edge_in[j])
	    {
	        printf("edge in, position %d ", j);
	    }
	    else
	    {
	        printf("                     ");
	    }

	    if(edgeConverter[i].string_edge_out[j])
	    {
	        printf("edge out, position %d\n", j);
	    }
	    else
	    {
	        printf("\n");
	    }
	}
    }
}
