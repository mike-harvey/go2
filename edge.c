#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct part_path_t
{
    int path_direction_in;
    int path_direction_out;
    bool path_visits_centre;
    bool path_is_active;
}
part_path_t;

typedef struct edgeDirectionConverter_t
{
    // These indicate if an edge exists between the direction and the next
    int string_edge_in[8];
    int string_edge_out[8];

    // these map incoming dirctions to outgoing directions
    int string_edge_part_path_count;
    part_path_t string_edge_part_paths[4];

    //int region_edge_in[8];
    //int region_edge_out[8];
    //path_t region_edge_paths[4];
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
    assert(0 <= d && d < 8);
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
            //edgeConverter[i].region_edge_in[j] = 0;
            //edgeConverter[i].region_edge_out[j] = 0;
	}

	edgeConverter[i].string_edge_part_path_count = 0;

	for(int j = 0; j < 4; j++)
	{
	    edgeConverter[i].string_edge_part_paths[j].path_is_active = false;
	    edgeConverter[i].string_edge_part_paths[j].path_visits_centre = false;
	    edgeConverter[i].string_edge_part_paths[j].path_direction_in = 0;
	    edgeConverter[i].string_edge_part_paths[j].path_direction_out = 0;
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

    // Figure out the string edge paths
    for(int i = 0; i < 256; i++)
    {
        for(int j=0; j < 8; j++)
	{
	    if(edgeConverter[i].string_edge_out[j])
	    {
	        for(int k = 1; k <= 8; k++)
		{
		    if(edgeConverter[i].string_edge_in[wrap_direction(j + k)])
		    {
		        // Found an edge - in and out
                        int path = edgeConverter[i].string_edge_part_path_count++;

	                edgeConverter[i].string_edge_part_paths[path].path_is_active = true;
			edgeConverter[i].string_edge_part_paths[path].path_visits_centre = true;
			edgeConverter[i].string_edge_part_paths[path].path_direction_in = wrap_direction(j + k);
			edgeConverter[i].string_edge_part_paths[path].path_direction_out = j;

			if(j % 2 == 0 && k == 2)
			{
			    edgeConverter[i].string_edge_part_paths[path].path_visits_centre = false;
			}
			break;
		    }
		}
	    }
	}
    }

    // dump 'em
    for(int i = 0; i < 256; i++)
    {
        printf("\n%c %c %c\n", i & (1 << 3) ? 'X' : '.', i & (1 << 2) ? 'X' : '.', i & (1 << 1) ? 'X' : '.');
        printf("%c . %c\n", i & (1 << 4) ? 'X' : '.', i & 1 ? 'X' : '.');
        printf("%c %c %c\n\n", i & (1 << 5) ? 'X' : '.', i & (1 << 6) ? 'X' : '.', i & (1 << 7) ? 'X' : '.');

	for(int j = 0; j < edgeConverter[i].string_edge_part_path_count; j++)
	{
	    printf("path: active ? %c, visits_centre ? %c, in %d, out %d\n",
		   edgeConverter[i].string_edge_part_paths[j].path_is_active ? 'T' : 'F',
		   edgeConverter[i].string_edge_part_paths[j].path_visits_centre ? 'T' : 'F',
		   edgeConverter[i].string_edge_part_paths[j].path_direction_in,
		   edgeConverter[i].string_edge_part_paths[j].path_direction_out);
	}
#if 0
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
#endif
    }
}
