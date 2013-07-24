#include <stdio.h>

static long image[1000][2] = {0};
static int pairs = 0;
static long width = 0;
static long length = 0;
int part_edge(long n, long wpidth, int j);
int pix(long n);
long skip_block(long i);

int main()
{

    while (1) {
	scanf("%ld", &width);
	if (0 == width) {
	    break;
	}


	int a;
	long b;
        //read in RLE image
	while (1) {
	    scanf("%d%ld", &a, &b);
	    if ((0 == a) && (0 == b)) {
		break;
	    }
	    image[pairs][0] = a;
	    image[pairs][1] = b;
	    length += b;
	    pairs++;
	}

	printf("%ld\n", width);
	int edge = 0;
	int last_edge = 0;
	long edge_len = 0;
	for (long i = 1; i <= length; i++) {
	    long s = skip_block(i);
	    i += s;
	    edge = 0;
	    for (int j = 0; j < 9; j++) {
		edge = edge > part_edge(i, width, j) ? edge : part_edge(i, width, j);
	    }

	    if (1 == i) {
		last_edge = edge;  //first pixel
	    }
	    if (edge != last_edge) {
		printf("%d %ld\n", last_edge, edge_len);
		last_edge = edge;
		edge_len = 1;
		continue;
	    } else {
		edge_len += s;
		edge_len++;
	    }
	}
	printf("%d %ld\n", edge, edge_len);
	printf("%d %d\n", 0, 0);
    }
    printf("%d\n", 0);

    return 0;
}


/*****************************************************/
/* 1 2 3					     */
/* 4 5 6					     */
/* 7 8 9  part_edge(n, width, 1) means (s(5) - s(1)) */
/*****************************************************/

int part_edge(long n, long width, int j)
{
    if (4 == j) {
	return 0;
    }

    int k[9][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 0}, {0, 1},
	{1, -1}, {1, 0}, {1, 1} };

    long n2 = n + k[j][0] * width + k[j][1];
    if (n2 < (((n - 1) / width + k[j][0]) * width) + 1 || 
	n2 > (((n - 1) / width + k[j][0] + 1) * width) ||
	n2 < 1 ||
	n2 > length) {
	return 0;
    }

    return pix(n) - pix(n2) > 0 ? 
	(pix(n) - pix(n2)) : (pix(n2) - pix(n));
}

int pix(long n)
{
    long pos = 0;
    int k = 0;
    while(pos < n) {
	pos += image[k++][1];
    }
    return image[k - 1][0];
}

long skip_block(long i)
{
    long ii = i;
    long pos = 0;
    long previous_pos = 0;
    int index = 0;
    while (pos < i && index < pairs) {
	previous_pos = pos;
	pos += image[index++][1];
    }

    /* if (index == pairs) { */
    /* 	goto exit; */
    /* } */

    if (((i - previous_pos) > 2 * width) && ((pos - i) > 2 * width)) {
	i = pos - 2 * width;
    }
exit:
    return i - ii;
}

