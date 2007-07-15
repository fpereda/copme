#include "ctme.h"

char *name(void)
{
	static char n[] = "test ctme: failure";
	return n;
}

int repeat(void)
{
	return 1;
}

void run_test(void)
{
	CTME_CHECK_EQUAL_STRING("this will", "definitely fail");
}
