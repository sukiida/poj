#include <stdio.h>
#include <string.h>

using namespace std;

int g_stamps[25];
int g_used[25];
int g_count;
void init();                    //clear global variables
int get_stamps();
int get_customer(char *str = NULL);
int allocate(int customer, int stamps[], const int max_count);

int main()
{
    while (1) {
	init();                    //clear global variables
	if (get_stamps() == 0) {
	    break;
	}

	char str[1000] = {0};
	gets(str);
	int customer = 0;
	while ((customer = get_customer(str)) != 0) {
	    int stamps[4] = {0};
	    allocate(customer, stamps, sizeof(stamps) / sizeof(stamps[0]));
	}
    }
    return 0;
}

void init()
{
    int count = sizeof(g_stamps) / sizeof(g_stamps[0]);
    for (int i = 0; i < count; i++) {
	g_stamps[i] = 0;
	g_used[i] = 0;
	g_count = 0;
    }
}

int get_stamps()
{
    char str[1000];
    gets(str);
    char *p = strtok(str, " ");
    while(1) {
	if (NULL == p) {
	    break;
	} else {
	    sscanf(p, "%d", &g_stamps[g_count++]);
	    p = strtok(str, " ");
	}
    }
    return g_count;
}

int get_customer(char *str)
{
    static char *p = NULL;
    if (str != NULL) {
	p = strtok(str, " ");
    } else {
	p = strtok(NULL, " ");
    }

    int customer = 0;
    if (p != NULL) {
	return sscanf(p, "%d", &customer);
    }
    return customer;
}

int allocate(int customer, int stamps[], const int max_count)
{
    //sort
    for (int i = 0; i < max_count - 1; i++) {
	for (int j = 0; j < max_count - i - 1; j++) {
	    if (g_stamps[j] > g_stamps[j + 1]) {
		int tmp = g_stamps[j];
		g_stamps[j] = g_stamps[j + 1];
		g_stamps[j + 1] = tmp;
	    }
	}
    }

    int stamps_array[4][200] = {0};
    int n = 0;
    for (int i = 0; i < 25; i++) {
	if (g_stamps[i] == customer) {
	    stamps_array[n][0] = g_stamps[i];
	    n++;
	} else if (g_stamps[i] > customer) {
	    break;
	} else {
	    for (int j = i + 1; j < 25; j++) {
		if (g_stamps[i] > customer / 2) {
		    break;
		}
		int sum = (g_stamps[i] + g_stamps[j]);
		if (customer == sum) {
		    stamps_array[n][0] = g_stamps[i];
		    stamps_array[n][1] = g_stamps[j];
		    n++;
		} else if (customer < sum) {
		    break;
		} else {
		    for (int k = j + 1; j < 25; j++) {
			if (g_stamps[j] > customer / 2) {
			    break;
			}
			int sum = (g_stamps[i] + g_stamps[j] + g_stamps[k]);
			if (customer == sum) {
			    stamps_array[n][0] = g_stamps[i];
			    stamps_array[n][1] = g_stamps[j];
			    stamps_array[n][2] = g_stamps[k];
			    n++;
			} else if (customer < sum) {
			    break;
			} else {
			    for (int l = k + 1; l < 25; l++) {
				if (g_stamps[k] > customer / 2) {
				    break;
				}
				int sum = (g_stamps[i] + g_stamps[j] + 
					   g_stamps[k] + g_stamps[l]);
				if (customer == sum) {
				    stamps_array[n][0] = g_stamps[i];
				    stamps_array[n][1] = g_stamps[j];
				    stamps_array[n][2] = g_stamps[k];
				    stamps_array[n][3] = g_stamps[l];
				    n++;
				} else if (customer < sum) {
				    break;
				}
			    }
			}
		    }
		}
	    }
	}
    }
}
