#include <stdio.h>
#include <string.h>

using namespace std;

int g_stamps[25];
int g_used[25];
int g_count;
void init();                    //clear global variables
int get_stamps();
//int get_customer(char *str = NULL);
int get_customer(char *str);
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
    ;
}
