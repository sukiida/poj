/********************************************************************************/
/* Can be improved by a sorting of nums[] before calc.			        */
/* Because bigger numbers can be calculated on the base of previous calculation */
/********************************************************************************/

#include <stdio.h>

long skip_group(int k);
long skip_integer(int k);

int main()
{
    int count;
    scanf("%d", &count);
    unsigned long nums[10];
    for (int i = 0; i < count; i++)
    {
	scanf("%ld", &nums[i]);
    }

    for (int i = 0; i < count; i++) {
	int index = 0;
	int index_r = 0;
	long k = 1;
	while (1) {
	    index_r = index;
	    index += skip_group(k);
	    if (index >= nums[i]) {
		break;
	    }
	    k++;
	}

	k = 1;
	index = index_r;
	while (1) {
	    index_r = index;
	    index += skip_integer(k);
	    if (index >= nums[i]) {
		break;
	    }
	    k++;
	}

	int remain = nums[i] - index_r;
	int digits[10] = {0};
	int len = 1;
	digits[0] = k % 10;
	while ((k /= 10) != 0) {
	    digits[len++] = k % 10;
	}
	printf("%d\n", digits[len - remain]); 
    }

    return 0;
}

long skip_group(int k)
{
    long ret;
    int tmp = k;
    int pow = 1;
    ret = k;
    //each number >= 10 adds a digit to the sum of digits in the group
    //each number >= 100 adds another digit to the sum of digits in the group
    //...
    while((tmp /= 10) != 0) {
	ret += k - (pow * 10 -1);
	pow *= 10;
    }
    return ret;
}

long skip_integer(int k)
{
    long ret = 1;
    while ((k /= 10) != 0) {
	ret++;
    }
    return ret;
}
