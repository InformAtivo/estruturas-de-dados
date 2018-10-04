#include <stdio.h>
#include <time.h>


int main ()
{
    int importancia;
    time_t atual;
    atual = time (NULL);
    struct tm str_time;
		time_t time_of_day;

		str_time.tm_year = 2019-1900;
		str_time.tm_mon = 6;
		str_time.tm_mday = 5;
		str_time.tm_hour = 10;
		str_time.tm_min = 3;
		str_time.tm_sec = 5;
		str_time.tm_isdst = 0;

		time_of_day = mktime (&str_time);
		printf(ctime(&time_of_day));
        printf("seconds fake data is %ld \n",time_of_day);
    printf(ctime(&atual));
    printf ("Number of seconds since January 1, 1970 is %ld \n", atual);
    importancia = (time_of_day)-(atual);
    printf ("importancia relativa = %ld",importancia);
    return 0;
}
