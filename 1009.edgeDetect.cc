#include <stdio.h>

static long image[1000][2] = {0};
static int pairs = 0;
static long width = 0;
static long length = 0;
int part_edge(long n, long wpidth, int j);
int pix(long n);
long skip_block(long i);
void one_line();
int abs(int a)
{
    return a > 0 ? a : -a;
}

int main()
{

    while (1) {
	scanf("%ld", &width);
	if (0 == width) {
	    break;
	}

	length = 0;
	pairs = 0;
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
	if (length == width)
	{
	    one_line();
	    continue;
	}

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

#define MAX_COUNT 3000
void one_line()
{
    int count = 0;
    long edge[MAX_COUNT][2] = {0};
    int index = 0;
    while (index < pairs) {
	if (index == 0) {
	    if (image[index][1] == 1) {
		if (index + 1 < pairs) {
		    edge[count][0] = abs(image[index][0] - image[index + 1][0]);
		} else {
		    edge[count][0] = 0;
		}
		edge[count][1] = 1;
		count++;
	    } else {
		if (index + 1 < pairs) {
		    edge[count][0] = 0;
		    edge[count][1] = image[index][1] - 1;
		    count++;
 		    edge[count][0] = abs(image[index][0] - image[index + 1][0]);
		    edge[count][0] = 1;
		    count++;
		} else {
		    edge[count][0] = 0;
		    edge[count][1] = image[index][1];
		    count++;
		}
	    }
	    index++;
	    continue;
	} else if (index == pairs - 1) {
	    if (image[index][1] == 1) {
		if (index - 1 < 0) {
		    edge[count][0] = 0;
		} else {
		    edge[count][0] = abs(image[index][0] - image[index - 1][0]);
		}
		edge[count][1] = 1;
		count++;
	    } else {
		if (index - 1 < 0) {
                    // never enters. same as index == 0 && pairs == 1
		    ;
		} else {
 		    edge[count][0] = abs(image[index][0] - image[index - 1][0]);
		    edge[count][1] = 1;
		    count++;
		    edge[count][0] = 0;
		    edge[count][1] = image[index][1] - 1;
		    count++;
		}
	    }
	    index++;
	    continue;
	} else {  // normal situation
	    if (image[index][1] == 1) {
		int edge1 = abs(image[index][0] - image[index - 1][0]);
		int edge2 = abs(image[index][0] - image[index + 1][0]);
		edge[count][0] = edge1 > edge2 ? edge1 : edge2;
		edge[count][1] = 1;
		count++;
	    } else if (image[index][1] == 2) {
		edge[count][0] = abs(image[index][0] - image[index - 1][0]);
		edge[count][1] = 1;
		count++;
		edge[count][0] = abs(image[index][0] - image[index + 1][0]);
		edge[count][1] = 1;
		count++;
	    } else {
		edge[count][0] = abs(image[index][0] - image[index - 1][0]);
		edge[count][1] = 1;
		count++;
		edge[count][0] = 0;
		edge[count][1] = image[index][1] - 2;
		count++;
		edge[count][0] = abs(image[index][0] - image[index + 1][0]);
		edge[count][1] = 1;
		count++;
	    }
	    index++;
	    continue;
	}
    }

    int tmp = 1;
    int tmp_edge = edge[0][0];
    long tmp_length = edge[0][1];
    while (tmp < count) {
	if (tmp_edge != edge[tmp][0]) {
	    printf("%d %ld\n", tmp_edge, tmp_length);
	    tmp_edge = edge[tmp][0];
	    tmp_length = edge[tmp][1];
	} else {
	    tmp_length += edge[tmp][1];
	}
	tmp++;
    }
    printf("%d %ld\n", tmp_edge, tmp_length);
    printf("0 0\n");
}
